//
// Created by Guy Wilks on 2/6/22.
//

#ifndef PONG_PADDLE_H
#define PONG_PADDLE_H
#include <Q9_6.h>
#include <vram.h>

#define PADDLE_HEIGHT ((uint8_t)4)


typedef enum paddle_side_e {PADDLE_LEFT, PADDLE_RIGHT} paddle_side_t;

typedef struct paddle_s{
    Q9_6 y;
    paddle_side_t side;
} paddle_t;

extern paddle_t paddle_left;
extern paddle_t paddle_right;
uint8_t paddle_get_left_input(void);
uint8_t paddle_get_right_input(void);
void paddles_init(void);
void paddle_draw(void);
void paddle_movement(void);
void score_draw(void);
void clear_TXBL(void);
#endif //PONG_PADDLE_H
