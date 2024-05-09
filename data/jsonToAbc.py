import assimp
import json

def convert_json_to_abc(json_file, abc_file):
    # Load JSON data
    with open(json_file, 'r') as f:
        data = json.load(f)
    
    # Create a scene
    scene = assimp.Scene()
    
    # Create a camera node
    camera_node = assimp.Node()
    camera_node.name = "camera"
    camera_node.transformation = assimp.Matrix4x4(data['camera']['fov'])
    scene.root_node.children.append(camera_node)
    
    # Create a ground node
    ground_node = assimp.Node()
    ground_node.name = "ground"
    ground_node.transformation = assimp.Matrix4x4(data['ground']['position'])
    scene.root_node.children.append(ground_node)

    # Create a sphere node
    sphere_node = assimp.Node()
    sphere_node.name = "ball"
    sphere_node.transformation = assimp.Matrix4x4(data['ball']['position'])
    scene.root_node.children.append(sphere_node)
    
    # Create particle nodes
    for particle_data in data['particles']:
        particle_node = assimp.Node()
        particle_node.name = particle_data['name']
        particle_node.transformation = assimp.Matrix4x4(particle_data['position'])
        scene.root_node.children.append(particle_node)
    
    # Export scene to Alembic file
    assimp.export(scene, abc_file, 'abc')

# Example usage
json_file = 'simulation.json'
abc_file = 'simulation.abc'
convert_json_to_abc(json_file, abc_file)