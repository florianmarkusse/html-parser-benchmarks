
#include <math.h>
#include <stdio.h>
#include <time.h>

#include "definitions.h"
#include "flo/flo-html-parser.h"
#include "google/gumbo-parser.h"
#include "lexbor/lexbor.h"
#include "util/decorator.h"

#define NUM_RUNS 10

struct timespec start;
struct timespec end;
double cpu_time_used = NAN;

void startBenchmark(const char *libraryName) {
    printf("Starting benchmark for %s\n", libraryName);
    clock_gettime(CLOCK_MONOTONIC, &start);
}

void endBenchmark() {
    clock_gettime(CLOCK_MONOTONIC, &end);
    cpu_time_used =
        (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    double cpu_time_used_ms = cpu_time_used * 1000 / NUM_RUNS;
    printf("Elapsed Time: %.2f milliseconds\n\n", cpu_time_used_ms);
}

#define FLO_HTML_BENCHMARK(libraryName)                                        \
    FLO_HTML_DEFER(startBenchmark(libraryName), endBenchmark())

int main() {
    FLO_HTML_BENCHMARK("flo/html-parser - Single Arena for all files") {
        for (int i = 0; i < NUM_RUNS; i++) {
            if (!benchmarkFloHtmlParserSingleArena(INPUTS_DIR)) {
                printf("Benchmark failed!\n");
            }
        }
    }

    FLO_HTML_BENCHMARK("flo/html-parser - New Arena for every file") {
        for (int i = 0; i < NUM_RUNS; i++) {
            if (!benchmarkFloHtmlParserArenaPerFile(INPUTS_DIR)) {
                printf("Benchmark failed!\n");
            }
        }
    }

    FLO_HTML_BENCHMARK("lexbor/lexbor") {
        for (int i = 0; i < NUM_RUNS; i++) {
            if (!benchmarkLexbor(INPUTS_DIR)) {
                printf("Benchmark failed!\n");
            }
        }
    }

    FLO_HTML_BENCHMARK("google/gumbo-parser") {
        for (int i = 0; i < NUM_RUNS; i++) {
            if (!benchmarkGumbo(INPUTS_DIR)) {
                printf("Benchmark failed!\n");
            }
        }
    }

    return 0;
}
