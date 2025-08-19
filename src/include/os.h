#ifndef OS_H
#define OS_H

typedef struct {
    char* name;
    char* pretty_name;
    char* ansi_color;
} OsInfo_s;

int get_os_info(OsInfo_s *os_info);

#endif
