#include <stdio.h>
#include <string.h>
#include "color.h"

// Define a structure for key-value pairs
typedef struct {
    const char *name;  // Color name (e.g., "blue")
    const char *value; // Color constant (e.g., BLUE)
} ColorMap;

// Lookup table for colors
static const ColorMap color_table[] = {
    {"black", BLACK},
    {"red", RED},
    {"green", GREEN},
    {"yellow", YELLOW},
    {"blue", BLUE},
    {"magenta", MAGENTA},
    {"cyan", CYAN},
    {"white", WHITE},
    {"bright_black", BRIGHT_BLACK},
    {"bright_red", BRIGHT_RED},
    {"bright_green", BRIGHT_GREEN},
    {"bright_yellow", BRIGHT_YELLOW},
    {"bright_blue", BRIGHT_BLUE},
    {"bright_magenta", BRIGHT_MAGENTA},
    {"bright_cyan", BRIGHT_CYAN},
    {"bright_white", BRIGHT_WHITE},
    {"bg_black", BG_BLACK},
    {"bg_red", BG_RED},
    {"bg_green", BG_GREEN},
    {"bg_yellow", BG_YELLOW},
    {"bg_blue", BG_BLUE},
    {"bg_magenta", BG_MAGENTA},
    {"bg_cyan", BG_CYAN},
    {"bg_white", BG_WHITE},
    {"bg_bright_black", BG_BRIGHT_BLACK},
    {"bg_bright_red", BG_BRIGHT_RED},
    {"bg_bright_green", BG_BRIGHT_GREEN},
    {"bg_bright_yellow", BG_BRIGHT_YELLOW},
    {"bg_bright_blue", BG_BRIGHT_BLUE},
    {"bg_bright_magenta", BG_BRIGHT_MAGENTA},
    {"bg_bright_cyan", BG_BRIGHT_CYAN},
    {"bg_bright_white", BG_BRIGHT_WHITE},
    {NULL, NULL} // Sentinel to mark end of table
};

// Function to get color constant from string
const char *get_color(const char *color) {
    if (color == NULL) {
        return NULL; // Handle invalid input
    }

    // Iterate through the table
    for (int i = 0; color_table[i].name != NULL; i++) {
        if (strcmp(color, color_table[i].name) == 0) {
            return color_table[i].value;
        }
    }

    // Return NULL for unknown colors
    return NULL;
}
