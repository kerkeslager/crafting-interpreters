# crafting-interpreters

This is my code for working through the amazing book [Crafting Interpreters](https://craftinginterpreters.com/).

## TODOs
* Challenges:
  - Chapter 14 Challenge 2 (allowing for more than 256 constants per chunk)
  - Chapter 14 Challenge 3 (implement and profile a few malloc/realloc/free implementations)
  - Chapter 15 Challenge 3 (expanding VM stacks) (or at least handle overflows gracefully)
  - Chapter 15 Challenge 4 (don't thrash stack within OPs) (already implemented this once, but broke the implementation when implementing Chapter 18)
  - Chapter 16 Challenge 1 (string interpolation)
  - Chapter 18 Challenge 2 (more opcodes for common operations like `>=` or `!=`).
* Interpreter features:
  - Get [the tests](https://github.com/munificent/craftinginterpreters/tree/master/test) working
  - Replace the REPL's rudimentary string reading with either GNU Readline or Linenoise
  - Replace the argument parsing in main.c with [argp](https://www.gnu.org/software/libc/manual/html_node/Argp.html)
* Code quality:
  - There are a bunch of spots where there's the comment `// Unreachable.` If it's really unreachable, we can assert that with `assert(false)` rather than failing silently there, and then probably failing later.
* Language features:
  - Handle comparisons with NaN and Infinity in floating point numbers (throwing an error seems more friendly than [the IEEE 754 Standard behavior](https://en.wikipedia.org/wiki/IEEE_754)).
  - Make a decision on how to handle "truthy" and "falsey" values (do we want a stricter type system here?).
* Libraries:
  - Commonmark. Use the spec test cases from [here](https://spec.commonmark.org/).
  - JSON. Probably do this before Commonmark, since it would be useful for parsing the Commonmark test cases.
