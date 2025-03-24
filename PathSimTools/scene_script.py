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


def apply_interpolation(obj, interpolation):
    if obj.animation_data and obj.animation_data.action:
        for fcurve in obj.animation_data.action.fcurves:
            for keyframe in fcurve.keyframe_points:
                keyframe.interpolation = interpolation


def import_objects(object_filepath):
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
    print("BEFORE:" + bpy.app.handlers.frame_change_post)
    bpy.app.handlers.frame_change_post.append(update)
    print("AFTER:" + bpy.app.handlers.frame_change_post)

def unregister():
    bpy.app.handlers.frame_change_post.remove(update)

def find_closest_pose(currentTime):
    for pose in pose_data:
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
    #bpy.app.timers.register(update, first_interval=0.01, persistent=True)
    #for data in pose_data:
    #    frame = data["time"]
    #    bpy.context.scene.frame_set(frame)
    #    params_str = (
    #        f"Time: {data['time']:.2f}s\n"
    #        f"Translation: ({data['position'][0]:.2f}, {data['position'][1]:.2f}, {data['position'][2]:.2f})\n"
    #        f"Rotation: ({data['rotation'][0]:.2f}, {data['rotation'][1]:.2f}, {data['rotation'][2]:.2f})\n"
    #        f"Velocity: ({data['velocity'][0]:.2f}, {data['velocity'][1]:.2f}, {data['velocity'][2]:.2f})\n"
    #       f"Ang. Velocity: ({data['angularVelocity'][0]:.2f}, {data['angularVelocity'][1]:.2f}, {data['angularVelocity'][2]:.2f})\n"
    #    )

        # Update the text object and keyframe the changes
    #    text_obj.data.body = params_str
    #    text_obj.keyframe_insert(data_path="data.body", frame=frame)





argv = sys.argv
argv = argv[argv.index("--") + 1:]

with open(argv[0], 'r') as file:
    envSettings = json.load(file)

with open("paths.json", 'r') as file:
    paths = json.load(file)
build_dir = paths['build_dir']
cpp_output_filepath = str(os.path.join(build_dir, paths['output_name']))
obstacles_filepath = str(os.path.join(paths['obstacles_dir'],envSettings['obstacles_name']))
agent_filepath = os.path.join(paths['agent_dir'],envSettings['agent_name'])

#bpy.ops.wm.read_factory_settings(use_empty=True)  # Clear the scene

bpy.context.preferences.view.show_splash = False




import_objects(obstacles_filepath)
import_objects(agent_filepath)

dynamic_objects_names = envSettings['dynamic_objects_names']
if dynamic_objects_names:
    dynamic_objects_filepaths = []
    for name in dynamic_objects_names:
        dynamic_objects_filepaths.append(str(os.path.join(paths['animations_dir'],name)))
    for filepath in dynamic_objects_filepaths:
        import_objects(filepath)

if isinstance(envSettings["end_position"], str):
    target_filepath = str(os.path.join(paths['animations_dir'],envSettings["end_position"]))
    import_objects(target_filepath)

agent = bpy.context.view_layer.objects.active

agent_material = materials.create_saturated_material("black", (0,0,0,1))
agent.data.materials.append(agent_material)


initial_setup.setup(envSettings)

with open(cpp_output_filepath, 'r') as file:
    pose_data = json.load(file)

apply_keyframes(agent, pose_data)
apply_interpolation(agent, "BEZIER")
bpy.context.scene.render.fps_base = 1
bpy.context.scene.frame_start = 1
bpy.context.scene.frame_end = math.ceil(pose_data[-1]["time"])
bpy.context.scene.frame_current = 1

if envSettings["kinodynamic"]:
    output_advanced_position_data(pose_data)



