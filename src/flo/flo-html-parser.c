
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

bool benchmark() {
    flo_html_Arena arena = flo_html_newArena(1U << 27U);
    void *jmp_buf[5];
    if (__builtin_setjmp(jmp_buf)) {
        flo_html_destroyArena(&arena);
        FLO_HTML_PRINT_ERROR("OOM in arena!\n");
        return false;
    }
    arena.jmp_buf = jmp_buf;

    DIR *dir;
    FLO_HTML_WITH_DIRECTORY_ELSE(dir, INPUTS_DIR) {
        char fileLocation[1024];
        FLO_HTML_FILE_NAME_ITERATOR(dir, fileLocation) {
            if (!parseFile(FLO_HTML_S_LEN(fileLocation, strlen(fileLocation)),
                           arena) != USER_SUCCESS) {
                printf("Failed to parse file!!\n");
                flo_html_destroyArena(&arena);
                return false;
            }
        }
    }
    else {
        printf("Incorrect input directory!\n");
        flo_html_destroyArena(&arena);
        return false;
    }

    flo_html_destroyArena(&arena);

    return true;
}
