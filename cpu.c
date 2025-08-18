#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#define CPUINFO_PATH "/proc/cpuinfo"

int get_cpu_info(CpuInfo_s *cpu_info)
{
    if (!cpu_info) return -1; // safety check

    cpu_info->model_name[0] = '\0';
    cpu_info->cores = 0;
    cpu_info->logical_processors = 0;
    cpu_info->frequency_mhz = 0.0f;

    FILE* cpuinfo = fopen(CPUINFO_PATH, "r");
    if (!cpuinfo) return -1;

    char line[256];
    int found_model = 0;
    int found_cores = 0;
    int found_siblings = 0;
    int found_freq = 0;

    while (fgets(line, sizeof(line), cpuinfo))
    {
        if (!found_model && sscanf(line, "model name : %[^\n]", cpu_info->model_name) == 1) {
            found_model = 1;
        }
        if (!found_cores && sscanf(line, "cpu cores : %d", &cpu_info->cores) == 1) {
            found_cores = 1;
        }
        if (!found_siblings && sscanf(line, "siblings : %d", &cpu_info->logical_processors) == 1) {
            found_siblings = 1;
        }
        if (!found_freq && sscanf(line, "cpu MHz : %f", &cpu_info->frequency_mhz) == 1) {
            found_freq = 1;
        }

        if (found_model && found_cores && found_siblings && found_freq) {
            break; // stop when all values are found
        }
    }

    fclose(cpuinfo);

    // if any field was not found, return -1
    if (!found_model || !found_cores || !found_siblings || !found_freq) return -2;

    return 0;
}
