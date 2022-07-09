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
  - Chapter 21 Challenge 1
  - Chapter 21 Challenge 2
  - Chapter 21 Challenge 3
* Interpreter features:
  - Get [the tests](https://github.com/munificent/craftinginterpreters/tree/master/test) working
  - Replace the REPL's rudimentary string reading with either GNU Readline or Linenoise
  - Replace the argument parsing in main.c with [argp](https://www.gnu.org/software/libc/manual/html_node/Argp.html)
* Optimizations:
  - Replace string concatenations with [ropes](https://en.wikipedia.org/wiki/Rope_(data_structure)).
  - In addition to supporting Ropes, let's look into lock-free thread-safe, reference-counted memory management for strings in a heap that is
    separate from the garbage collected heap.
    * Might be faster because it avoids some of the time-complexity of GC.
    * Ropes are a simple case for reference counting since there can be no cycles.
    * Separating out heaps for non-cyclical data structures means that the GC'ed heap is smaller, which might improve performance on the GC'ed heap.
    * Final decisions should be based on profiling, not on the above hypotheses.
  - Do performance analysis of hash probing algorithms in the open addressing scheme. The probing algorithms mentioned on the sidebar of
    chapter 20 are:
    * Double hashing
    * Cuckoo hashing
    * Robin Hood hashing
  - Look into fast non-cryptographic hashes (keep looking for more other than this):
    * [Pearson Hashing](
    * [xxHash](https://cyan4973.github.io/xxHash/)
    * t1ha. Rust implementation [here](https://lib.rs/crates/t1ha) but the original Github project seems to no longer exist. [This page](https://github.com/rurban/smhasher) might contain code?
    * [Meow hash](https://github.com/cmuratori/meow_hash).
* Code quality:
  - There are a bunch of spots where there's the comment `// Unreachable.` If it's really unreachable, we can assert that with `assert(false)` rather than failing silently there, and then probably failing later.
  - > You can sum the stack effects of a series of instructions to get their total effect. When you add the stack effects of the series of instructions compiled from any complete expression, it will total one. Each expression leaves one result value on the stack.

    > The bytecode for an entire statement has a total stack effect of zero. Since a statement produces no values, it ultimately leaves the stack unchanged, though it of course uses the stack while it’s doing its thing. This is important because when we get to control flow and looping, a program might execute a long series of statements. If each statement grew or shrank the stack, it might eventually overflow or underflow.

    \- Robert Nystrom in *Crafting Interpeters* [21.1](https://craftinginterpreters.com/global-variables.html#statements)

    This is a pretty big insight... and one it's useful to write assertions
    around. We wouldn't want these assertions to execute in production, but
    running tests with these assertions in place would potentially allow us
    to catch a lot of errors.

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
