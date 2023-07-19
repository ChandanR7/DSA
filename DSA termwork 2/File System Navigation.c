#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void traverseFileSystem(char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Unable to open directory: %s\n", path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        printf("%s\n", entry->d_name);

        char newPath[1000];
        sprintf(newPath, "%s/%s", path, entry->d_name);
        traverseFileSystem(newPath);
    }

    closedir(dir);
}

int main() {
    char path[1000];
    printf("Enter the directory path: ");
    scanf("%s", path);

    printf("File system traversal:\n");
    traverseFileSystem(path);

    return 0;
}
