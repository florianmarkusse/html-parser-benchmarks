# C HTML-PARSER BENCHMARKS

This repository contains benchmarks of C-based HTML-parsers.

Results

| library | speed (of 10 runs) | comments |
|:-------:|:-----:|:--------:|
| `flo/html-parser` | `873ms` | Single Arena for all files  |
| `lexbor/lexbor` | `1874ms` | |
| `flo/html-parser` | `2135ms` | New Arena for every new file |
