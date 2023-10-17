
#include "flo/flo-html-parser.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

int main() {
  struct timespec start;
  struct timespec end;
  double cpu_time_used = NAN;

  clock_gettime(CLOCK_MONOTONIC, &start);
  benchmark();
  clock_gettime(CLOCK_MONOTONIC, &end);

  cpu_time_used =
      (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

  double cpu_time_used_ms = cpu_time_used * 1000;

  printf("Elapsed Time: %.2f milliseconds\n", cpu_time_used_ms);

  return 0;
}
