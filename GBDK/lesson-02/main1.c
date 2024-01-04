// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the space aliens program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>

#include "SpaceAliens.c"

int main() {
    // Load spritesheet reference
    set_sprite_data(0, 16, SpaceAliens);

    // Load sprites for meta sprite
    set_sprite_tile(0, 15);

    // Move meta sprite on screen
    move_sprite(0, 88, 78);

    // Load more sprites
    set_sprite_tile(1, 5);
    set_sprite_tile(2, 10);

    // Move the sprites
    move_sprite(1, 8, 144);
    move_sprite(2, 64, 64);

    SHOW_SPRITES;
    return 0;
}
