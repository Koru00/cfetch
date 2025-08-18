#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os.h"

#define OS_RELEASE_PATH "/etc/os-release"

int get_os_info(OsInfo_s *os_info)
{
    FILE *f = fopen(OS_RELEASE_PATH, "r");
    if (!f)
    {
        return -1;
    }

    os_info->name = NULL;
    os_info->pretty_name = NULL;
    os_info->ansi_color = NULL;

    char line[256];
    int name_found = 0;
    int pretty_name_found = 0;
    int ansi_color_found = 0;

    while (fgets(line, sizeof(line), f))
    {
        char* eq_pos = strchr(line, '=');
        if (!eq_pos) continue;

        *eq_pos = '\0';
        char *key = line;
        char *value = eq_pos + 1;

        // Skip leading whitespace in value
        while (*value == ' ' || *value == '\t') value++;

        // Handle quoted values: if starts with ", read until closing "
        int quoted = 0;
        if (*value == '"') {
            quoted = 1;
            value++;  // Skip opening quote
        }

        // Find the end of the value
        char *end = value;
        while (*end && *end != '\n' && *end != '\r' && (!quoted || *end != '"')) {
            end++;
        }
        *end = '\0';  // Null-terminate the value

        // Allocate and copy if it's a key we care about
        size_t len = strlen(value);
        if (!name_found && strcmp(key, "NAME") == 0) {
            os_info->name = malloc(len + 1);
            if (!os_info->name) {
                fclose(f);
                return -3;  // Allocation failure
            }
            strcpy(os_info->name, value);
            name_found = 1;
        } else if (!pretty_name_found && strcmp(key, "PRETTY_NAME") == 0) {
            os_info->pretty_name = malloc(len + 1);
            if (!os_info->pretty_name) {
                fclose(f);
                return -3;
            }
            strcpy(os_info->pretty_name, value);
            pretty_name_found = 1;
        } else if (!ansi_color_found && strcmp(key, "ANSI_COLOR") == 0) {
            os_info->ansi_color = malloc(len + 1);
            if (!os_info->ansi_color) {
                fclose(f);
                return -3;
            }
            strcpy(os_info->ansi_color, value);
            ansi_color_found = 1;
        }

        if (name_found && pretty_name_found && ansi_color_found) {
            break;
        }
    }
 
    fclose(f);

    if (!name_found || !pretty_name_found || !ansi_color_found) {
        free(os_info->name);
        free(os_info->pretty_name);
        free(os_info->ansi_color);
        os_info->name = NULL;
        os_info->pretty_name = NULL;
        os_info->ansi_color = NULL;
        return -2;
    }
    return 0; 
}
