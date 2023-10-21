#ifndef UTIL_DECORATOR_H
#define UTIL_DECORATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#define FLO_HTML_DEFER(start, end)                                             \
    for (int(_i_) = (start, 0); !(_i_); ((_i_) += 1), end)

#ifdef __cplusplus
}
#endif

#endif
