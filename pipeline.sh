#!/bin/bash

###
# Make sure you `pip install bpy` and `pip install datetime` before running! 
#
# Make sure you have Blender installed on your machine inside the Applications directory -- this script as is will only work on MacOS
# 
# This script should be run from the cs2240-final-project directory.
#
# Usage: ./pipeline.sh <number_of_runs> <num_frames_list> <num_particles_list> <grid_size_list>
# The lists should be comma-separated values surrounded in quotes. For example:
#
# ./pipeline.sh 3 "100,200,300" "100,400,1600" "5,8,10"
# would run the simulation 3 times with the following parameters:
# 1. 100 frames, 100 particles, 5x5 grid
# 2. 200 frames, 400 particles, 8x8 grid
# 3. 300 frames, 1600 particles, 10x10 grid
###

if [ "$#" -lt 4 ]; then
    echo "Usage: $0 <number_of_runs> <num_frames_list> <num_particles_list> <grid_size_list>"
    exit 1
fi

num_runs=$1
num_frames_list=($(echo $2 | tr "," "\n"))
num_particles_list=($(echo $3 | tr "," "\n"))
grid_size_list=($(echo $4 | tr "," "\n"))

# there must be num_runs number of elements in each list
if [ ${#num_frames_list[@]} -ne $num_runs ] || [ ${#num_particles_list[@]} -ne $num_runs ] || [ ${#grid_size_list[@]} -ne $num_runs ]; then
  echo "ERROR: Number of runs must match the number of elements in each list"
  exit 1
fi

# number of particles must be a perfect square
for num_particles in "${num_particles_list[@]}"
do
  sqrt=$(echo "sqrt($num_particles)" | bc)
  if [ $sqrt -ne ${sqrt%.*} ]; then
    echo "ERROR: Number of particles must be a perfect square"
    exit 1
  fi
done

for (( i=0; i<$num_runs; i++ ))
do
  num_frames=${num_frames_list[$i]}
  num_particles=${num_particles_list[$i]}
  grid_size=${grid_size_list[$i]}

  echo "Run $((i+1))/$num_runs with frames=$num_frames, particles=$num_particles, grid_size=$grid_size"

  make clean all

  ./letitsnow $num_frames $num_particles $grid_size

  if [ ! -f "data/simulation.json" ]; then
    echo "JSON file not generated. Skipping to next run..."
    continue
  else
    echo "JSON file generated -- converting to Alembic..."
  fi

  python3 blender/jsontoalembic.py

  if [ ! -f "data/exported_scene.abc" ]; then
    echo "ERROR: Alembic file not generated. Skipping to next run..."
    rm data/simulation.json
    continue
  else
    echo "Alembic file generated -- rendering in Blender..."
  fi

  /Applications/Blender.app/Contents/MacOS/blender -b -P blender/renderabc.py

  rm data/simulation.json
  rm data/exported_scene.abc

  if [ $? -eq 0 ]; then
    echo "Render complete!!"
  else
    echo "Rendering failed :( Skipping to next run..."
    continue
  fi
done