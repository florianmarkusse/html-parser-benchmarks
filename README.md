# C HTML-PARSER BENCHMARKS

This repository contains benchmarks of C-based HTML-parsers.

Results

| library | speed | comments |
|:-------:|:-----:|:--------:|
| [flo/html-parser](https://github.com/florianmarkusse/html-parser) | `89ms` | Single Arena for all files  |
| [lexbor/lexbor](https://github.com/lexbor/lexbor) | `195ms` | |
| [flo/html-parser](https://github.com/florianmarkusse/html-parser) | `225ms` | New Arena for every new file |
