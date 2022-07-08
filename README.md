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
  - Chapter 19 Challenge 1 (flexible array members)
  - Chapter 19 Challenge 2 (constant strings)
* Interpreter features:
  - Get [the tests](https://github.com/munificent/craftinginterpreters/tree/master/test) working
  - Replace the REPL's rudimentary string reading with either GNU Readline or Linenoise
  - Replace the argument parsing in main.c with [argp](https://www.gnu.org/software/libc/manual/html_node/Argp.html)
  - Replace string concatenations with [ropes](https://en.wikipedia.org/wiki/Rope_(data_structure)).
  - In addition to supporting Ropes, let's look into lock-free thread-safe, reference-counted memory management for strings in a heap that is
    separate from the garbage collected heap.
    * Might be faster because it avoids some of the time-complexity of GC.
    * Ropes are a simple case for reference counting since there can be no cycles.
    * Separating out heaps for non-cyclical data structures means that the GC'ed heap is smaller, which might improve performance on the GC'ed heap.
    * Final decisions should be based on profiling, not on the above hypotheses.
* Code quality:
  - There are a bunch of spots where there's the comment `// Unreachable.` If it's really unreachable, we can assert that with `assert(false)` rather than failing silently there, and then probably failing later.
* Language features:
  - Handle comparisons with NaN and Infinity in floating point numbers (throwing an error seems more friendly than
    [the IEEE 754 Standard behavior](https://en.wikipedia.org/wiki/IEEE_754)).
  - Make a decision on how to handle "truthy" and "falsey" values (do we want a stricter type system here?).
  - Use either [GNU libunistring](https://www.gnu.org/software/libunistring/) or [ICU](https://icu.unicode.org/) to support Unicode. Some notes:
    * In most cases we can store as UTF-32 as this follows the principle of least surprises (i.e. random access has predictable performance).
      We could optimize for memory usage with a variable-width format like UTF-8, but then we risk hard-to-predict performance issues on
      basic programs.
    * It's worth adding low-level support (in VM opcodes, for example) for ASCII (as it's a common case which also has fast random access) and UTF-8
      which might be worth exposing in the language (i.e. "abc"ascii, "abc"utf8, "abc"utf32).
    * We should support read/write to UTF-16 because it's needed for interoperation, but maybe not include low-level support.
    * See notes in the Crafting Compilers book after Chapter 19.
* Libraries:
  - Commonmark. Use the spec test cases from [here](https://spec.commonmark.org/).
  - JSON. Probably do this before Commonmark, since it would be useful for parsing the Commonmark test cases.
