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
        frame = pose["frame"]
        position = pose["position"]
        rotation = pose["rotation"]

        # Set the object's location and rotation
        obj.location = position
        obj.rotation_euler = rotation

        # Insert keyframes for location and rotation
        obj.keyframe_insert(data_path="location", frame=frame)
        obj.keyframe_insert(data_path="rotation_euler", frame=frame)





def import_objects(object_filepath):
    for window in bpy.context.window_manager.windows:
        for area in window.screen.areas:
            if area.type == 'VIEW_3D':  # Ensure we are in the 3D View context
                with bpy.context.temp_override(window=window, area=area):
                    # Import OBJ file
                    bpy.ops.wm.obj_import(filepath=object_filepath, forward_axis='Y', up_axis='Z')
                break


def setup_grease_pencil():
    # Check if the Grease Pencil object and data block already exist
    gp_data = bpy.data.grease_pencils.get("AgentTrace")
    gp_obj = bpy.data.objects.get("AgentTrace")

    # Create a new Grease Pencil data block and object if needed
    if gp_data is None:
        gp_data = bpy.data.grease_pencils.new("AgentTrace")
        print("Created new Grease Pencil data block.")
    if gp_obj is None:
        gp_obj = bpy.data.objects.new("AgentTrace", gp_data)
        bpy.context.collection.objects.link(gp_obj)
        print("Linked Grease Pencil object to the scene.")

    # Create a Grease Pencil material with shader nodes if it doesn't exist
    material_name = "TraceMaterial"
    material = bpy.data.materials.get(material_name)
    if material is None:
        material = bpy.data.materials.new(name=material_name, use_nodes=True)
        material.use_nodes = True
        material.grease_pencil = True  # Set material to Grease Pencil type
        print("Created Grease Pencil material with nodes.")

        # Set up shader nodes for color and stroke thickness
        node_tree = material.node_tree
        nodes = node_tree.nodes
        nodes.clear()  # Clear any default nodes

        # Add a Stroke Shader (for line color) and set it to red
        stroke_shader = nodes.new(type="ShaderNodeStroke")
        stroke_shader.inputs["Color"].default_value = (1.0, 0.0, 0.0, 1.0)  # Red color
        stroke_shader.inputs["Thickness"].default_value = 3.0  # Set desired stroke thickness

        # Create Material Output and connect the Stroke Shader
        output_node = nodes.new(type="ShaderNodeOutputMaterial")
        node_tree.links.new(stroke_shader.outputs["Color"], output_node.inputs["Surface"])

    # Ensure the Grease Pencil object uses the new material by name
    if not any(mat.name == material_name for mat in gp_obj.data.materials):
        gp_obj.data.materials.append(material)
        print(f"Added material '{material_name}' to Grease Pencil object.")

    # Ensure an active Grease Pencil layer exists
    if len(gp_data.layers) == 0:
        gp_layer = gp_data.layers.new(name="TraceLayer", set_active=True)
        print("Created new Grease Pencil layer.")
    else:
        gp_layer = gp_data.layers.active

    return gp_layer


# Function to draw a trace for the agent with Blender 4.2 compatibility
def draw_trace(scene):
    try:
        gp_layer = setup_grease_pencil()
        frame_number = scene.frame_current

        # Check if a frame already exists for the current time
        gp_frame = None
        for frame in gp_layer.frames:
            if frame.frame_number == frame_number:
                gp_frame = frame
                break

        # If no frame exists, create a new one
        if gp_frame is None:
            gp_frame = gp_layer.frames.new(frame_number=frame_number)
            print(f"Created frame {frame_number} in Grease Pencil layer.")

        # Add a stroke at the agent's location for the current frame
        stroke = gp_frame.strokes.new()
        stroke.display_mode = '3DSPACE'
        stroke.material_index = 0  # Use the first material (TraceMaterial)
        stroke.points.add(count=1)
        stroke.points[0].co = agent.location

        # Print successful stroke creation
        print(f"Frame {frame_number}: Added trace point at location {agent.location}")
    except Exception as e:
        # Print any errors encountered during draw_trace execution
        print(f"Error on frame {scene.frame_current}: {str(e)}")


with open("envSettings.json", 'r') as file:
    envSettings = json.load(file)

with open("paths.json", 'r') as file:
    paths = json.load(file)
build_dir = paths['build_dir']
cpp_output_filepath = str(os.path.join(build_dir, paths['output_name']))
obstacles_filepath = str(os.path.join(paths['obstacles_dir'],envSettings['obstacles_name']))
agent_filepath = os.path.join(paths['agent_dir'],envSettings['agent_name'])


bpy.ops.wm.read_factory_settings(use_empty=True)  # Clear the scene

bpy.context.preferences.view.show_splash = False




import_objects(obstacles_filepath)
import_objects(agent_filepath)


agent = bpy.context.view_layer.objects.active

agent_material = materials.create_saturated_material("black", (0,0,0,1))
agent.data.materials.append(agent_material)


initial_setup.setup(envSettings)

with open(cpp_output_filepath, 'r') as file:
    pose_data = json.load(file)

apply_keyframes(agent, pose_data)


bpy.context.scene.frame_start = 1
bpy.context.scene.frame_end = len(pose_data)
bpy.context.scene.frame_current = 1

#bpy.app.handlers.frame_change_post.clear()  # Clear any existing handlers to avoid duplicates
#bpy.app.handlers.frame_change_post.append(draw_trace)
#print("Trace script added for the agent. Play the animation to see the trace.")
#for frame in range(bpy.context.scene.frame_start, bpy.context.scene.frame_end + 1):
 #   bpy.context.scene.frame_set(frame)
#print("Completed frame stepping for trace.")
