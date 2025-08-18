#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "cpu.h"
#include "uptime.h"
#include "os.h"

int main(int argc, char *argv[])
{
    RamInfo_s ram_info;
    if (get_ram_info(&ram_info) != 0)
    {
        exit(EXIT_FAILURE);
    }
    CpuInfo_s cpu_info;
    if (get_cpu_info(&cpu_info) != 0)
    {
        exit(EXIT_FAILURE);
    }
    Uptime_s uptime;
    if (get_uptime(&uptime) != 0)
    {
        exit(EXIT_FAILURE);
    }
    OsInfo_s os_info;
    if (get_os_info(&os_info) != 0)
    {
        exit(EXIT_FAILURE);
    }

    printf("ram_info.total = %ld\n", ram_info.total);
    printf("ram_info.available = %ld\n", ram_info.available);

    printf("cpu_info.model_name = %s\n", cpu_info.model_name);
    printf("cpu_info.cores = %d\n", cpu_info.cores);
    printf("cpu_info.logical_processors = %d\n", cpu_info.logical_processors);
    printf("cpu_info.frequency_mhz = %f\n", cpu_info.frequency_mhz);

    printf("uptime.seconds = %lf\n", uptime.seconds);
    printf("uptime.idle = %lf\n", uptime.idle);

    printf("os_info.name = %s\n", os_info.name);
    printf("os_info.pretty_name = %s\n", os_info.pretty_name);
    printf("os_info.ansi_color = %s\n", os_info.ansi_color);

    free(os_info.name);
    free(os_info.pretty_name);
    free(os_info.ansi_color);

    return EXIT_SUCCESS;
}


/*
static void print_user_host(void) {
  // Get login name
  struct passwd *pw = getpwuid(geteuid());
  if (!pw) {
    perror("getpwuid");
    exit(EXIT_FAILURE);
  }

  // Determine hostname buffer size
  long hm = sysconf(_SC_HOST_NAME_MAX);
  if (hm < 1) hm = 256; // fallback buffer size

  char *host = malloc(hm + 1);
  if (!host) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  if (gethostname(host, hm + 1) != 0) {
    perror("gethostname");
    free(host);
    exit(EXIT_FAILURE);
  }

  printf("%s@%s\n", pw->pw_name, host);
  free(host);
}

static void print_os_info(void) {
  // Read distro info from /etc/os-release
  FILE *f = fopen("/etc/os-release", "r");
  if (!f) {
    perror("fopen /etc/os-release");
    exit(EXIT_FAILURE);
  }

  char key[64], val[256];
  while (fscanf(f, "%63[^=]=\"%255[^\"]\"%*c", key, val) == 2) {
    if (strcmp(key, "PRETTY_NAME") == 0 ||
        strcmp(key, "NAME")        == 0 ||
        strcmp(key, "VERSION")     == 0) {
      printf("%s: %s\n", key, val);
    }
  }
  fclose(f);
}

unsigned long long ram_info(struct sysinfo si,char type)
{
  if (type == 't')
  {
    return (si.totalram * si.mem_unit) / 1024 / 1024;
  }
  else if (type == 'f')
  {
    return (si.freeram  * si.mem_unit) / 1024 / 1024;
  }
  else 
  {
    exit(EXIT_FAILURE);
  }
}

static void print_sys_info(void) {
  struct sysinfo si;
  if (sysinfo(&si) != 0) {
    perror("sysinfo");
    exit(EXIT_FAILURE);
  }

  // RAM
  unsigned long long total_mb = ram_info(si, 't');
  unsigned long long free_mb  = ram_info(si, 'f');    
    printf("Total RAM: %llu MB\nFree RAM:  %llu MB\n\n",
         total_mb, free_mb);

  // Uptime
  long up = si.uptime;
  printf("Uptime: %ldd %ldh %ldm %lds\n\n",
         up / 86400,
         (up % 86400) / 3600,
         (up % 3600)  / 60,
         up % 60);

  // CPU (filtered)
  FILE *f = fopen("/proc/cpuinfo", "r");
  if (!f) {
    perror("fopen /proc/cpuinfo");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), f)) {
    if (strncmp(line, "model name", 10) == 0 ||
        strncmp(line, "cpu MHz",    7) == 0 ||
        strncmp(line, "core id",    7) == 0) {
      printf("%s", line);
    }
  }
  fclose(f);
}

static void print_kernel_info(void) {
  struct utsname u;
  if (uname(&u) != 0) {
    perror("uname");
    exit(EXIT_FAILURE);
  }
  printf("\nSystem:    %s\nNode Name: %s\nRelease:   %s\n"
         "Version:   %s\nMachine:   %s\n",
         u.sysname, u.nodename, u.release, u.version, u.machine);
}

int main(void) {
  print_user_host();
  print_sys_info();
  print_os_info();
  print_kernel_info();
  return EXIT_SUCCESS;
}
*/
