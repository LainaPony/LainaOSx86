#include "vga.h"
#include <string.h>
// again ported directly from the fucking riscV alpha keep in mind this is AIDS temp code so if its broken yeah no wonder go fuck yourself :p
void run_command(const char* cmd)
{
    if (strcmp(cmd, "help") == 0) {
        vga_print("Commands: help, clear, about\n");
    }
    else if (strcmp(cmd, "clear") == 0) {
        vga_clear();
    }
    else if (strcmp(cmd, "about") == 0) {
        vga_print("LainaOSx86 kernel shell 0.1\n");
    }
    else {
        vga_print("Unknown command\n");
    }
}
