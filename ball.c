//
// Created by Guy Wilks on 2/4/22.
//

#include "ball.h"
#include <stdlib.h>
#include "paddle.h"
#include "main.h"
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

Q9_6 compute_path(ball_t* ball){
    Q9_6 frame_1;
    frame_1 = Q9_6_div((ball->vx < 0 ? (ball->x_pos-20) : (GameWidth - ball->x_pos - BallWidth)), ball->vx);
    return compute_ypos(ball->y_pos, ball->vy, frame_1);
}


Q9_6 compute_xpos(Q9_6 x_n, Q9_6 vx, Q9_6 f){
    return x_n + Q9_6_mul(vx, f);
}

Q9_6 compute_ypos(Q9_6 y_n, Q9_6 vy, Q9_6 f){
    return y_n + Q9_6_mul(vy, f);
}

void ball_advance(){
    if(BALL.x_pos > GameWidth - 20){
        left_score++;
        ball_init();
        paddles_init();
        return;
    }else if(BALL.x_pos < 20){
        right_score++;
        ball_init();
        paddles_init();
        return;
    }
    BALL.x_pos += BALL.vx;
    BALL.y_pos += BALL.vy;
    if(BALL.y_pos >= SINT_TO_Q9_6(GameHeight) || BALL.y_pos <= 0){
        BALL.vy = Q9_6_neg(BALL.vy);
        BALL.y_pos += Q9_6_mul(BALL.y_pos >= SINT_TO_Q9_6(GameHeight) ? -1 : 1,
                               (sint16_to_Q9_6(GameHeight) - BALL.y_pos));
    }
    if(BALL.x_pos >= GameWidth - 30 &&
        (paddle_right.y <= BALL.y_pos) &&
        (paddle_right.y >= (BALL.y_pos - (8*paddle_height)))){
        BALL.vx = Q9_6_neg(BALL.vx);
        BALL.vx -= SINT_TO_Q9_6(1);

    }
    if(BALL.x_pos <= 30 &&
       (paddle_left.y <= BALL.y_pos) &&
       (paddle_left.y >= (BALL.y_pos - (8*paddle_height)))){
        BALL.vx = Q9_6_neg(BALL.vx);
        BALL.vx += SINT_TO_Q9_6(1);
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
