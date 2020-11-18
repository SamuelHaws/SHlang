# SHlang

SHlang (a silly name that is short for Samuel Haws language) is a heuristic programming language, currently in development.
This readme will serve as an unavoidably informal living document for the grammar/usage of the language and its lexer/parser/compiler.

Lexer originally written in C before I realized that handling array resizing and memory allocation entirely myself would probably lead to worse performance than if I had just bundled in all of the bells and whistles of C++, so... here we are.

Please note that this is my first attempt at writing a compiler, and I am by no means a C++ expert. If you should decide to look through this repo, and see some glaring issue or design flaw, please submit an issue or pull request so that I can improve and learn. Thanks.
