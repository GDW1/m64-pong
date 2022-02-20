//
// Created by Guy Wilks on 2/4/22.
//

#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "coordinate.h"
#include <Q9_6.h>
#include <vram.h>
#include "patterns.h"

#include "backend/headers/Q9_6.h"
#include "backend/headers/screen.h"

#define BallHeight 5
#define BallWidth 5

typedef enum direction_e {LEFT, RIGHT} direction_t;

typedef struct Ball{
    Q9_6 vx;
    Q9_6 vy;
    Q9_6 x_pos;
    Q9_6 y_pos;
} ball_t;

extern ball_t BALL;

void ball_init(void);

Q9_6 compute_path(ball_t* ball);

Q9_6 compute_xpos(Q9_6 x_n, Q9_6 vx, Q9_6 f);

Q9_6 compute_ypos(Q9_6 y_n, Q9_6 vy, Q9_6 f);

void setBall(ball_t* ball);

void ball_advance();

direction_t getDirection(void);

void ball_draw_init_f(void);

void ball_draw(void);
#endif //PONG_BALL_H