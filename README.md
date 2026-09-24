*This project has been created as part of the 42 curriculum by elim-hon.*

# ft_printf

## Description

`ft_printf` is a re-implementation of the C standard library function `printf()`, written from scratch as part of the 42 curriculum. Its purpose is to deepen understanding of variadic functions in C, manual output buffering via `write()`, and structured parsing of format strings.

Unlike the original `printf`, this version does not implement internal buffering — every character is written directly to file descriptor `1` using `write()`. The function returns the total number of characters printed, exactly like the libc version.

The library is compiled into a static archive `libftprintf.a`, which can be linked against any C program that needs formatted output without depending on the standard library's `printf`.

### Goal

Reproduce the behaviour of `printf()` for the following conversion specifiers:

| Specifier | Description |
|-----------|-------------|
| `%c` | Prints a single character. |
| `%s` | Prints a string, following the common C convention. |
| `%p` | Prints a `void *` pointer in hexadecimal format. |
| `%d` | Prints a signed decimal (base 10) integer. |
| `%i` | Prints an integer in base 10. |
| `%u` | Prints an unsigned decimal (base 10) integer. |
| `%x` | Prints a number in lowercase hexadecimal. |
| `%X` | Prints a number in uppercase hexadecimal. |
| `%%` | Prints a literal percent sign. |

In addition, the bonus part is fully implemented:

- Handles any combination of the flags `-`, `0`, and `.` (dot) with a field minimum width, under all conversions.
- Handles the additional flags `#`, ` ` (space), and `+`.
- Supports `*` for width and precision (values taken from the argument list).

### Overview

The project is small but structured: `int ft_printf(const char *, ...)`, a parser, a dispatcher, and one converter per conversion class (text vs. numeric). All state for a single conversion — the current format cursor, the `va_list`, the parsed flags, the width and precision, and the running output count — is in one struct, `t_ft_printf`. Every helper receives only this struct as an argument, which keeps function signatures uniform, avoids passing `va_list` around, and makes each function easy to test and to keep within the 42 Norm (≤ 25 lines, ≤ 5 functions per file, ≤ 4 parameters).

## Instructions

### Compilation

The project uses a `Makefile` that compiles the sources into a static library and links the bundled `libft` (which is compiled by its own `Makefile` first).

```bash
make          # build libftprintf.a
make clean    # remove object files
make fclean   # remove object files and libftprintf.a
make re       # rebuild from scratch
```
The archive is created at the root of the repository using `ar rcs`, as required by the subject. The compiler is `cc` with `-Wall -Wextra -Werror`.

### Usage

1. Include the header in your C files:

```c
#include "ft_printf.h"
```

2. Compile your program with the archive:

```bash
cc -Wall -Wextra -Werror main.c libftprintf.a -I. -o my_program
```

3. Call the function exactly like the standard `printf`:

```c
#include "ft_printf.h"

int main(void)
{
    int n = ft_printf("Hello, %s! You are %d years old.\n", "World", 42);
    ft_printf("Printed %d characters.\n", n);
    return (0);
}
```

### Project layout

```text
.
├── Makefile
├── README.md
├── ft_printf.h
├── ft_printf.c              # entry point, dispatcher, state init
├── ft_printf_parser.c       # flag / width / precision / specifier parsing
├── ft_printf_text.c         # %c, %s, %p, %%
├── ft_printf_num.c          # %d, %i, %u, %x, %X
├── ft_printf_num_utils.c    # sign, prefix, padding logic for numbers
├── ft_printf_base.c         # base conversion helpers
├── ft_printf_utils.c        # low-level write wrappers and padding
└── libft/                   # allowed libft library, compiled by its own Makefile
```

### Behaviour notes

- The function returns `-1` when the format string is `NULL`, matching glibc.
- Passing `NULL` to `%s` prints `(null)` when no precision is given, and an empty string when the precision is smaller than the length of `"(null)"` - this reproduces glibc's behaviour.
- Passing `NULL` to `%p` prints `(nil)` on Linux.
- Width and flags for `%%` are ignored, matching the original `printf`.

## Technical choices

### Data structure: `t_ft_printf`

All the state needed to handle a single conversion is stored in one struct:

