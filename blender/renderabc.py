import bpy
import sys

def load_alembic(filepath):
  bpy.ops.wm.alembic_import(filepath=filepath)

def setup_render_settings():
  bpy.context.scene.render.image_settings.file_format = 'FFMPEG'
  bpy.context.scene.render.ffmpeg.format = 'MPEG4'
  bpy.context.scene.render.ffmpeg.codec = 'H264'
  bpy.context.scene.render.ffmpeg.constant_rate_factor = 'PERC_LOSSLESS'
  bpy.context.scene.render.filepath = f'//output/snow-{sys.argv[5]}.mp4'

def render_scene():
  bpy.ops.render.render(animation=True)

def clear_mesh_objects():
  for obj in bpy.data.objects:
    if obj.type == 'MESH':
        bpy.data.objects.remove(obj, do_unlink=True)
    elif obj.type == 'CAMERA':
        obj.location = (0, -5, 0)
        obj.rotation_euler = ((90 * (3.1415 / 180)), 0, 0)

def main():
  # print(sys.argv)
  clear_mesh_objects()

  alembic_file = bpy.path.abspath('//data/exported_scene.abc')

  load_alembic(alembic_file)
  setup_render_settings()
  render_scene()

if __name__ == "__main__":
    main()

