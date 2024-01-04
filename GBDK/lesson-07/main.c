// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the space aliens program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "GBDK_Constants.h"
#include "MetaSprites.c"
#include "SpaceAliens.c"
#include "Background.c"

typedef enum {
    SPLASH,
    START,
    GAME,
    GAME_OVER
} screen_t;

// Splash scene
screen_t splash() {
    // User input
    uint8_t joypadData;
    screen_t next_screen = GAME;

    // Time
    unsigned int timeCounter = 0;

    // Display
    printf("\n\n\n\n\n");
    printf("   MT Game Studios");
    printf("        Presents");
    printf("\n\n\n\n\n\n");
    printf("    Space Aliens");

    DISPLAY_ON;

    // Game Loop
    while(1) {
        // Get D-Pad input
        joypadData = joypad();

        // When START button is pressed
        if (joypadData & J_START) {
            return next_screen;
        }

        // Move even if START button is not pressed after 2 seconds
        timeCounter++;
        if (timeCounter > (3 * 60)) {
            return next_screen;
        }

        // Wait until end of the frame
        wait_vbl_done();
    }
}

// Game scene
screen_t game() {
    // User input
    uint8_t joypadData;

    // Check if A button is single pressed
    bool aButtonJustPressed = false;
    bool aButtonStillPressed = false;

    // Registers for sound
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

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
        joypadData = joypad();

        // When left D-Pad is pressed
        if (joypadData & J_LEFT) {
            // Move sprite in the index 0 by (x, y) (-1, 0)
            scroll_meta_sprite(0, -1, 0);
            shipXPosition -= 1;
            if (shipXPosition < 8) {
                shipXPosition = 8;
                move_meta_sprite(0, 8, FIXED_Y_POSITION_OF_SHIP);
            }
        }

        // When right D-Pad is pressed
        if (joypadData & J_RIGHT) {
            // Move sprite in the index 0 by (x, y) (+1, 0)
            scroll_meta_sprite(0, 1, 0);
            shipXPosition += 1;
            if (shipXPosition > SCREEN_WIDTH - 8) {
                shipXPosition = SCREEN_WIDTH - 8;
                move_meta_sprite(0, (uint8_t)(SCREEN_WIDTH - 8), FIXED_Y_POSITION_OF_SHIP);
            }
        }

        // When A button is pressed
        if (joypadData & J_A) {
            if (aButtonJustPressed == true) {
                aButtonStillPressed = true;
            } else {
                aButtonJustPressed = true;
                // Play sound
                NR10_REG = 0x16;
                NR11_REG = 0x82;
                NR12_REG = 0x69;
                NR13_REG = 0x59;
                NR14_REG = 0xC6;
            }
        }
        else {
            aButtonJustPressed = false;
            aButtonStillPressed = false;
        }

        // Scroll the background
        scroll_bkg(0, -1);

        // Wait for VBlank
        wait_vbl_done();
    }
}


// Main function
void main() {
    // Current screen, defaults to Title
    screen_t current_screen = SPLASH;

    // Registers
    NR52_REG = 0x80;
    NR50_REG = 0x77;
    NR51_REG = 0xFF;

    while (1) {
        if (current_screen == SPLASH) {
            current_screen = splash();
        }
        else if (current_screen == START) {
            printf("Start");
            // current_screen = start();
        }
        else if (current_screen == GAME) {
            current_screen = game();
        }
        else if (current_screen == GAME_OVER) {
            printf("Game Over");
            // current_screen = game_over();
        }
    }
}
