#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "stdint.h"
#include "structs.h"

struct graphic_rgb{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct graphic_pixel {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t padding;
};

void graphic_init(struct GraphicConfig* config);
void graphic_draw_pixel(int x, int y, struct graphic_rgb *rgb);
int graphic_get_horizontal_resolution();
int graphic_get_vertical_resolution();
#endif
