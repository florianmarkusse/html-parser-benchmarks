
#include <dirent.h>

#include "definitions.h"
#include "flo/flo-html-parser.h"
#include "util/decorator.h"

bool parseFile(flo_html_String fileLocation, flo_html_Arena scratch) {
    flo_html_ParsedHTML parsed;
    if (flo_html_fromFile(fileLocation, &parsed, &scratch) != USER_SUCCESS) {
        return false;
    }

    return true;
}

#define HTML_FILES(fileLocation)                                               \
    DIR *dir = NULL;                                                           \
    struct dirent *ent = NULL;                                                 \
    if ((dir = opendir(INPUTS_DIR)) == NULL) {                                 \
        printf("Failed to open directory: %s\n", INPUTS_DIR);                  \
        return false;                                                          \
    }                                                                          \
    ent = readdir(dir);                                                        \
    ent = readdir(dir);                                                        \
    for (ent = readdir(dir);                                                   \
         ent != NULL && snprintf(fileLocation, sizeof(fileLocation), "%s%s",   \
                                 INPUTS_DIR, ent->d_name);                     \
         (ent = readdir(dir)))

bool benchmark() {
    flo_html_Arena arena = flo_html_newArena(1U << 27U);
    void *jmp_buf[5];
    if (__builtin_setjmp(jmp_buf)) {
        flo_html_destroyArena(&arena);
        FLO_HTML_PRINT_ERROR("OOM in arena!\n");
        return false;
    }
    arena.jmp_buf = jmp_buf;

    char fileLocation[1024];
    bool parseSuccess = false;
    HTML_FILES(fileLocation) {
        if (!parseFile(FLO_HTML_S_LEN(fileLocation, strlen(fileLocation)),
                       arena)) {
            printf("Parsing DOM %s failed\n", fileLocation);
            parseSuccess = false;
        }
        parseSuccess = true;
    }

    for (DIR *dir = opendir(INPUTS_DIR), int i = 0; (dir != NULL) && !(i);
         i++, closedir(dir)) {
    }

    FLO_HTML_DEFER_DIR(INPUTS_DIR) {}

    flo_html_destroyArena(&arena);

    return true;
}
