#include <stdio.h>
#include <stdlib.h>
#include "uptime.h"

#define UPTIME_PATH "/proc/uptime" 



int get_uptime(Uptime_s *uptime)
{
    FILE *f = fopen(UPTIME_PATH, "r");
    if (!f)
    {
        return -1;
    }

    double uptime_seconds, idle_seconds;
    fscanf(f, "%lf %lf", &uptime_seconds, &idle_seconds);
    fclose(f);

    uptime->seconds = uptime_seconds;
    uptime->idle = idle_seconds;

    return 0;
}
