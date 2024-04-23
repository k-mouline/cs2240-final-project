import bpy
import json

def load_json_data(filename):
    with open(filename, 'r') as file:
        return json.load(file)

def setup_scene(scene_data):
    scene = bpy.context.scene
    scene.render.resolution_x = scene_data['resolution'][0]
    scene.render.resolution_y = scene_data['resolution'][1]
    scene.frame_start = scene_data['frame_range'][0]
    scene.frame_end = scene_data['frame_range'][1]
    scene.render.fps = scene_data['frame_rate']

def setup_camera(camera_data):
    camera = bpy.data.objects.get("Camera")
    if not camera:
        bpy.ops.object.camera_add()
        camera = bpy.context.object
        camera.name = "Camera"
    
    camera.location = tuple(camera_data['position'])
    camera.rotation_euler = tuple(camera_data['rotation'][0], camera_data['rotation'][1], camera_data['rotation'][2])
    camera.data.angle = camera_data['fov'] * (3.14159 / 180)

def create_particle(particle_data):
    mesh = bpy.data.meshes.new(particle_data['name'])
    obj = bpy.data.objects.new(particle_data['name'], mesh)
    bpy.context.collection.objects.link(obj)
    
    obj.location = tuple(particle_data['position'])
    obj.scale = tuple(particle_data['scale'])

    mat = bpy.data.materials.new(name=f"{particle_data['name']}_Material")
    mat.diffuse_color = particle_data['color'] + [1.0]
    obj.data.materials.append(mat)

    for anim in particle_data['animation']:
        obj.location = tuple(anim['position'])
        obj.keyframe_insert(data_path="location", frame=anim['frame'])

def setup_ground(ground_data):
    bpy.ops.mesh.primitive_plane_add(size=1)
    ground = bpy.context.object
    ground.name = "Ground"
    ground.location = tuple(ground_data['position'])
    ground.scale = tuple(ground_data['scale'])

    mat = bpy.data.materials.new(name="Ground_Material")
    mat.diffuse_color = ground_data['material']['color'] + [1.0]  # Include alpha
    ground.data.materials.append(mat)

def main():
    filename = bpy.path.abspath('//data/simulation.json')
    data = load_json_data(filename)

    setup_scene(data['scene_setup'])
    setup_camera(data['camera'])

    for particle in data['particles']:
        create_particle(particle)

    setup_ground(data['ground'])

if __name__ == "__main__":
    main()
