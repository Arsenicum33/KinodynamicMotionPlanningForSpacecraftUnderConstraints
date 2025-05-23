import argparse
import math
from time import time
from math import radians
from operator import matmul

import bpy
import bmesh
import json
import sys
import os
from mathutils import Quaternion
script_dir = os.path.dirname(__file__)
sys.path.append(script_dir)

import materials
import initial_setup


# Function to apply keyframes (assuming pose_data is available and contains frames, positions, and rotations)
def apply_keyframes(obj, pose_data):
    for pose in pose_data:
        frame = pose["time"]
        position = pose["position"]
        rotation = pose["rotation"]

        # Set the object's location and rotation
        obj.location = position
        obj.rotation_euler = rotation

        # Insert keyframes for location and rotation
        obj.keyframe_insert(data_path="location", frame=frame)
        obj.keyframe_insert(data_path="rotation_euler", frame=frame)

def apply_keyframes_quaternion_rotation(obj, pose_data):
    obj.rotation_mode = 'QUATERNION'
    for pose in pose_data:
        frame = pose["time"]
        position = pose["position"]
        rotation = pose["rotation"]

        # Set the object's location and rotation
        obj.location = position
        obj.rotation_quaternion = Quaternion(rotation)

        # Insert keyframes for location and rotation
        obj.keyframe_insert(data_path="location", frame=frame)
        obj.keyframe_insert(data_path="rotation_quaternion", frame=frame)


def apply_interpolation(obj, interpolation):
    if obj.animation_data and obj.animation_data.action:
        for fcurve in obj.animation_data.action.fcurves:
            for keyframe in fcurve.keyframe_points:
                keyframe.interpolation = interpolation

def import_celestial_bodies(celestial_bodies):
    for body, properties in celestial_bodies.items():
        import_objects(properties['mesh'])
        obj = bpy.context.view_layer.objects.active
        apply_keyframes(obj, properties['positions'])


def import_objects(object_filepath):
    if object_filepath is None:
        return
    file_extension = object_filepath.split('.')[-1].lower()  # Get file extension
    for window in bpy.context.window_manager.windows:
        for area in window.screen.areas:
            if area.type == 'VIEW_3D':  # Ensure we are in the 3D View context
                with bpy.context.temp_override(window=window, area=area):
                    if file_extension == 'obj':
                        # Import OBJ file
                        bpy.ops.wm.obj_import(filepath=object_filepath, forward_axis='Y', up_axis='Z')
                    elif file_extension == 'fbx':
                        # Import FBX file
                        bpy.ops.import_scene.fbx(filepath=object_filepath)
                    else:
                        print(f"Unsupported file format: {file_extension}")
                break

def parse_args():
    parser = argparse.ArgumentParser(description="Command-line argument parser")
    parser.add_argument("--env", type=str, help="Filename with env settings")
    args = parser.parse_args()
    print(vars(args))

def reg():
    bpy.app.handlers.frame_change_post.append(update)

def unregister():
    bpy.app.handlers.frame_change_post.remove(update)

def find_closest_pose(currentTime):
    for pose in agent_trajectory:
        if pose["time"] > currentTime:
            return pose
    return None

def update(scene):
    text = bpy.data.objects['ParametersText']
    curTime = scene.frame_current
    pose = find_closest_pose(curTime)
    if pose is None:
        return
    params_str = (
            f"Time: {pose['time']:.2f}s\n"
            f"Translation: ({pose['position'][0]:.2f}, {pose['position'][1]:.2f}, {pose['position'][2]:.2f})\n"
            f"Rotation: ({pose['rotation'][0]:.2f}, {pose['rotation'][1]:.2f}, {pose['rotation'][2]:.2f})\n"
            f"Velocity: ({pose['velocity'][0]:.2f}, {pose['velocity'][1]:.2f}, {pose['velocity'][2]:.2f})\n"
            f"Ang. Velocity: ({pose['angularVelocity'][0]:.2f}, {pose['angularVelocity'][1]:.2f}, {pose['angularVelocity'][2]:.2f})\n"
            )
    text.data.body = params_str

def output_advanced_position_data(pose_data):
    global start_time
    start_time = None
    bpy.ops.object.text_add(location=(0, 0, 25))
    text_obj = bpy.context.active_object
    text_obj.name = "ParametersText"
    text_obj.rotation_euler = (radians(90), 0, 0)  # Rotate to face the camera
    text_obj.scale = (1.5, 1.5, 1.5)  # Make text smaller for readability
    text_obj.data.align_x = 'LEFT'  # Align text to the left for better formatting
    text_obj.data.align_y = 'TOP'  # Align text to the top
    text_obj.data.body = "Initial text"
    bpy.app.handlers.frame_change_post.append(update)



if __name__ == "__main__":

    argv = sys.argv
    argv = argv[argv.index("--") + 1:]

    blender_input_filepath = argv[0]

    with open(blender_input_filepath, 'r') as file:
        blender_input = json.load(file)


    bpy.context.preferences.view.show_splash = False
    import_objects(blender_input.get("obstacles"))
    import_objects(blender_input.get("agent").get("mesh"))

    agent = bpy.context.view_layer.objects.active

    agent_material = materials.create_saturated_material("black", (0, 0, 0, 1))

    agent.data.materials.append(agent_material)


    dynamic_objects = blender_input.get("dynamic_objects")
    if dynamic_objects is not None:
        for dynamic_object in dynamic_objects:
            import_objects(dynamic_object)

    if isinstance(blender_input.get('target'), str):
        import_objects(blender_input.get('target'))


    initial_setup.setup(blender_input)

    agent_trajectory = blender_input.get("agent").get("trajectory")

    apply_keyframes_quaternion_rotation(agent, agent_trajectory)
    #apply_interpolation(agent, "BEZIER")
    bpy.context.scene.render.fps_base = 1
    bpy.context.scene.frame_start = 1
    bpy.context.scene.frame_end = math.ceil(agent_trajectory[-1]["time"])
    bpy.context.scene.frame_current = 1

    env_type = blender_input["env_type"]
    if env_type == "kinodynamic" or env_type == "astrodynamic":
        output_advanced_position_data(agent_trajectory)

    if env_type == "astrodynamic":
        print("IMPORTING CELESTIAL")
        import_celestial_bodies(blender_input["celestial_bodies"])




