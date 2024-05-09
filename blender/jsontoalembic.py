import bpy
import json
import sys
from tqdm import tqdm

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

def create_particle(particle_data, material):
  bpy.ops.mesh.primitive_uv_sphere_add(segments=8, ring_count=4, radius=particle_data['size'])
  sphere = bpy.context.object
  sphere.name = particle_data['name']

  sphere.location = tuple(particle_data['position'])
  sphere.scale = tuple(particle_data['scale'])

  sphere.data.materials.append(material)

  bpy.context.view_layer.objects.active = sphere
  sphere.select_set(True)

  for anim in particle_data['animation']:
    sphere.location = tuple(anim['position'])
    sphere.keyframe_insert(data_path="location", frame=anim['frame'])

  bpy.ops.object.select_all(action='DESELECT')

def setup_ground(ground_data):
  bpy.ops.mesh.primitive_plane_add(size=1)
  ground = bpy.context.object
  ground.name = "Ground"
  ground.location = tuple(ground_data['position'])
  ground.scale = (ground_data['scale'])

  mat = bpy.data.materials.new(name="Ground_Material")
  mat.diffuse_color = ground_data['material']['color']
  ground.data.materials.append(mat)

def export_alembic(filepath):
  bpy.ops.wm.alembic_export(filepath=filepath)

def save_blend_file():
  blend_file_path = bpy.path.abspath(f"//output/rendered_project-{sys.argv[2]}.blend")
  bpy.ops.wm.save_as_mainfile(filepath=blend_file_path)

def clear_mesh_objects():
  for obj in bpy.data.objects:
    if obj.type == 'MESH':
      bpy.data.objects.remove(obj, do_unlink=True)

def setup_sphere(sphere_data):
  # bpy.ops.mesh.primitive_plane_add(size=1)
  bpy.ops.mesh.primitive_uv_sphere_add(radius=sphere_data['radius'])
  sphere = bpy.context.object
  sphere.name = "ball"
  sphere.location = tuple(sphere_data['position'])
  # sphere.scale = tuple(sphere_data['scale'])

  mat = bpy.data.materials.new(name="Sphere_Material")
  mat.diffuse_color = sphere_data['material']['color']
  sphere.data.materials.append(mat)

def main():
  clear_mesh_objects()

  filename = bpy.path.abspath('//data/simulation.json')
  data = load_json_data(filename)

  setup_scene(data['scene_setup'])
  setup_camera(data['camera'])

  mat = bpy.data.materials.new(name="Particle_Material")
  mat.diffuse_color = data['particles'][0]['color']

  for particle in tqdm(data['particles']):
    create_particle(particle, mat)

  setup_ground(data['ground'])
  setup_sphere(data['ball'])
  print("Exporting Alembic file...")
  export_alembic(bpy.path.abspath('//data/exported_scene.abc'))
  print("Alembic file exported successfully!")
  save_blend_file()
  print("Blend file saved successfully!")

if __name__ == "__main__":
    main()