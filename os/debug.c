#include "debug.h"
#include "console.h"

#include "structs.h"

void debug_info_graphic(struct GraphicConfig *g_conf){
    console_puts_str("[Graphic] FrameBase:0x");
    console_puts_hex(g_conf->frame_base);
    console_puts_str("\n[Graphic] FrameSize:");
    console_puts_dec(g_conf->frame_size);
    console_puts_str("\n[Graphic] H_Reso:");
    console_puts_dec(g_conf->horizontal_resolution);
    console_puts_str("\n[Graphic] V_Reso:");
    console_puts_dec(g_conf->vertical_resolution);
    console_puts_str("\n[Graphic] PixelsPerScanLine:");
    console_puts_dec(g_conf->pixels_per_scan_line);
    console_puts_str("\n");
}
