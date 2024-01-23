// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the tetris program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>

#include "Game.c"
#include "Background.c"

void main() {
    // User input
    uint8_t joypadData;

    // Set background tile sheet
    set_bkg_data(0, 23, TileLabel);  // starting tile, number of tiles, data

    // Load times from the tile map called Background
    set_bkg_tiles(0, 0, 32, 32, Background);  // x, y, width, height, map

    SHOW_BKG;
    DISPLAY_ON;

    // Game Loop
    while (1) {
        // Get D-Pad input
        joypadData = joypad();

        // When the D-Pad Right is pressed
        if (joypadData & J_RIGHT) {
            // Move the background to the right by 1 pixels
            scroll_bkg(1, 0);
        }

        // When the D-Pad Left is pressed
        if (joypadData & J_LEFT) {
            // Move the background to the left by 1 pixels
            scroll_bkg(-1, 0);
        }

        // When the D-Pad Up is pressed
        if (joypadData & J_UP) {
            // Move the background to the up by 1 pixels
            scroll_bkg(0, -1);
        }

        // When the D-Pad Down is pressed
        if (joypadData & J_DOWN) {
            // Move the background to the down by 1 pixels
            scroll_bkg(0, 1);
        }

        // Wait for VBlank
        wait_vbl_done();
    }
}