```c
typedef struct s_ft_printf
{
    const char  *format;     /* cursor into the format string */
    va_list     ap;          /* the variadic argument list */
    int         count;       /* total characters printed so far */
    int         minus;       /* '-' flag */
    int         zero;        /* '0' flag */
    int         hash;        /* '#' flag */
    int         space;       /* ' ' flag */
    int         plus;        /* '+' flag */
    int         width;       /* minimum field width */
    int         dot;         /* '.' present */
    int         precision;   /* precision value */
    char        spec;        /* the conversion specifier */
}   t_ft_printf;
```

Why this design:
- One argument per helper. Every parser step and every converter receives only `t_ft_printf *p`. This keeps signatures short, avoids `va_list` being passed around (which on some ABIs is an array type and cannot be passed by value safely), and makes it trivial to add new state fields later.
- Output count is centralised. Instead of returning an int from each helper, every helper adds directly to `p->count`. The top-level function therefore has a single source of truth for the return value.
- Format cursor is shared. `p->format` advances as the parser reads flags, width, precision, and specifier. The main loop resumes exactly where parsing stopped.

### Algorithm

The flow inside `ft_printf` is:

1. Guard against `NULL` format -> return `-1`. 
2. Initialise the state (`format`, `count`, `va_start`).
3. Loop over the format string:
    - If the current character is not `%`, write it with `ft_printf_putchar_count` and advance.
    - If it is `%`, advance past it, reset the parsed fields, then call `ft_printf_parse` followed by `ft_printf_arg`.
4. `ft_printf_parse` runs four small steps in order:
    - `ft_printf_parse_flags` - consumes any sequence of `-0# +`.
    - `ft_printf_parse_width` - reads either `*` (from `va_arg`) or a decimal width. A negative width from `*` sets `minus` and flips the sign.
    - `ft_printf_parse_precision` - if the next character is `.`, sets `dot` and reads either `*` or a decimal precision.
    - `ft_printf_parse_spec` - stores the conversion character in `p->spec` and advances.
5. `ft_printf_arg` dispatches on `p->spec` and calls the correct converter.
6. Each converter fills `p->count` and returns.
7. The main loop continues until the end of the format string; `va_end` is called and the count is returned.

Numeric conversions (`%d`, `%i`, `%u`, `%x`, `%X`) all funnel into `ft_printf_number` amd then `ft_printf_number_all`. That function:
- Converts the value to a string using `ft_printf_uitoa_base`.
- Computes the number of significant digits (`digits`), taking into account the special case `%.0d` with value `0` (which produces no digits).
- Computes the number of precision zeros (`zeros`).
- Computes the sign/prefix length via `ft_printf_extra_len`.
- Emits, in order: optional left padding (spaces), sign, prefix (`0x`/`0X`), optional zero padding, precision zeros, the digits, and optional right padding (spaces).

This matches the original `printf` order for every combination of flags, width, and precision.

### Why this is extensible

Adding a new conversion means:
1. Add its specifier to `ft_printf_arg`.
2. Write a converter that fills `p->count`.
3. Add its prototype to `ft_printf.h`.

No other file needs to change. This is why the subject emphasises "well-structured and extensible code".

## Resources

### Classic references

