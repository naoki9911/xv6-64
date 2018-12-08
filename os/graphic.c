#include "graphic.h"
#include "stdint.h"
#include "structs.h"

struct GraphicConfig graphic_config;
void graphic_init(struct GraphicConfig* config)
{
  graphic_config.frame_base = config->frame_base;
  graphic_config.frame_size = config->frame_size;
  graphic_config.horizontal_resolution = config->horizontal_resolution;
  graphic_config.vertical_resolution = config->vertical_resolution;
  graphic_config.pixels_per_scan_line = config->pixels_per_scan_line;
  struct graphic_rgb black = {0,0,0};
  for(int x=0;x<graphic_config.horizontal_resolution;x++){
    for(int y=0;y<graphic_config.vertical_resolution;y++){
      graphic_draw_pixel(x,y,&black);
    }
  }
}

void graphic_draw_pixel(int x, int y, struct graphic_rgb *rgb)
{
  struct graphic_pixel *pixel = (struct graphic_pixel *)((x + y*graphic_config.pixels_per_scan_line)*sizeof(struct graphic_pixel) + graphic_config.frame_base);
  pixel->red = rgb->red;
  pixel->green = rgb->green;
  pixel->blue = rgb->blue;
}

int graphic_get_horizontal_resolution(){
  return graphic_config.horizontal_resolution;
}
int graphic_get_vertical_resolution(){
  return graphic_config.vertical_resolution;
}
