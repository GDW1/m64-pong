//
// Created by Guy Wilks on 2/4/22.
//

#include "ball.h"
#include <stdlib.h>
#include "paddle.h"
#include "main.h"
#include <vram.h>
ball_t BALL;
uint8_t ball_draw_init;
void ball_init(void){
    ball_t ball_start;
    ball_start.x_pos = SINT_TO_Q9_6(GameWidth/2);
    ball_start.y_pos = SINT_TO_Q9_6(GameHeight/2);
    ball_start.vx    = SINT_TO_Q9_6(1);//SINT_TO_Q9_6(((uint8_t)(rand())%10 - 5));
    ball_start.vy    = SINT_TO_Q9_6(2);//SINT_TO_Q9_6(((uint8_t)(rand())%10 - 5));
    setBall(&ball_start);
    ball_draw_init = 0;
}

void setBall(ball_t* ball){
    BALL.x_pos = ball->x_pos;
    BALL.y_pos = ball->y_pos;
    BALL.vx    = ball->vx;
    BALL.vy    = ball->vy;
}

void ball_advance(void){
    if(BALL.x_pos > SINT_TO_Q9_6(GameWidth - 20)){
        left_score++;
        ball_init();
        paddles_init();
        return;
    }else if(BALL.x_pos < SINT_TO_Q9_6(20)){
        right_score++;
        ball_init();
        paddles_init();
        return;
    }
    BALL.x_pos += BALL.vx;
    BALL.y_pos += BALL.vy;
    // TOP BOTTOM COLLISION
    if(BALL.y_pos >= SINT_TO_Q9_6(GameHeight) || BALL.y_pos <= 0){
        BALL.vy = Q9_6_neg(BALL.vy);
        BALL.y_pos += Q9_6_mul(BALL.y_pos >= SINT_TO_Q9_6(GameHeight) ? -1 : 1,
                               (SINT_TO_Q9_6(GameHeight) - BALL.y_pos));
    }
    // RIGHT COLLISION
    if((BALL.x_pos >= SINT_TO_Q9_6(GameWidth - 38)) && (BALL.x_pos <= SINT_TO_Q9_6(GameWidth - 36)) &&
        (paddle_right.y <= BALL.y_pos) &&
        (paddle_right.y >= (BALL.y_pos - SINT_TO_Q9_6(8*PADDLE_HEIGHT)))){
        BALL.vx = Q9_6_neg(BALL.vx);
        BALL.vx -= Q9_6_div(SINT_TO_Q9_6(1), SINT_TO_Q9_6(2));

    }
    // LEFT COLLISION
    if((BALL.x_pos <= SINT_TO_Q9_6(38)) && (BALL.x_pos >= SINT_TO_Q9_6(32)) &&
       (paddle_left.y <= BALL.y_pos) &&
       (paddle_left.y >= (BALL.y_pos - SINT_TO_Q9_6(8*PADDLE_HEIGHT)))){
        BALL.vx = Q9_6_neg(BALL.vx);
        BALL.vx += Q9_6_div(SINT_TO_Q9_6(1), SINT_TO_Q9_6(2));
    }
}

void ball_draw(void){
    if(!ball_draw_init){
        ball_draw_init_f();
    }
    // OBM object 8 is the ball
    OBM[8].x = Q9_6_to_sint8(BALL.x_pos);
    OBM[8].y = Q9_6_to_sint8(BALL.y_pos);
}


void ball_draw_init_f(void){
    // OBM object 8 is the ball
    OBM[8].pattern_config = ball_pattern_pmfa;
    OBM[8].color = MAGENTA_C_MASK;
    ball_draw_init = true;
}
