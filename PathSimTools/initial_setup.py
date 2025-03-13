import os
import sys

import bpy
import bmesh

from materials import create_boundary_material, create_bright_material

def create_boundaries(env_settings):
    boundaries = env_settings['boundaries']
    x_min, x_max = boundaries["xMin"], boundaries["xMax"]
    y_min, y_max = boundaries["yMin"], boundaries["yMax"]
    z_min, z_max = boundaries["zMin"], boundaries["zMax"]
    material = create_boundary_material()

    size_x = abs(x_max - x_min)
    size_y = abs(y_max - y_min)
    size_z = abs(z_max - z_min)

    # X min boundary plane (left side)
    create_boundary_plane("XMin_Boundary", location=(x_min, 0, 0), rotation=(0, 1.5708, 0), scale=(size_z, size_y, 1),
                          material=material)
   #  X max boundary plane (right side)
    create_boundary_plane("XMax_Boundary", location=(x_max, 0, 0), rotation=(0, 1.5708, 0), scale=(size_z, size_y, 1),
                          material=material)
    # Y min boundary plane (front side)
    create_boundary_plane("YMin_Boundary", location=(0, y_min, 0), rotation=(1.5708, 0, 0), scale=(size_x, size_z, 1),
                          material=material)
    # Y max boundary plane (back side)
    create_boundary_plane("YMax_Boundary", location=(0, y_max, 0), rotation=(1.5708, 0, 0), scale=(size_x, size_z, 1),
                          material=material)
     #Z min boundary plane (bottom side)
    create_boundary_plane("ZMin_Boundary", location=(0, 0, z_min), rotation=(0, 0, 0), scale=(size_x, size_y, 1),
                          material=material)
    # Z max boundary plane (top side)
    create_boundary_plane("ZMax_Boundary", location=(0, 0, z_max), rotation=(0, 0, 0), scale=(size_x, size_y, 1),
                          material=material)





def create_boundary_plane(name, location, rotation, scale, material):
    # Using 'bpy.data.objects.new' to directly create a plane without using operators
    mesh = bpy.data.meshes.new(name + "_mesh")
    plane = bpy.data.objects.new(name, mesh)

    # Link to the scene collection and set location, rotation, and scale
    bpy.context.collection.objects.link(plane)
    plane.location = location
    plane.rotation_euler = rotation

    # Create the geometry for the plane
    bpy.context.view_layer.objects.active = plane
    bpy.context.view_layer.update()

    # Add mesh data manually for a 1x1 plane and then scale it up
    vertices = [(-0.5, -0.5, 0), (0.5, -0.5, 0), (0.5, 0.5, 0), (-0.5, 0.5, 0)]
    edges = []
    faces = [(0, 1, 2, 3)]
    mesh.from_pydata(vertices, edges, faces)
    mesh.update()

    # Scale the plane to the required size
    plane.scale = scale
    plane.data.materials.append(material)
    bpy.context.view_layer.update()

def set_viewport_shading(shading_type='MATERIAL'):
    # Iterate over all windows in the Blender context
    for window in bpy.context.window_manager.windows:
        for area in window.screen.areas:
            if area.type == 'VIEW_3D':
                # Temporarily override context to apply shading mode to the 3D View area
                for space in area.spaces:
                    if space.type == 'VIEW_3D':
                        with bpy.context.temp_override(window=window, area=area, space=space):
                            space.shading.type = shading_type  # Options: 'WIREFRAME', 'SOLID', 'MATERIAL', 'RENDERED'
                break

def create_glowing_marker(name, location, color=(1, 0, 0, 1), size=0.1):
    mesh = bpy.data.meshes.new(name)
    sphere = bpy.data.objects.new(name, mesh)
    bpy.context.collection.objects.link(sphere)
    bpy.context.view_layer.objects.active = sphere
    sphere.select_set(True)
    bm = bmesh.new()
    bmesh.ops.create_uvsphere(bm, u_segments=32, v_segments=16, radius=size)
    bm.to_mesh(mesh)
    bm.free()
    sphere.location = location

    material = create_bright_material(name, color)

    # Apply the material to the sphere
    sphere.data.materials.append(material)
    bpy.context.view_layer.update()

def create_camera(location, rotation):
    bpy.ops.object.camera_add(location=location, rotation=rotation)
    camera = bpy.context.view_layer.objects.active  # Use the camera as the active object
    bpy.context.scene.camera = camera


def setup(envSettings):
    create_boundaries(envSettings)
    set_viewport_shading()
    create_glowing_marker("StartPoint", envSettings["start_position"]["translation"], color=(0, 1, 0, 1), size=0.5)
    if not isinstance(envSettings["end_position"], str):
        create_glowing_marker("EndPoint", envSettings["end_position"]["translation"], color=(1, 0, 0, 1), size=0.5)
    create_camera(location=(25.0, -30.0, 22.0), rotation=(1.1, 0.0, 0.785))
