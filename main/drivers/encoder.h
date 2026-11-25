#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>

void encoder_init(void);
int encoder_read(void);
bool encoder_button_pressed(void);

#endif