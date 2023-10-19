#ifndef UTIL_DECORATOR_H
#define UTIL_DECORATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#define FLO_HTML_DEFER(start, end)                                             \
    for (int(_i_) = (start, 0); !(_i_); ((_i_) += 1), end)

#define FLO_HTML_WITH_DIRECTORY(dir, dirPath)                                  \
    for ((dir) = opendir(directoryPath); ((dir) != NULL);                      \
         (dir) = (closedir(dir), NULL))

#define FLO_HTML_WITH_DIRECTORY_ELSE(dir, dirPath)                             \
    dir = opendir(dirPath);                                                    \
    if (dir)                                                                   \
        for (; ((dir) != NULL); (dir) = (closedir(dir), NULL))

#define FLO_HTML_FILE_NAME_ITERATOR(dir, fileLocation)                         \
    for (struct dirent *ent = (readdir(dir), readdir(dir), readdir(dir));      \
         ent != NULL && snprintf(fileLocation, sizeof(fileLocation), "%s%s",   \
                                 INPUTS_DIR, ent->d_name);                     \
         (ent = readdir(dir)))

#ifdef __cplusplus
}
#endif

#endif
