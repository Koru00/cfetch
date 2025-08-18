#ifndef RAM_H
#define RAM_H

typedef struct {
    long total;
    long available;
} RamInfo_s;

int get_ram_info(RamInfo_s *ram_info);

#endif
