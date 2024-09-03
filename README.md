# lith

Lith is a library of tools for C++, aimed at making simple, Python-ish programs
easier to write and more intuitive. Think of it like Boost, if Boost was made to
a lower standard of quality.

The utility libraries provided by lith are described below.

## `lith::print`

A library which makes more things explicitly printable via any method derived
from `std::ostream`. This library provides no public functions, only overloads;
the modified behaviors are as follows:

`std::pair`: Prints with format `<$(first) : $(last)>`.

Any iterable type: prints with format `[$(element1), $(element2), ...]`.

TODO: `std::tuple`

TODO: `std::format`

To use the overloads provided by `lith::print`, simply include in your program:

```c++
using namespace lith::print;
```

You may want to be cautious about doing this at global scope, as it will pollute
the global namespace with a number of extra overloads which may cause conflicts.

## `lith::test`

Simple unit-testing framework.

### `lith::test::test_failed`

Exception type thrown whenever an assertion fails. It's recommended to catch
this exception at your main function and return nonzero rather than letting the
exception fall through; this way things like file handles will be correctly
cleaned up.

#### `const char* test_failed::what()`

Returns some useful information about the failure.

### `lith::test::testcase`

Test case class. 

#### `testcase::testcase(const std::string& name)`

Test case constructor. It is recommended to use test cases with RAII by making a
default scope for each test case, like so:

```c++
using namespace lith::test;

int main(int, char**) {
    {
        testcase tc("my test");
        // Assertions here...
    }
}
```

#### `void testcase::fail(std::string msg = "")`
Prints a standard message to stderr optionally followed by `msg`, then throws
`test_failed`.

#### `void testcase::assertEqual(T a, U b, std::string msg = "")`

Checks whether `a` and `b` are equal according to their `==` operator. Does not
compile if T and U are not equality-comparable. If `a` and `b` are not equal,
prints a standard message to stderr optionally followed by `msg`, then throws
`test_failed`.

#### `void testcase::assertLess(T a, U b, std::string msg = "")`

Checks whether `a` is less than `b` are equal according to their `<` operator.
Does not compile if T and U are not less-than-comparable. If `a` is not less
than `b`, prints a standard message to stderr optionally followed by `msg`, then
throws `test_failed`.
