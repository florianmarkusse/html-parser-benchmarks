# C HTML-PARSER BENCHMARKS

This repository contains benchmarks of C-based HTML-parsers.

Results

| library | speed | comments |
|:-------:|:-----:|:--------:|
| [flo/html-parser](https://github.com/florianmarkusse/html-parser) | `95ms` | Single Arena for all files  |
| [flo/html-parser](https://github.com/florianmarkusse/html-parser) | `133ms` | New Arena for every new file |
| [lexbor/lexbor](https://github.com/lexbor/lexbor) | `187ms` | |
| [google/gumbo-parser](https://github.com/google/gumbo-parser) | `950ms` | |
