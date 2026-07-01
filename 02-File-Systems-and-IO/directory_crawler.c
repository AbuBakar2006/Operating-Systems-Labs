#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir failed");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
        count++;
    }

    closedir(dir);

    printf("Total files: %d\n", count);

    return 0;
}
