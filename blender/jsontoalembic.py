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

def create_particle(particle_data):
  bpy.ops.mesh.primitive_uv_sphere_add(segments=8, ring_count=4, radius=particle_data['size'])
  sphere = bpy.context.object
  sphere.name = particle_data['name']

  sphere.location = tuple(particle_data['position'])
  sphere.scale = tuple(particle_data['scale'])

  mat = bpy.data.materials.new(name=f"{particle_data['name']}_Material")
  mat.diffuse_color = particle_data['color']
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

def export_alembic(filepath):
  bpy.ops.wm.alembic_export(filepath=filepath)

def main():
  filename = bpy.path.abspath('//data/simulation.json')
  data = load_json_data(filename)

  setup_scene(data['scene_setup'])
  setup_camera(data['camera'])

  for particle in data['particles']:
    create_particle(particle)

  setup_ground(data['ground'])

  export_alembic(bpy.path.abspath('//data/exported_scene.abc'))

if __name__ == "__main__":
    main()
