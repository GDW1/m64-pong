//
// Created by Guy Wilks on 2/6/22.
//

#include "paddle.h"
#include <int.h>
#include <vram.h>
#include <Q9_6.h>
#include <controller.h>
#include "patterns.h"
#include <screen.h>
#include <mapache64_zero_page.h>
#include "backend/headers/Q9_6.h"
#include "main.h"
#include "ball.h"
paddle_t paddle_left;
paddle_t paddle_right;
uint8_t paddle_draw_init;

void paddles_init(void){
    paddle_draw_init = 0;
    paddle_left.y=SINT_TO_Q9_6(108);
    paddle_left.side=PADDLE_LEFT;
    paddle_right.y=SINT_TO_Q9_6(148);
    paddle_right.side=PADDLE_RIGHT;
}

uint8_t paddle_get_left_input(void){
    if(CONTROLLER_1&CONTROLLER_UP_MASK){
        return CONTROLLER_UP_MASK;
    }else if(CONTROLLER_1&CONTROLLER_DOWN_MASK){
        return CONTROLLER_DOWN_MASK;
    }
    return 0;
}

uint8_t paddle_get_right_input(void){
    if(CONTROLLER_2&CONTROLLER_UP_MASK) {
        return CONTROLLER_UP_MASK;
    }else if(CONTROLLER_2&CONTROLLER_DOWN_MASK){
        return CONTROLLER_DOWN_MASK;
    }
    return 0;
}
void paddle_draw_init_f(void) {
    uint8_t i;
    for(i = 0; i < (PADDLE_HEIGHT); i++){ // OBM 0, 1, 2, 3 are for left paddle
        OBM[0+i].pattern_config = white_pattern_pmfa;
        OBM[0+i].x = 30;
        OBM[0+i].y = Q9_6_to_sint8(paddle_left.y)+(8*i);
        OBM[0+i].color = WHITE_C_MASK;
    }
    for(i = 0; i < (PADDLE_HEIGHT); i++){ // OBM 4, 5, 6, 7 are for left paddle
        OBM[PADDLE_HEIGHT+i].pattern_config = white_pattern_pmfa;
        OBM[PADDLE_HEIGHT+i].x = (GameWidth - 30);
        OBM[PADDLE_HEIGHT+i].y = Q9_6_to_sint8(paddle_right.y)+(8*i);
        OBM[PADDLE_HEIGHT+i].color = WHITE_C_MASK;
    }
    paddle_draw_init = 1;
}

void paddle_draw(void){
    uint8_t i;
    if(paddle_draw_init == 0){
        paddle_draw_init_f();
    }
    for(i = 0; i < (PADDLE_HEIGHT); i++){ // OBM 0, 1, 2, 3 are for left paddle
        OBM[0+i].y = Q9_6_to_sint8(paddle_left.y)+(8*i);
    }
    for(i = 0; i < (PADDLE_HEIGHT); i++){ // OBM 4, 5, 6, 7 are for left paddle
        OBM[PADDLE_HEIGHT+i].y = Q9_6_to_sint8(paddle_right.y)+(8*i);
    }
}

void paddle_movement(void){
    if(paddle_get_left_input() == CONTROLLER_UP_MASK && (paddle_left.y) > SINT_TO_Q9_6(0)){
        paddle_left.y -= SINT_TO_Q9_6(6);
    } else if(paddle_get_left_input() == CONTROLLER_DOWN_MASK && paddle_left.y < SINT_TO_Q9_6(GameHeight - (8*PADDLE_HEIGHT))){
        paddle_left.y += SINT_TO_Q9_6(6);
    }
//    if(paddle_get_right_input() == CONTROLLER_UP_MASK && paddle_right.y > SINT_TO_Q9_6(0)){
//        paddle_right.y -= SINT_TO_Q9_6(6);
//    } else if(paddle_get_right_input() == CONTROLLER_DOWN_MASK && paddle_right.y < SINT_TO_Q9_6(GameHeight - (8*PADDLE_HEIGHT))){
//        paddle_right.y += SINT_TO_Q9_6(6);
//    }
    paddle_right.y = BALL.y_pos;
}

void score_draw(void){
    TXBL[5][5] = COLOR_SELECT_MASK |'P';
    TXBL[5][6] = COLOR_SELECT_MASK |'1';
    TXBL[5][8] = COLOR_SELECT_MASK |'0' + left_score;

    TXBL[5][25] = COLOR_SELECT_MASK |'P';
    TXBL[5][26] = COLOR_SELECT_MASK |'2';
    TXBL[5][28] = COLOR_SELECT_MASK |'0' + right_score;
}

void clear_TXBL(void){
    uint8_t i, j;
    for(i = 0; i < 32; i++){
        for(j = 0; j < 30; j++)
        {
            TXBL[i][j] = 0x00;
        }
    }
}