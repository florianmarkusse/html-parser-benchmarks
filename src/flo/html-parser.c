#include "flo/flo-html-parser.h"
#include <dirent.h>
#include <flo/html-parser.h>

static bool parseFile(flo_html_String fileLocation, flo_html_Arena scratch) {
    flo_html_Dom *dom = flo_html_createDomFromFile(fileLocation, &scratch);
    if (dom == NULL) {
        return false;
    }

    return true;
}

bool benchmarkFloHtmlParserSingleArena(char *inputDirectory) {
    flo_html_Arena arena = flo_html_newArena(1U << 27U);
    void *jmp_buf[5];
    if (__builtin_setjmp(jmp_buf)) {
        flo_html_destroyArena(&arena);
        FLO_HTML_PRINT_ERROR("OOM in arena!\n");
        return false;
    }
    arena.jmp_buf = jmp_buf;

    DIR *dir = opendir(inputDirectory);
    if (dir) {
        char fileLocation[1024];

        struct dirent *ent = (readdir(dir), readdir(dir), readdir(dir));
        while (ent != NULL) {
            snprintf(fileLocation, sizeof(fileLocation), "%s%s", inputDirectory,
                     ent->d_name);
            if (!parseFile(FLO_HTML_S_LEN(fileLocation, strlen(fileLocation)),
                           arena)) {
                printf("Failed to parse file %s\n", fileLocation);
                flo_html_destroyArena(&arena);
                return false;
            }

            ent = readdir(dir);
        }
    } else {
        printf("Incorrect input directory!\n");
        flo_html_destroyArena(&arena);
        return false;
    }

    flo_html_destroyArena(&arena);

    return true;
}

bool benchmarkFloHtmlParserArenaPerFile(char *inputDirectory) {
    DIR *dir = opendir(inputDirectory);
    if (dir) {
        char fileLocation[1024];

        struct dirent *ent = (readdir(dir), readdir(dir), readdir(dir));
        while (ent != NULL) {
            snprintf(fileLocation, sizeof(fileLocation), "%s%s", inputDirectory,
                     ent->d_name);
            flo_html_Arena arena = flo_html_newArena(1U << 27U);
            void *jmp_buf[5];
            if (__builtin_setjmp(jmp_buf)) {
                flo_html_destroyArena(&arena);
                FLO_HTML_PRINT_ERROR("OOM in arena!\n");
                return false;
            }
            arena.jmp_buf = jmp_buf;
            if (!parseFile(FLO_HTML_S_LEN(fileLocation, strlen(fileLocation)),
                           arena)) {
                printf("Failed to parse file %s\n", fileLocation);
                flo_html_destroyArena(&arena);
                return false;
            }

            flo_html_destroyArena(&arena);
            ent = readdir(dir);
        }
    } else {
        printf("Incorrect input directory!\n");
        return false;
    }

    return true;
}
