// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the space aliens program for the GameBoy

#include <stdio.h>
#include <gb/gb.h>

#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "SpaceAliensBackgroundMap.c"

void main() {
    // Load spritesheet reference
    set_sprite_data(0, 15, SpaceAliens);

    // Load sprites for meta sprite
    set_meta_sprite_tile(0, 1, 2, 3, 4);

    // Move meta sprite on screen
    move_meta_sprite(0, 76, 144);

    // Set background tile sheet
    set_bkg_data(0, 16, SpaceAliens);

    // Load times from the tile map called BackgroundMap
    set_bkg_tiles(0, 0, 20, 36, SpaceAliensBackgroundMap);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game Loop
    while (1) {
        // Scroll the background
        scroll_bkg(0, -1);

        // Wait for VBlank
        wait_vbl_done();
    }
}
