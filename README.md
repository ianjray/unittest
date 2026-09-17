# unittest

A small Bash test runner for C/C++ programs.

`unittest` builds and runs test programs using directives embedded in their source files.
Expected output can either be stored in a separate file or embedded directly in the source.

The runner is intentionally simple: compilation and teardown commands are interpreted by Bash, while test arguments are parsed using `xargs` syntax without shell expansion.

## Usage

```sh
unittest path/to/test.c
```

Multiple tests can be supplied:

```sh
unittest *.c
```

The runner exits successfully when all tests pass.
It exits unsuccessfully if a test fails, an expected failure unexpectedly passes, teardown fails, or test metadata is invalid.

## Directives

| Directive    | Purpose                                          | Optional                  |
| ------------ | ------------------------------------------------ | ------------------------- |
| `@unittest`  | Command used to compile the test                 | No                        |
| `@uut`       | Test executable filename                         | Yes                       |
| `@args`      | Arguments passed to the test executable          | Yes                       |
| `@xfail`     | Mark the test as an expected failure             | Yes                       |
| `@expected`  | Expected output file or start of embedded output | Yes                       |
| `@expected.` | End of embedded expected output                  | With embedded `@expected` |
| `@teardown`  | Command executed after the test                  | Yes                       |

Directives are written in C-style comments:

```c
//@unittest clang
/*
@args --verbose
*/
```

### `@unittest`

Specifies the command used to compile the test.

The source filename and output filename are supplied to the command as positional arguments `$1` and `$2`.
For example:

```text
@unittest clang
```

is effectively invoked as:

```sh
clang "$source" -o "$uut"
```

The command may contain arbitrary shell syntax:

```text
@unittest date ; rm -f foo ; clang
```

### `@uut`

Specifies the filename of the test executable.

```text
@uut example
```

If omitted, the executable name is derived from the source filename.
For example `path/to/example.c` produces `example`.

### `@args`

Specifies arguments passed to the test executable.
Arguments use **`xargs` word splitting and quoting syntax**.
For example:

```text
@args 3 "2 .5" \" 1\\ $HOME
```

Expands to:

```text
3
2 .5
"
1\
$HOME
```

Malformed `@args` syntax, such as an unterminated quote, is reported as an error.

### `@expected`

Specifies expected output as named file:

```text
@expected expected.txt
```

Or, alternatively, in-line:

```text
@expected
hello
world
@expected.
```

Output is compared using:

```sh
diff -up
```

The test program's exit status is checked independently of its output.
Consequently, a test can report both an exit-status failure and an output mismatch.

### `@xfail`

Marks a test as an expected failure:

```text
@xfail
```

A failing test is reported as `XFAIL` and does not cause the test run to fail.

A test that unexpectedly succeeds is reported as `XPASS` and causes the test run to fail.

```c
//@unittest clang
//@xfail
int main(void)
{
    // Reported as XPASS.
}
```

### `@teardown`

Specifies an optional command to execute after the test:

```text
@teardown rm data
```

The command is interpreted by Bash.
Teardown is executed regardless of whether the test passes, fails, is XFAIL, or is XPASS.
A teardown failure causes the overall test run to fail.

## Results

A successful test is reported as:

```text
PASS:   example.c
```

An ordinary failure:

```text
FAIL:   example.c (exit 1)
```

A test with incorrect output:

```text
FAIL:   example.c (output mismatch)
```

If both occur:

```text
FAIL:   example.c (exit 1, output mismatch)
```

Expected failures are reported as:

```text
XFAIL:  example.c (exit 1)
```

and unexpected successes as:

```text
XPASS:  example.c
```

When the expected output differs, `diff` output is displayed before the test verdict.

## Example

A complete test might look like this:

```c
/*
@unittest clang
@args 3 "2 .5"
@expected
	arg 0 './example'
	arg 1 '3'
	arg 2 '2 .5'
@expected.
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("\targ %d '%s'\n", i, argv[i]);
    }
}
```

Running it:

```sh
$ unittest example.c
PASS:	example.c
```

## Test Organization

The repository's own tests are organized in sub-directories by purpose.
The Makefile exercises both successful and intentionally unsuccessful invocations.

## Installation

Place `unittest` in your `PATH`.

## Requirements

* Bash 4+
* `diff`
* `xargs`
