// data.h
#ifndef DATA_H
#define DATA_H

#include <stdint.h>


typedef struct {
    uint16_t keycode;
    bool shift;
    bool alt;
    bool special;
} KeyData;

typedef struct {
    KeyData input;
    KeyData output;
} Transform;

#endif // DATA_H