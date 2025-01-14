import bpy


def create_glow_material(name, color, strength):
    material = bpy.data.materials.new(name=name + "_GlowMaterial")
    material.use_nodes = True
    nodes = material.node_tree.nodes
    nodes.clear()
    output_node = nodes.new(type="ShaderNodeOutputMaterial")
    emission_node = nodes.new(type="ShaderNodeEmission")
    # Set the emission color and strength
    emission_node.inputs["Color"].default_value = color  # Color of the glow
    emission_node.inputs["Strength"].default_value = strength  # Brightness of the glow
    # Link emission node to output
    material.node_tree.links.new(emission_node.outputs["Emission"], output_node.inputs["Surface"])
    return material

def create_bright_material(name, color):
    material = bpy.data.materials.new(name=name)
    material.use_nodes = True
    nodes = material.node_tree.nodes

    # Clear existing nodes to avoid conflicts
    nodes.clear()

    # Create a simple Diffuse BSDF shader for a solid red color
    diffuse_node = nodes.new(type="ShaderNodeBsdfDiffuse")
    diffuse_node.inputs["Color"].default_value = color  # Solid red color

    # Create a material output node and link it
    output_node = nodes.new(type="ShaderNodeOutputMaterial")
    material.node_tree.links.new(diffuse_node.outputs["BSDF"], output_node.inputs["Surface"])

    return material


def create_saturated_material(name, color):
    # Create a new material
    material = bpy.data.materials.new(name=name)
    material.use_nodes = True
    nodes = material.node_tree.nodes
    nodes.clear()  # Clear any existing nodes

    # Create a Principled BSDF shader for saturated black
    principled_node = nodes.new(type="ShaderNodeBsdfPrincipled")
    principled_node.inputs["Base Color"].default_value = color
    principled_node.inputs["Roughness"].default_value = 1.0  # Matte finish
    principled_node.inputs["Metallic"].default_value = 1.0  # No specular reflections

    # Create a material output node and link it
    output_node = nodes.new(type="ShaderNodeOutputMaterial")
    material.node_tree.links.new(principled_node.outputs["BSDF"], output_node.inputs["Surface"])

    return material


def create_boundary_material():
    # Create a new material with transparency settings
    material = bpy.data.materials.new(name="BoundaryMaterial")
    material.use_nodes = True
    material.blend_method = 'BLEND'  # Enables transparency in material

    # Get the nodes and clear the existing ones
    nodes = material.node_tree.nodes
    nodes.clear()

    # Create necessary nodes
    output_node = nodes.new(type="ShaderNodeOutputMaterial")
    principled_node = nodes.new(type="ShaderNodeBsdfPrincipled")

    # Set the Base Color and Alpha for transparency
    principled_node.inputs["Base Color"].default_value = (0.3, 0.6, 0.9, 1)  # Red color, fully opaque color
    principled_node.inputs["Alpha"].default_value = 0.05  # Adjust this value for transparency level (0.0 - 1.0)

    # Link nodes
    material.node_tree.links.new(principled_node.outputs["BSDF"], output_node.inputs["Surface"])

    return material