- `man 3 printf` - the reference implementation and its exact behaviour.
- `man 3 stdarg` - `va_list`, `va_start`, `va_arg`, `va_end`, `va_copy`.
- `man 2 write` - the only allowed output primitive.
- C11 standard (ISO/IEC 9899:2011), §7.21.6 — formal definition of formatted output. The core conversion rules (flags, width, precision, specifiers) are specified in §7.21.6.1 (fprintf); §7.21.6.3 defines printf as fprintf applied to stdout, which is exactly what ft_printf mimics.
- [cppreference: printf](https://en.cppreference.com/c/io/fprintf) — a very readable summary of every flag, width, precision, and length modifier.
- [GNU C Library manual](https://sourceware.org/glibc/manual/) — the glibc behaviour that the subject's testers compare against.

### AI Usage

AI tools were used as a learning aid and a documentation assistant during this project, in the following ways:
- Concept clarification. Understanding how `va_list` behaves when passed around, why passing it by value to a helper can be unsafe, and how `va_arg` reads arguments in promoted types (`char` → `int`, `float` → `double`).
- Behavioural reference. Confirming the exact glibc behaviour of edge cases such as `%.3s` with a `NULL` argument (empty string when precision < 6, `(null)` otherwise), `(nil)` for `NULL` pointers with `%p`, and the fact that width and flags are ignored for `%%`.
- Testing help. Generating a comprehensive and commented out `int main(void)` that compares `ft_printf` against the system `printf` across many flag/width/precision combinations, including the edge cases listed above.
- `README` drafting. Producing the structure and wording of this document.

AI was not used to write the converters' core logic blindly. Every function was reviewed, tested, and adjusted to match the observed behaviour of the system `printf`.

### Testing

```c
#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	int	x;

	printf("=== %%c ===\n");
	printf("printf:    [%c]\n", 'A');
	ft_printf("ft_printf: [%c]\n", 'A');
	printf("printf:    [%5c]\n", 'A');
	ft_printf("ft_printf: [%5c]\n", 'A');
	printf("printf:    [%-5c]\n", 'A');
	ft_printf("ft_printf: [%-5c]\n", 'A');
	printf("printf:    [%05c]\n", 'A');
	ft_printf("ft_printf: [%05c]\n", 'A');
	printf("printf:    [%c]\n", 0);
	ft_printf("ft_printf: [%c]\n", 0);
	printf("=== %%s ===\n");
	printf("printf:    [%s]\n", "hello");
	ft_printf("ft_printf: [%s]\n", "hello");
	printf("printf:    [%10s]\n", "hello");
	ft_printf("ft_printf: [%10s]\n", "hello");
	printf("printf:    [%-10s]\n", "hello");
	ft_printf("ft_printf: [%-10s]\n", "hello");
	printf("printf:    [%.3s]\n", "hello");
	ft_printf("ft_printf: [%.3s]\n", "hello");
	printf("printf:    [%10.3s]\n", "hello");
	ft_printf("ft_printf: [%10.3s]\n", "hello");
	printf("printf:    [%-10.3s]\n", "hello");
	ft_printf("ft_printf: [%-10.3s]\n", "hello");
	printf("printf:    [%s]\n", (char *)NULL);
	ft_printf("ft_printf: [%s]\n", (char *)NULL);
	printf("printf:    [%10s]\n", "");
	ft_printf("ft_printf: [%10s]\n", "");
	printf("printf:    [%.0s]\n", "hello");
	ft_printf("ft_printf: [%.0s]\n", "hello");
	printf("=== %%p ===\n");
	x = 42;
	printf("printf:    [%p]\n", (void *)&x);
	ft_printf("ft_printf: [%p]\n", (void *)&x);
	printf("printf:    [%20p]\n", (void *)&x);
	ft_printf("ft_printf: [%20p]\n", (void *)&x);
	printf("printf:    [%-20p]\n", (void *)&x);
	ft_printf("ft_printf: [%-20p]\n", (void *)&x);
	printf("printf:    [%p]\n", (void *)NULL);
	ft_printf("ft_printf: [%p]\n", (void *)NULL);
	printf("printf:    [%20p]\n", (void *)NULL);
	ft_printf("ft_printf: [%20p]\n", (void *)NULL);
	printf("=== %%d and %%i ===\n");
	printf("printf:    [%d]\n", 0);
	ft_printf("ft_printf: [%d]\n", 0);
	printf("printf:    [%d]\n", 42);
	ft_printf("ft_printf: [%d]\n", 42);
	printf("printf:    [%d]\n", -42);
	ft_printf("ft_printf: [%d]\n", -42);
	printf("printf:    [%i]\n", 42);
	ft_printf("ft_printf: [%i]\n", 42);
	printf("printf:    [%i]\n", -42);
	ft_printf("ft_printf: [%i]\n", -42);
	printf("printf:    [%d]\n", INT_MAX);
	ft_printf("ft_printf: [%d]\n", INT_MAX);
	printf("printf:    [%d]\n", INT_MIN);
	ft_printf("ft_printf: [%d]\n", INT_MIN);
	printf("printf:    [%+d]\n", 42);
	ft_printf("ft_printf: [%+d]\n", 42);
	printf("printf:    [%+d]\n", -42);
	ft_printf("ft_printf: [%+d]\n", -42);
	printf("printf:    [% d]\n", 42);
	ft_printf("ft_printf: [% d]\n", 42);
	printf("printf:    [% d]\n", -42);
	ft_printf("ft_printf: [% d]\n", -42);
	printf("printf:    [%10d]\n", 42);
	ft_printf("ft_printf: [%10d]\n", 42);
	printf("printf:    [%-10d]\n", 42);
	ft_printf("ft_printf: [%-10d]\n", 42);
	printf("printf:    [%010d]\n", 42);
	ft_printf("ft_printf: [%010d]\n", 42);
	printf("printf:    [%010d]\n", -42);
	ft_printf("ft_printf: [%010d]\n", -42);
	printf("printf:    [%+010d]\n", 42);
	ft_printf("ft_printf: [%+010d]\n", 42);
	printf("printf:    [%.5d]\n", 42);
	ft_printf("ft_printf: [%.5d]\n", 42);
	printf("printf:    [%.5d]\n", -42);
	ft_printf("ft_printf: [%.5d]\n", -42);
	printf("printf:    [%.0d]\n", 0);
	ft_printf("ft_printf: [%.0d]\n", 0);
	printf("printf:    [%10.5d]\n", 42);
	ft_printf("ft_printf: [%10.5d]\n", 42);
	printf("printf:    [%-10.5d]\n", 42);
	ft_printf("ft_printf: [%-10.5d]\n", 42);
	printf("printf:    [%+10.5d]\n", 42);
	ft_printf("ft_printf: [%+10.5d]\n", 42);
	printf("printf:    [% 10.5d]\n", 42);
	ft_printf("ft_printf: [% 10.5d]\n", 42);
	printf("printf:    [%010.5d]\n", 42);
	ft_printf("ft_printf: [%010.5d]\n", 42);
	printf("=== %%u ===\n");
	printf("printf:    [%u]\n", 0);
	ft_printf("ft_printf: [%u]\n", 0);
	printf("printf:    [%u]\n", 42);
	ft_printf("ft_printf: [%u]\n", 42);
	printf("printf:    [%u]\n", UINT_MAX);
	ft_printf("ft_printf: [%u]\n", UINT_MAX);
	printf("printf:    [%10u]\n", 42);
	ft_printf("ft_printf: [%10u]\n", 42);
	printf("printf:    [%-10u]\n", 42);
	ft_printf("ft_printf: [%-10u]\n", 42);
	printf("printf:    [%010u]\n", 42);
	ft_printf("ft_printf: [%010u]\n", 42);
	printf("printf:    [%.5u]\n", 42);
	ft_printf("ft_printf: [%.5u]\n", 42);
	printf("printf:    [%.0u]\n", 0);
	ft_printf("ft_printf: [%.0u]\n", 0);
	printf("printf:    [%10.5u]\n", 42);
	ft_printf("ft_printf: [%10.5u]\n", 42);
	printf("printf:    [%-10.5u]\n", 42);
	ft_printf("ft_printf: [%-10.5u]\n", 42);
	printf("=== %%x ===\n");
	printf("printf:    [%x]\n", 0);
	ft_printf("ft_printf: [%x]\n", 0);
	printf("printf:    [%x]\n", 42);
	ft_printf("ft_printf: [%x]\n", 42);
	printf("printf:    [%x]\n", 255);
	ft_printf("ft_printf: [%x]\n", 255);
	printf("printf:    [%x]\n", UINT_MAX);
	ft_printf("ft_printf: [%x]\n", UINT_MAX);
	printf("printf:    [%#x]\n", 0);
	ft_printf("ft_printf: [%#x]\n", 0);
	printf("printf:    [%#x]\n", 42);
	ft_printf("ft_printf: [%#x]\n", 42);
	printf("printf:    [%#x]\n", 255);
	ft_printf("ft_printf: [%#x]\n", 255);
	printf("printf:    [%10x]\n", 42);
	ft_printf("ft_printf: [%10x]\n", 42);
	printf("printf:    [%-10x]\n", 42);
	ft_printf("ft_printf: [%-10x]\n", 42);
	printf("printf:    [%010x]\n", 42);
	ft_printf("ft_printf: [%010x]\n", 42);
	printf("printf:    [%#010x]\n", 42);
	ft_printf("ft_printf: [%#010x]\n", 42);
	printf("printf:    [%.5x]\n", 42);
	ft_printf("ft_printf: [%.5x]\n", 42);
	printf("printf:    [%.0x]\n", 0);
	ft_printf("ft_printf: [%.0x]\n", 0);
	printf("printf:    [%10.5x]\n", 42);
	ft_printf("ft_printf: [%10.5x]\n", 42);
	printf("printf:    [%-10.5x]\n", 42);
	ft_printf("ft_printf: [%-10.5x]\n", 42);
	printf("printf:    [%#10.5x]\n", 42);
	ft_printf("ft_printf: [%#10.5x]\n", 42);
	printf("=== %%X ===\n");
	printf("printf:    [%X]\n", 0);
	ft_printf("ft_printf: [%X]\n", 0);
	printf("printf:    [%X]\n", 42);
	ft_printf("ft_printf: [%X]\n", 42);
	printf("printf:    [%X]\n", 255);
	ft_printf("ft_printf: [%X]\n", 255);
	printf("printf:    [%X]\n", UINT_MAX);
	ft_printf("ft_printf: [%X]\n", UINT_MAX);
	printf("printf:    [%#X]\n", 0);
	ft_printf("ft_printf: [%#X]\n", 0);
	printf("printf:    [%#X]\n", 42);
	ft_printf("ft_printf: [%#X]\n", 42);
	printf("printf:    [%#X]\n", 255);
	ft_printf("ft_printf: [%#X]\n", 255);
	printf("printf:    [%10X]\n", 42);
	ft_printf("ft_printf: [%10X]\n", 42);
	printf("printf:    [%-10X]\n", 42);
	ft_printf("ft_printf: [%-10X]\n", 42);
	printf("printf:    [%010X]\n", 42);
	ft_printf("ft_printf: [%010X]\n", 42);
	printf("printf:    [%#010X]\n", 42);
	ft_printf("ft_printf: [%#010X]\n", 42);
	printf("printf:    [%.5X]\n", 42);
	ft_printf("ft_printf: [%.5X]\n", 42);
	printf("printf:    [%.0X]\n", 0);
	ft_printf("ft_printf: [%.0X]\n", 0);
	printf("printf:    [%10.5X]\n", 42);
	ft_printf("ft_printf: [%10.5X]\n", 42);
	printf("printf:    [%-10.5X]\n", 42);
	ft_printf("ft_printf: [%-10.5X]\n", 42);
	printf("printf:    [%#10.5X]\n", 42);
	ft_printf("ft_printf: [%#10.5X]\n", 42);
	printf("=== %%%% ===\n");
	printf("printf:    [%%]\n");
	ft_printf("ft_printf: [%%]\n");
	printf("printf:    [%5%]\n");
	ft_printf("ft_printf: [%5%]\n");
	printf("printf:    [%-5%]\n");
	ft_printf("ft_printf: [%-5%]\n");
	printf("printf:    [%05%]\n");
	ft_printf("ft_printf: [%05%]\n");
	printf("=== mixed ===\n");
	printf("printf:    [%d %s %x]\n", 42, "hi", 255);
	ft_printf("ft_printf: [%d %s %x]\n", 42, "hi", 255);
	printf("printf:    [%+d %-10s %#X]\n", -42, "hello", 255);
	ft_printf("ft_printf: [%+d %-10s %#X]\n", -42, "hello", 255);
	printf("printf:    [%5.3d %10.5s %08x]\n", 42, "hello", 255);
	ft_printf("ft_printf: [%5.3d %10.5s %08x]\n", 42, "hello", 255);
	printf("printf:    [%*d]\n", 10, 42);
	ft_printf("ft_printf: [%*d]\n", 10, 42);
	printf("printf:    [%-*d]\n", 10, 42);
	ft_printf("ft_printf: [%-*d]\n", 10, 42);
	printf("printf:    [%*d]\n", -10, 42);
	ft_printf("ft_printf: [%*d]\n", -10, 42);
	printf("printf:    [%.*d]\n", 5, 42);
	ft_printf("ft_printf: [%.*d]\n", 5, 42);
	printf("printf:    [%*.*d]\n", 10, 5, 42);
	ft_printf("ft_printf: [%*.*d]\n", 10, 5, 42);
	printf("printf:    [%-*.*d]\n", 10, 5, 42);
	ft_printf("ft_printf: [%-*.*d]\n", 10, 5, 42);
	printf("printf:    [%*.*s]\n", 10, 3, "hello");
	ft_printf("ft_printf: [%*.*s]\n", 10, 3, "hello");
	return (0);
}
```