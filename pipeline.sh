#!/bin/bash

###
# Make sure you `pip install bpy` and `pip install datetime` before running! 
#
# Make sure you have Blender installed on your machine inside the Applications directory -- this script as is will only work on MacOS
# 
# This script should be run from the cs2240-final-project directory.
###

make clean all

./letitsnow

if [ ! -f "data/simulation.json" ]; then
  echo "JSON file not generated."
  exit 1
else
  echo "JSON file generated -- converting to Alembic..."
fi

python3 blender/jsontoalembic.py

if [ ! -f "data/exported_scene.abc" ]; then
  echo "ERROR: Alembic file not generated"
  exit 1
else
  echo "Alembic file generated -- rendering in Blender..."
fi

/Applications/Blender.app/Contents/MacOS/blender -b -P blender/renderabc.py

if [ $? -eq 0 ]; then
  rm data/simulation.json
  rm data/exported_scene.abc
  echo "Render complete!! JSON and ABC files deleted"
else
  echo "Rendering failed :( Temporary files not deleted."
fi
