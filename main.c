
// ==================== main.c ==================== //
// Follow this file template to implement your game //
// ================================================ //

#define SIM 1 // change value depending if running simulation or not

// ================================ //
#pragma code-name ("CODE")
#pragma bss-name ("BSS")

#include <int.h>
#include <vram.h>
#include <stop.h>
#include <Q9_6.h>
#include <mapache64_zero_page.h>
#include <controller.h>
#include <screen.h>
#include "ball.h"
#include "paddle.h"
#include "patterns.h"
#include <controller.h>
// run once on startup

uint8_t left_score;
uint8_t right_score;


void reset(void) {
    clear_TXBL();
    paddles_init();
    ball_init();
    left_score = 0;
    right_score = 0;
}

// run 60 times a second
void do_logic(void) {
    paddle_movement();
    ball_advance();
    if(left_score > 9 || right_score > 9){
        reset();
    }
}

// run after do_logic and once gpu is idle
void fill_vram(void) {
    load_patterns();
    paddle_draw();
    ball_draw();
    score_draw();
}
