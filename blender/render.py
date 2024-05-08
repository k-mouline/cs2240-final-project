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
  camera.rotation_euler = tuple(camera_data['rotation'])
  camera.data.angle = camera_data['fov'] * (3.14159 / 180)

def create_particle(particle_data, mat):
  bpy.ops.mesh.primitive_uv_sphere_add(segments=4, ring_count=4, radius=particle_data['size'])
  sphere = bpy.context.object
  sphere.name = particle_data['name']
  
  sphere.location = tuple(particle_data['position'])
  sphere.scale = tuple(particle_data['scale'])
  sphere.data.materials.append(mat)

  for anim in particle_data['animation']:
    sphere.location = tuple(anim['position'])
    sphere.keyframe_insert(data_path="location", frame=anim['frame'])

  bpy.ops.object.select_all(action='DESELECT')

def setup_ground(ground_data):
  bpy.ops.mesh.primitive_plane_add(size=1)
  ground = bpy.context.object
  ground.name = "Ground"
  ground.location = tuple(ground_data['position'])
  ground.scale = tuple(ground_data['scale'])

  mat = bpy.data.materials.new(name="Ground_Material")
  mat.diffuse_color = ground_data['material']['color']
  ground.data.materials.append(mat)

def setup_wall(wall_data):
    bpy.ops.mesh.primitive_plane_add(size=1, location=wall_data["position"])
    wall = bpy.context.object
    wall.scale = tuple(wall_data["scale"])
    wall.rotation_euler[0] = 3.141592;
    wall.rotation_euler[1] = 3.141592 / 2;
    mat = bpy.data.materials.new(name="Wall_Material")
    mat.diffuse_color = wall_data["material"]["color"]
    mat.roughness = wall_data["material"]["roughness"]
    mat.metallic = wall_data["material"]["metallic"]
    if wall.data.materials:
        wall.data.materials[0] = mat
    else:
        wall.data.materials.append(mat)

def main():
  filename = bpy.path.abspath('//../data/simulation.json')
  data = load_json_data(filename)

  setup_scene(data['scene_setup'])
  setup_camera(data['camera'])

  mat = bpy.data.materials.new(name="Particle_Material")
  mat.diffuse_color = data['particles'][0]['color']

  for particle in data['particles']:
      create_particle(particle, mat)

  setup_ground(data['ground'])
  setup_wall(data['wall'])

if __name__ == "__main__":
    main()
