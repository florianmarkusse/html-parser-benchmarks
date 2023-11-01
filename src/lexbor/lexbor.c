#include <dirent.h>
#include <lexbor/core/fs.h>
#include <lexbor/html/html.h>

#include "lexbor/lexbor.h"

static bool parseFile(lxb_char_t *fileName) {
    size_t html_len;
    lxb_char_t *html = lexbor_fs_file_easy_read(fileName, &html_len);
    if (html == NULL) {
        return false;
    }

    lxb_html_document_t *document = lxb_html_document_create();
    if (document == NULL) {
        return false;
    }

    lxb_status_t status = lxb_html_document_parse(document, html, html_len);
    if (status != LXB_STATUS_OK) {
        return false;
    }

    lxb_html_document_destroy(document);
    lexbor_free(html);

    return true;
}

bool benchmarkLexbor(char *inputDirectory) {
    DIR *dir = opendir(inputDirectory);
    if (dir) {
        char fileLocation[1024];

        struct dirent *ent = (readdir(dir), readdir(dir), readdir(dir));
        while (ent != NULL) {
            snprintf(fileLocation, sizeof(fileLocation), "%s%s", inputDirectory,
                     ent->d_name);
            if (!parseFile((lxb_char_t *)fileLocation)) {
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
