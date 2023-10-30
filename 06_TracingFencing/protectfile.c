#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


int remove(const char *pathname) {
    if (strstr(pathname, "PROTECT")) {
        errno = 1024;
        return -1;
    }
    int (*original_remove)(const char*) = dlsym(RTLD_NEXT, "remove");
    return original_remove(pathname);
}
