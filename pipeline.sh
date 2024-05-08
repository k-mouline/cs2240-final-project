#!/bin/bash

make clean all

./letitsnow

if [ ! -f "../data/simulation.json" ]; then
    echo "JSON file not generated."
    exit 1
fi

python3 blender/jsontoalembic.py

blender --background --python blender/renderabc.py

if [ $? -eq 0 ]; then
    rm /path/to/data/simulation.json
    rm /path/to/data/exported_scene.abc
    echo "Temporary files deleted successfully."
else
    echo "Rendering failed. Temporary files not deleted."
fi