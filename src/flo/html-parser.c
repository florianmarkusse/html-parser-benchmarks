#include "flo/flo-html-parser.h"
#include <dirent.h>
#include <flo/html-parser.h>
#include <sys/mman.h>

#define CAP 1 << 27

static bool parseFile(flo_String fileLocation, flo_Arena scratch) {
    flo_html_Dom *dom = flo_html_createDomFromFile(fileLocation, &scratch);
    if (dom == NULL) {
        return false;
    }

    return true;
}

bool benchmarkFloHtmlParserSingleArena(char *inputDirectory) {
    char *begin = mmap(NULL, CAP, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (begin == MAP_FAILED) {
        FLO_PRINT_ERROR("Failed to allocate memory!\n");
        return -1;
    }

    flo_Arena arena = flo_createArena(begin, CAP);

    void *jmp_buf[5];
    if (__builtin_setjmp(jmp_buf)) {
        if (munmap(arena.beg, arena.cap) == -1) {
            FLO_PRINT_ERROR("Failed to unmap memory from arena!\n"
                            "Arena Details:\n"
                            "  beg: %p\n"
                            "  end: %p\n"
                            "  cap: %td\n"
                            "Zeroing Arena regardless.",
                            arena.beg, arena.end, arena.cap);
        }
        FLO_PRINT_ERROR("OOM/overflow in arena!\n");
        return -1;
    }
    arena.jmp_buf = jmp_buf;

    DIR *dir = opendir(inputDirectory);
    if (dir) {
        char fileLocation[1024];

        struct dirent *ent = (readdir(dir), readdir(dir), readdir(dir));
        while (ent != NULL) {
            snprintf(fileLocation, sizeof(fileLocation), "%s%s", inputDirectory,
                     ent->d_name);
            if (!parseFile(FLO_STRING_LEN(fileLocation, strlen(fileLocation)),
                           arena)) {
                printf("Failed to parse file %s\n", fileLocation);
                if (munmap(arena.beg, arena.cap) == -1) {
                    FLO_PRINT_ERROR("Failed to unmap memory from arena!\n"
                                    "Arena Details:\n"
                                    "  beg: %p\n"
                                    "  end: %p\n"
                                    "  cap: %td\n"
                                    "Zeroing Arena regardless.",
                                    arena.beg, arena.end, arena.cap);
                }
                return false;
            }

            ent = readdir(dir);
        }
    } else {
        printf("Incorrect input directory!\n");
        if (munmap(arena.beg, arena.cap) == -1) {
            FLO_PRINT_ERROR("Failed to unmap memory from arena!\n"
                            "Arena Details:\n"
                            "  beg: %p\n"
                            "  end: %p\n"
                            "  cap: %td\n"
                            "Zeroing Arena regardless.",
                            arena.beg, arena.end, arena.cap);
        }
        return false;
    }

    if (munmap(arena.beg, arena.cap) == -1) {
        FLO_PRINT_ERROR("Failed to unmap memory from arena!\n"
                        "Arena Details:\n"
                        "  beg: %p\n"
                        "  end: %p\n"
                        "  cap: %td\n"
                        "Zeroing Arena regardless.",
                        arena.beg, arena.end, arena.cap);
    }

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

            char *begin = mmap(NULL, CAP, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            if (begin == MAP_FAILED) {
                FLO_PRINT_ERROR("Failed to allocate memory!\n");
                return -1;
            }

            flo_Arena arena = flo_createArena(begin, CAP);

            void *jmp_buf[5];
            if (__builtin_setjmp(jmp_buf)) {
                if (munmap(arena.beg, arena.cap) == -1) {
                    FLO_PRINT_ERROR("Failed to unmap memory from arena!\n"
                                    "Arena Details:\n"
                                    "  beg: %p\n"
                                    "  end: %p\n"
                                    "  cap: %td\n"
                                    "Zeroing Arena regardless.",
                                    arena.beg, arena.end, arena.cap);
                }
                FLO_PRINT_ERROR("OOM/overflow in arena!\n");
                return -1;
            }
            arena.jmp_buf = jmp_buf;

            if (!parseFile(FLO_STRING_LEN(fileLocation, strlen(fileLocation)),
                           arena)) {
                printf("Failed to parse file %s\n", fileLocation);
                return false;
            }
            if (munmap(arena.beg, arena.cap) == -1) {
                FLO_PRINT_ERROR("Failed to unmap memory from arena!\n"
                                "Arena Details:\n"
                                "  beg: %p\n"
                                "  end: %p\n"
                                "  cap: %td\n"
                                "Zeroing Arena regardless.",
                                arena.beg, arena.end, arena.cap);
            }
            ent = readdir(dir);
        }
    } else {
        printf("Incorrect input directory!\n");
        return false;
    }

    return true;
}
