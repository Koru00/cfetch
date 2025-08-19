#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ram.h"
#include "cpu.h"
#include "uptime.h"
#include "os.h"
#include "hostname.h"
#include "color.h"

// Function to print a separator line based on the longest label
void print_separator(size_t width) {
    for (size_t i = 0; i < width; i++) {
        printf("=");
    }
    printf("\n");
}

// Function to format uptime into hours and minutes
void print_uptime(const Uptime_s* uptime) {
    long total_minutes = uptime->seconds / 60;
    long hours = total_minutes / 60;
    long minutes = total_minutes % 60;
    printf("%-12s: %ld hours, %ld minutes\n", "Uptime", hours, minutes);
}

int main(int argc, char *argv[]) {
    // Initialize structures
    RamInfo_s ram_info = {0};
    CpuInfo_s cpu_info = {0};
    Uptime_s uptime = {0};
    OsInfo_s os_info = {0};
    char* user_hostname = NULL;
    char* username = NULL;

    // Get username from environment
    username = getenv("USER");
    if (!username) {
        fprintf(stderr, "Error: Failed to retrieve username\n");
        username = "Unknown"; // Fallback if USER env variable is not set
    }

    // Get system information with error checking
    if (get_ram_info(&ram_info) != 0) {
        fprintf(stderr, "Error: Failed to retrieve RAM information\n");
        exit(EXIT_FAILURE);
    }

    if (get_cpu_info(&cpu_info) != 0) {
        fprintf(stderr, "Error: Failed to retrieve CPU information\n");
        exit(EXIT_FAILURE);
    }

    if (get_uptime(&uptime) != 0) {
        fprintf(stderr, "Error: Failed to retrieve uptime information\n");
        exit(EXIT_FAILURE);
    }

    if (get_os_info(&os_info) != 0) {
        fprintf(stderr, "Error: Failed to retrieve OS information\n");
        exit(EXIT_FAILURE);
    }

    user_hostname = get_user_hostname();
    if (!user_hostname) {
        fprintf(stderr, "Error: Failed to retrieve hostname\n");
        exit(EXIT_FAILURE);
    }

    const char *color = (argc >= 2) ? get_color(argv[1]) : RESET_COLOR;
    if (color == NULL)
    {
        color = RESET_COLOR;
    }

    // Print formatted system information with consistent spacing
    printf("%s", color);
    print_separator(30);
    printf("%-12s: %s\n", "User", username);
    printf("%-12s: %s\n", "Hostname", user_hostname);
    printf("%-12s: %s\n", "OS", os_info.pretty_name);
    print_uptime(&uptime);
    printf("%-12s: %ld/%ld MB\n", "RAM", ram_info.available/1000, ram_info.total/1000);
    printf("%-12s: %s\n", "CPU", cpu_info.model_name);
    print_separator(30);
    printf("%s\n", RESET_COLOR);

    // Clean up allocated memory
    free(os_info.name);
    free(os_info.pretty_name);
    free(os_info.ansi_color);
    free(user_hostname);

    return EXIT_SUCCESS;
}
