#!/bin/bash

# Created by: Mr Coxall
# Created on: Sep 2022
# Created for: To automate the generation of gameboy files

base_name=$(basename "$1" .c)

# remove old gameboy file from the simulator directory
rm /workspaces/Youngwook-Go-ICS3U-Final-Project-YoungwookGo/simulator/rom/game.gb

# compile to game
/opt/gbdk/bin/lcc -Wa-l -Wl-m -Wl-j -o $base_name.gb $base_name.c

# move it to the simulator directory
cp ./$base_name.gb /workspaces/Youngwook-Go-ICS3U-Final-Project-YoungwookGo/simulator/rom/game.gb
