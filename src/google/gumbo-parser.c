#include <dirent.h>
#include <google/gumbo-parser.h>
#include <gumbo.h>
#include <stdio.h>
#include <stdlib.h>

static bool parseFile(const char *fileName) {
    FILE *file = fopen(fileName, "re");
    if (!file) {
        return false;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(file_size + 1);
    if (!buffer) {
        fclose(file);
        return false;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        fclose(file);
        free(buffer);
        return false;
    }

    buffer[file_size] = '\0'; // Null-terminate the buffer.

    GumboOutput *output = gumbo_parse(buffer);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    free(buffer);
    fclose(file);
    return true;
}

bool benchmarkGumbo(char *inputDirectory) {
    DIR *dir = opendir(inputDirectory);
    if (dir) {
        char fileLocation[1024];

        struct dirent *ent = (readdir(dir), readdir(dir), readdir(dir));
        while (ent != NULL) {
            snprintf(fileLocation, sizeof(fileLocation), "%s%s", inputDirectory,
                     ent->d_name);
            if (!parseFile(fileLocation)) {
                printf("Failed to parse file %s\n", fileLocation);
                return false;
            }

            ent = readdir(dir);
        }
    } else {
        printf("Incorrect input directory!\n");
        return false;
    }

    return true;
}
