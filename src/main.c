
#include "flo/flo-html-parser.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

#define for_str_split(iter, src, split_by)                                     \
    for (str macro_var(src_) = (src),                                          \
             (iter) = str_pop_first_split(*macro_var(src_), split_by),         \
             macro_var(split_by_) = split_by;                                  \
                                                                               \
         str_valid(macro_var(src_));                                           \
                                                                               \
         (iter) = str_pop_first_split(&macro_var(src_), macro_var(split_by_)))

#define FLO_HTML_DEFER(start, end)                                             \
    for (int(_i_) = (start, 0); !(_i_); ((_i_) += 1), end)

struct timespec start;
struct timespec end;
double cpu_time_used = NAN;

void startBenchmark(const char *libraryName) {
    printf("Starting benchmark for library %s\n", libraryName);
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void endBenchmark() {
    clock_gettime(CLOCK_MONOTONIC, &end);
    cpu_time_used =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    double cpu_time_used_ms = cpu_time_used * 1000;
    printf("Elapsed Time: %.2f milliseconds\n\n", cpu_time_used_ms);
}

#define FLO_HTML_BENCHMARK_2(libraryName)                                      \
    FLO_HTML_DEFER_WITH_RETURN(startBenchmark(libraryName), endBenchmark())

#define FLO_HTML_BENCHMARK(libraryName)                                        \
    FLO_HTML_DEFER(startBenchmark(libraryName), endBenchmark())

int main() {
    int result = 0;
    FLO_HTML_BENCHMARK("flo/html-parser") {
        if (!benchmark()) {
            printf("Benchmark failed!\n");
            result = -1;
        }
    }

    return result;
}
