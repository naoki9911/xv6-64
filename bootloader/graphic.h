#ifndef GRAPHIC_H
#define GRAPHIC_H
#include "structs.h"
EFI_STATUS GetGraphicMode(IN EFI_HANDLE ImageHandle, OUT struct GraphicConfig *graphic_config);
#endif
