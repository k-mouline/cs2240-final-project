import bpy
from datetime import datetime

timestamp = datetime.now().strftime("%Y%m%d-%H%M%S")

def load_alembic(filepath):
  bpy.ops.wm.alembic_import(filepath=filepath)

def setup_render_settings():
  bpy.context.scene.render.image_settings.file_format = 'FFMPEG'
  bpy.context.scene.render.ffmpeg.format = 'MPEG4'
  bpy.context.scene.render.ffmpeg.codec = 'H264'
  bpy.context.scene.render.ffmpeg.constant_rate_factor = 'PERC_LOSSLESS'
  bpy.context.scene.render.filepath = f'//output/snow-{timestamp}.mp4'

def render_scene():
  bpy.ops.render.render(animation=True)

def save_blend_file():
  blend_file_path = bpy.path.abspath(f"//output/rendered_project-{timestamp}.blend")
  bpy.ops.wm.save_as_mainfile(filepath=blend_file_path)

def clear_mesh_objects():
  for obj in bpy.data.objects:
    if obj.type == 'MESH':
        bpy.data.objects.remove(obj, do_unlink=True)

def main():
  clear_mesh_objects()

  alembic_file = bpy.path.abspath('//data/exported_scene.abc')

  load_alembic(alembic_file)
  setup_render_settings()
  render_scene()
  save_blend_file()

if __name__ == "__main__":
    main()
