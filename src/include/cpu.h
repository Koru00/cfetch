#ifndef CPU_H
#define CPU_H

typedef struct {
    char model_name[128];
    int cores;
    int logical_processors;
    float frequency_mhz;
} CpuInfo_s;

int get_cpu_info(CpuInfo_s *cpu_info);

#endif // !CPU_H
