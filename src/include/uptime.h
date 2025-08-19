#ifndef UPTIME_H
#define UPTIME_H

typedef struct {
    double seconds;
    double idle;
} Uptime_s;

int get_uptime(Uptime_s *uptime);

#endif // !UPTIME_H
