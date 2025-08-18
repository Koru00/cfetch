#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ram.h"

#define MEMINFO_PATH "/proc/meminfo"

int get_ram_info(RamInfo_s *ram_info)
{
    if (!ram_info) return -1; // safety check

    ram_info->total = 0;
    ram_info->available = 0;
    
    FILE* meminfo = fopen(MEMINFO_PATH, "r");
    if (!meminfo)
    {
        return -1;
    }

    char line[256];
    int found_total = 0;      // initialize to 0
    int found_available = 0;  // initialize to 0

    while (fgets(line, sizeof(line), meminfo))
    {
        if (!found_total && sscanf(line, "MemTotal: %ld kB", &ram_info->total) == 1) {
            found_total = 1;
        }

        if (!found_available && sscanf(line, "MemAvailable: %ld kB", &ram_info->available) == 1) {
            found_available = 1;
        }

        if (found_total && found_available) {
            break; // stop only when both are found
        }
    }
 
    fclose(meminfo);

    // return -1 if we failed to read any of the values
    if (!found_total || !found_available) return -2;

    return 0;
}

