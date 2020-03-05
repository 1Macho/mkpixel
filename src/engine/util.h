#ifndef ENGINE_UTIL_H
#define ENGINE_UTIL_H

unsigned char util_bit_value(unsigned int value, 
    unsigned char pos) {
    return (value >> pos) & 1;
}

#endif