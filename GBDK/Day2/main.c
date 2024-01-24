// Copyright 2023 Youngwook Go
//
// Created by: Youngwook Go
// Created on: DEC 2023
// This program is the tetris program for the GameBoy

#include <gb/gb.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <time.h>
#include <types.h>

#include "Game.c"
#include "Background.c"
#include "MetaSprites.c"

#include "SpaceAliensData.c"
#include "SpaceAliensMap.c"

typedef enum {
    START,
    GAME
} screen_t;

// Start scene
screen_t start() {
    screen_t next_screen = GAME;

    set_bkg_data(0, 215, space_aliens_data);
    set_bkg_tiles(0, 0, 20, 18, space_aliens_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);
    return next_screen;
}

screen_t game() {
    // User input
    uint8_t joypadData;

    // Check if A button is single pressed
    bool aButtonJustPressed = false;
    bool aButtonStillPressed = false;

    // Keep track of meta sprite position
    int shipXPosition = 80;
    int shipYPosition = 72;
    int shipXVelocity = 1;
    int shipYVelocity = 1;
    int shipDicection = 1;

    // Keep track of sprite position
    int enemyCounter = 0;
    int missileCounter = 0;

    // ========== Background Set Up ===========
    // Set background tile sheet
    set_bkg_data(0, 23, TileLabel);  // starting tile, number of tiles, data

    // Load times from the tile map called Background
    set_bkg_tiles(0, 0, 32, 32, Background);  // x, y, width, height, map

    // ========== Sprites Set Up ==============
    // Load sprite tile sheet
    set_sprite_data(0, 23, TileLabel);

    // Load sprites for meta sprite
    set_meta_sprite_tile(0, 1, 2, 3, 4);

    // Move meta sprite on screen
    move_meta_sprite(0, 80, 72);

    // ========== Missile Set Up ==============
    int missileLimit = 5;
    // Load sprite tile sheet
    int missiles[10][3] = {
        {5, 255, 255},
        {6, 255, 255},
        {7, 255, 255},
        {8, 255, 255},
        {9, 255, 255},
        {10, 255, 255},
        {11, 255, 255},
        {12, 255, 255},
        {13, 255, 255},
        {14, 255, 255}
    };

    // Load sprites for missiles
    for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
        set_sprite_tile(missiles[laserCounter][0], 12);
    }

    // Move the missile off screen
    for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
        move_sprite(missiles[laserCounter][0],
                    missiles[laserCounter][1],
                    missiles[laserCounter][2]);
    }

    // ========== Enemy Set Up ================
    int enemyLimit = 5;
    // Load sprite tile sheet
    int enemies[10][3] = {
        {15, 255, 255},
        {16, 255, 255},
        {17, 255, 255},
        {18, 255, 255},
        {19, 255, 255},
        {20, 255, 255},
        {21, 255, 255},
        {22, 255, 255},
        {23, 255, 255},
        {24, 255, 255}
    };

    // Load sprites for enemies
    for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
        set_sprite_tile(enemies[enemyCounter][0], 18);
    }

    // Move the enemy off screen
    for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
        move_sprite(enemies[enemyCounter][0],
                    enemies[enemyCounter][1],
                    enemies[enemyCounter][2]);
    }

    // Create first enemy
    enemies[0][1] = 80;
    enemies[0][2] = 8;
    move_sprite(enemies[0][0], enemies[0][1], enemies[0][2]);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    // Game Loop
    while (1) {
        // Get D-Pad input
        joypadData = joypad();

        // When the D-Pad Right is pressed
        if (joypadData & J_RIGHT) {
            // Move the spaceship
            set_meta_sprite_prop(0, S_FLIPX);
            scroll_meta_sprite(0, shipXVelocity, 0);
            shipXPosition = shipXPosition + shipXVelocity;
            shipDicection = 2;
            if (shipXPosition > 152) {
                shipXPosition = 152;
                move_meta_sprite(0, 152, shipYPosition);
            } else {
                // Scroll the background
                scroll_bkg(shipXVelocity * 2, 0);
                // Scroll every enemy
                for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
                    if (enemies[enemyCounter][1] < 255) {
                        enemies[enemyCounter][1] = enemies[enemyCounter][1] - 1;
                        move_sprite(enemies[enemyCounter][0],
                                    enemies[enemyCounter][1],
                                    enemies[enemyCounter][2]);
                    }
                }
                // Scroll every missile
                for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
                    if (missiles[laserCounter][1] < 255) {
                        missiles[laserCounter][1] = missiles[laserCounter][1] - 1;
                        move_sprite(missiles[laserCounter][0],
                                    missiles[laserCounter][1],
                                    missiles[laserCounter][2]);
                    }
                }
            }
        }

        // When the D-Pad Left is pressed
        if (joypadData & J_LEFT) {
            // Move the spaceship
            set_meta_sprite_prop(0, 0);
            scroll_meta_sprite(0, -shipXVelocity, 0);
            shipXPosition = shipXPosition - shipXVelocity;
            shipDicection = 4;
            if (shipXPosition < 8) {
                shipXPosition = 8;
                move_meta_sprite(0, 8, shipYPosition);
            } else {
                // Scroll the background
                scroll_bkg(-shipXVelocity * 2, 0);
                // Scroll every enemy
                for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
                    if (enemies[enemyCounter][1] < 255) {
                        enemies[enemyCounter][1] = enemies[enemyCounter][1] + 1;
                        move_sprite(enemies[enemyCounter][0],
                                    enemies[enemyCounter][1],
                                    enemies[enemyCounter][2]);
                    }
                }
                // Scroll every missile
                for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
                    if (missiles[laserCounter][1] < 255) {
                        missiles[laserCounter][1] = missiles[laserCounter][1] + 1;
                        move_sprite(missiles[laserCounter][0],
                                    missiles[laserCounter][1],
                                    missiles[laserCounter][2]);
                    }
                }
            }
        }

        // When the D-Pad Up is pressed
        if (joypadData & J_UP) {
            // Move the spaceship
            scroll_meta_sprite(0, 0, -shipYVelocity);
            shipYPosition = shipYPosition - shipYVelocity;
            shipDicection = 1;
            if (shipYPosition < 22) {
                shipYPosition = 22;
                move_meta_sprite(0, shipXPosition, 22);
            } else {
                // Scroll the background
                scroll_bkg(0, -shipYVelocity);
                // Scroll every enemy
                for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
                    enemies[enemyCounter][2] = enemies[enemyCounter][2] + 1;
                    move_sprite(enemies[enemyCounter][0],
                                enemies[enemyCounter][1],
                                enemies[enemyCounter][2]);
                }
                // Scroll every missile
                for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
                    if (missiles[laserCounter][1] < 255) {
                        missiles[laserCounter][2] = missiles[laserCounter][2] + 1;
                        move_sprite(missiles[laserCounter][0],
                                    missiles[laserCounter][1],
                                    missiles[laserCounter][2]);
                    }
                }
            }
        }

        // When the D-Pad Down is pressed
        if (joypadData & J_DOWN) {
            // Move the spaceship
            scroll_meta_sprite(0, 0, shipYVelocity);
            shipYPosition = shipYPosition + shipYVelocity;
            shipDicection = 3;
            if (shipYPosition > 152) {
                shipYPosition = 152;
                move_meta_sprite(0, shipXPosition, 152);
            } else {
                // Scroll the background
                scroll_bkg(0, shipYVelocity);
                // Scroll every enemy
                for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
                    if (enemies[enemyCounter][1] < 255) {
                        enemies[enemyCounter][2] = enemies[enemyCounter][2] - 1;
                        move_sprite(enemies[enemyCounter][0],
                                    enemies[enemyCounter][1],
                                    enemies[enemyCounter][2]);
                    }
                }
                // Scroll every missile
                for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
                    if (missiles[laserCounter][1] < 255) {
                        missiles[laserCounter][2] = missiles[laserCounter][2] - 1;
                        move_sprite(missiles[laserCounter][0],
                                    missiles[laserCounter][1],
                                    missiles[laserCounter][2]);
                    }
                }
            }
        }

        // When A button is pressed
        if (joypadData & J_A) {
            if (aButtonJustPressed == true) {
                aButtonStillPressed = true;
            } else {
                // Check to see if there are any of the [missileLimit] missiles left
                for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
                    if (missiles[laserCounter][1] >= 255) {
                        // Fire this laser
                        missiles[laserCounter][1] = shipXPosition + 4;
                        missiles[laserCounter][2] = shipYPosition - 4;
                        move_sprite(missiles[laserCounter][0],
                                    missiles[laserCounter][1],
                                    missiles[laserCounter][2]);

                        aButtonJustPressed = true;
                        // Play sound
                        NR10_REG = 0x16;
                        NR11_REG = 0x82;
                        NR12_REG = 0x69;
                        NR13_REG = 0x59;
                        NR14_REG = 0xC6;
                        break;
                    }
                }
            }
        }
        else {
            aButtonJustPressed = false;
            aButtonStillPressed = false;
        }

        // If the A button are any missiles on the screen, move them up
        for (int laserCounter = 0; laserCounter < missileLimit + 1; laserCounter++) {
            if (missiles[laserCounter][1] < 255) {
                // Move up
                missiles[laserCounter][2]--;
                move_sprite(missiles[laserCounter][0],
                            missiles[laserCounter][1],
                            missiles[laserCounter][2]);

                // Check if the missile is off the screen
                if (missiles[laserCounter][2] < 0) {
                    // Move the missile off screen
                    missiles[laserCounter][1] = 255;
                    missiles[laserCounter][2] = 255;
                    move_sprite(missiles[laserCounter][0],
                                missiles[laserCounter][1],
                                missiles[laserCounter][2]);
                }
            }
        }

        // Keep track the enemy sprite status
        for (int enemyCounter = 0; enemyCounter < enemyLimit; enemyCounter++) {
            if (enemies[enemyCounter][1] < 255) {
                // Move up
                enemies[enemyCounter][2]++;
                move_sprite(enemies[enemyCounter][0],
                            enemies[enemyCounter][1],
                            enemies[enemyCounter][2]);

                // Check if the enemy is off the screen
                if (enemies[enemyCounter][2] > 160) {
                    // Move the enemy off screen
                    enemies[enemyCounter][1] = 255;
                    enemies[enemyCounter][2] = 255;
                    move_sprite(enemies[enemyCounter][0],
                                enemies[enemyCounter][1],
                                enemies[enemyCounter][2]);
                }
            }

            // Check if the enemy is hit by the missile
            for (int laserCounter = 0; laserCounter < missileLimit; laserCounter++) {
                if (missiles[laserCounter][1] < 255) {
                    if (missiles[laserCounter][1] > enemies[enemyCounter][1] - 8 &&
                        missiles[laserCounter][1] < enemies[enemyCounter][1] + 8 &&
                        missiles[laserCounter][2] > enemies[enemyCounter][2] - 8 &&
                        missiles[laserCounter][2] < enemies[enemyCounter][2] + 8) {
                        // Move the enemy off screen
                        enemies[enemyCounter][1] = 255;
                        enemies[enemyCounter][2] = 255;
                        move_sprite(enemies[enemyCounter][0],
                                    enemies[enemyCounter][1],
                                    enemies[enemyCounter][2]);

                        // Move the missile off screen
                        missiles[laserCounter][1] = 255;
                        missiles[laserCounter][2] = 255;
                        move_sprite(missiles[laserCounter][0],
                                    missiles[laserCounter][1],
                                    missiles[laserCounter][2]);

                        // Create new enemy in random position in screen
                        // Generate random number
                        int randomXPosition = rand() % 160;
                        enemies[enemyCounter][1] = randomXPosition;
                        enemies[enemyCounter][2] = 80;
                        move_sprite(enemies[enemyCounter][0],
                                    enemies[enemyCounter][1],
                                    enemies[enemyCounter][2]);
                    }
                }
            }
        }

        // Wait for VBlank
        wait_vbl_done();
    }
}

// Main function
void main() {
    // Current screen, defaults to Title
    screen_t current_screen = START;

    while (1) {
        if (current_screen == START) {
            current_screen = start();
        } else if (current_screen == GAME) {
            current_screen = game();
        }
    }
}
