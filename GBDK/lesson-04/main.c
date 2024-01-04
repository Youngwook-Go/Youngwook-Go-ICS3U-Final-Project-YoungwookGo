// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the space aliens program for the GameBoy

#include <stdio.h>
#include <gb/gb.h>

#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "Background.c"

void main() {
    // User input
    uint8_t joypadData;

    // Load spritesheet reference
    set_sprite_data(0, 16, SpaceAliens);

    // Load sprites for meta sprite
    set_meta_sprite_tile(0, 1, 2, 3, 4);

    // Move meta sprite on screen
    move_meta_sprite(0, 76, 120);

    // Set background tile sheet
    set_bkg_data(0, 43, SpaceAliens);

    // Load tiles from the tile map called BackgroundMap
    set_bkg_tiles(0, 0, 20, 36, Background);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game Loop
    while (1) {
        // Get D-Pad input
        joypadData = joypad();

        // When left D-Pad is pressed
        if (joypadData & J_LEFT) {
            // Move sprite in the index 0 by (x, y) (-1, 0)
            scroll_meta_sprite(0, -1, 0);
        }

        // When right D-Pad is pressed
        if (joypadData & J_RIGHT) {
            // Move sprite in the index 0 by (x, y) (+1, 0)
            scroll_meta_sprite(0, 1, 0);
        }

        // When up D-Pad is pressed
        if (joypadData & J_UP) {
            // Move sprite in the index 0 by (x, y) (0, -1)
            scroll_meta_sprite(0, 0, -1);
        }

        // When down D-Pad is pressed
        if (joypadData & J_DOWN) {
            // Move sprite in the index 0 by (x, y) (0, +1)
            scroll_meta_sprite(0, 0, 1);
        }

        // Scroll the background
        scroll_bkg(0, -1);

        // Wait for VBlank
        wait_vbl_done();
    }
}
