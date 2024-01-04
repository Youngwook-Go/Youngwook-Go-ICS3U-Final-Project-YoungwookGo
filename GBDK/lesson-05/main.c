// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the space aliens program for the GameBoy

#include <stdio.h>
#include <gb/gb.h>

#include "GBDK_Constants.h"
#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "Background.c"

void main() {
    // Keep track of meta sprite position
    const int FIXED_Y_POSITION_OF_SHIP = 144;
    int shipXPosition = 76;
    int shipYPosition = FIXED_Y_POSITION_OF_SHIP;

    // Load spritesheet reference
    set_sprite_data(0, 16, SpaceAliens);

    // Load sprites for meta sprite
    set_meta_sprite_tile(0, 1, 2, 3, 4);

    // Move meta sprite on screen
    move_meta_sprite(0, shipXPosition, shipYPosition);

    // Set background tile sheet
    set_bkg_data(0, 16, SpaceAliens); // set_bkg_data(0, 43, SpaceAliens);

    // Load tiles from the tile map called BackgroundMap
    set_bkg_tiles(0, 0, 20, 36, Background);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game Loop
    while (1) {
        // Get D-Pad input
        switch (joypad()) {
            case J_LEFT:
                // Move sprite in the index 0 by (x, y), (-1, 0)
                scroll_meta_sprite(0, -1, 0);
                shipXPosition -= 1;
                if (shipXPosition < 8) {
                    shipXPosition = 8;
                    move_meta_sprite(0, 8, FIXED_Y_POSITION_OF_SHIP);
                }
                break;
            case J_RIGHT:
                // Move sprite in the index 0 by (x, y), (1, 0)
                scroll_meta_sprite(0, 1, 0);
                shipXPosition += 1;
                if (shipXPosition > SCREEN_WIDTH - 8) {
                    shipXPosition = SCREEN_WIDTH - 8;
                    move_meta_sprite(0, (uint8_t)(SCREEN_WIDTH - 8), FIXED_Y_POSITION_OF_SHIP);
                }
                break;
            default:
                break;
        }

        // Scroll the background
        scroll_bkg(0, -1);

        // Wait for VBlank
        wait_vbl_done();
    }
}
