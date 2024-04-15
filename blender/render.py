import bpy
import json

def load_json_data(filename):
  with open(filename, 'r') as file:
    return json.load(file)

def setup_scene(scene_data):
  bpy.context.scene.render.resolution_x = scene_data['resolution'][0]
  bpy.context.scene.render.resolution_y = scene_data['resolution'][1]
  bpy.context.scene.frame_start = scene_data['frame_range'][0]
  bpy.context.scene.frame_end = scene_data['frame_range'][1]
  bpy.context.scene.render.fps = scene_data['frame_rate']

def setup_camera(camera_data):
  if "Camera" not in bpy.data.objects:
    bpy.ops.object.camera_add()
    camera = bpy.context.object
    camera.name = "Camera"
  else:
    camera = bpy.data.objects["Camera"]

  camera.location = camera_data['position']
  camera.rotation_euler = [camera_data['rotation'][0], camera_data['rotation'][1], camera_data['rotation'][2]]
  camera.data.angle = camera_data['fov'] * (3.14159 / 180)
def create_particle(particle_data):
  mesh = bpy.data.meshes.new(particle_data['name'])
  obj = bpy.data.objects.new(particle_data['name'], mesh)
  bpy.context.collection.objects.link(obj)
  obj.location = particle_data['position']
  obj.scale = particle_data['scale']

  mat = bpy.data.materials.new(name=f"{particle_data['name']}_Material")
  mat.diffuse_color = particle_data['color'] + [1]
  obj.data.materials.append(mat)

  for anim in particle_data['animation']:
    obj.location = anim['position']
    obj.keyframe_insert(data_path="location", frame=anim['frame'])

def setup_ground(ground_data):
  bpy.ops.mesh.primitive_plane_add(size=1)
  ground = bpy.context.object
  ground.name = "Ground"
  ground.location = ground_data['position']
  ground.scale = ground_data['scale']

  mat = bpy.data.materials.new(name="Ground_Material")
  mat.diffuse_color = ground_data['material']['color'] + [1]
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
