# C HTML-PARSER BENCHMARKS

This repository contains benchmarks of C-based HTML-parsers.

Results

| library | speed | comments |
|:-------:|:-----:|:--------:|
| `flo/html-parser` | `89ms` | Single Arena for all files  |
| `lexbor/lexbor` | `195ms` | |
| `flo/html-parser` | `225ms` | New Arena for every new file |
