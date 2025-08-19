#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 255
#endif

// Returns a newly allocated string "username@hostname" on success, NULL on failure.
// Caller must free() the returned string.
char* get_user_hostname() {
    // Get username
    struct passwd *pw = getpwuid(getuid());
    if (!pw) return NULL;
    const char *username = pw->pw_name;

    // Get hostname
    char hostname[HOST_NAME_MAX + 1];
    if (gethostname(hostname, sizeof(hostname)) != 0) return NULL;

    // Allocate enough memory for "username@hostname\0"
    size_t len = strlen(username) + 1 + strlen(hostname) + 1;
    char *result = malloc(len);
    if (!result) return NULL;

    // Combine username and hostname
    snprintf(result, len, "%s@%s", username, hostname);
    return result;
}
