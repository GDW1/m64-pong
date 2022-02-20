#ifndef __COORDINATE_H
#define __COORDINATE_H

#include <int.h>
#include <Q9_6.h>

typedef struct coordinateS8_s {
    sint8_t x;
    sint8_t y;
} coordinateS8_t;

typedef struct coordinateU8_s {
    uint8_t x;
    uint8_t y;
} coordinateU8_t;

typedef struct coordinateQ9_6_s {
    Q9_6 x;
    Q9_6 y;
} coordinateQ9_6_t;

#endif