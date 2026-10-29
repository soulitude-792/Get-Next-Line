*This activity has been created as part of the 42 curriculum by imigdady.*

# get_next_line

## Description

**get_next_line** is a C function that reads a file descriptor and returns one line per call, including the terminating `\n` when there is one. Calling it in a loop reads the whole file, line by line, until it returns `NULL` at the end of the file or on an error.

```c
char *get_next_line(int fd);
```

The goal of the project is to learn about file descriptors, the `read` system call, static variables, and careful dynamic memory management in C.

**Behavior**
- Returns the line that was read, including the `\n` if it exists.
- Returns `NULL` when there is nothing left to read, or when an error occurs.
- Works with any `BUFFER_SIZE` value, defined at compile time with `-D BUFFER_SIZE=n`.
- Works on files and on standard input.
- Only `read`, `malloc` and `free` are used, as required by the subject.

### Project structure

| File | Content |
|------|---------|
| `get_next_line.h` | Header with the prototypes and the default `BUFFER_SIZE` |
| `get_next_line.c` | `get_next_line` and its main helpers |
| `get_next_line_utils.c` | String helpers used by `get_next_line` |

### Algorithm and justification

The function keeps the data that was read but not yet returned in a **static variable** (the stash). On each call it does the following:

1. Read `BUFFER_SIZE` bytes from the file descriptor into a temporary buffer.
2. Append the buffer to the stash.
3. Repeat steps 1 and 2 until the stash contains a `\n`, or `read` returns 0 (end of file).
4. Extract the line from the start of the stash up to and including the first `\n`.
5. Keep only what comes after the line in the stash, free the old stash, and return the line.
6. When the stash is empty and `read` returns 0, return `NULL`.

**Why this approach**
- **A static variable is needed.** `read` returns up to `BUFFER_SIZE` bytes, which can be more than one line. The extra bytes have already been consumed from the file descriptor and cannot be read again, so they must be kept between calls. A static variable keeps its value after the function returns, which makes it the natural tool for this, and it respects the subject's rule of not using global variables.
- **Reading in blocks, not byte by byte.** Reading `BUFFER_SIZE` bytes at a time means fewer system calls than reading one character at a time, which is faster for large files.
- **Stopping as soon as a `\n` is in the stash.** The function never reads more of the file than it needs for the current line, so the rest stays available for the next call and memory use stays low.
- **Handling any `BUFFER_SIZE`.** Because the stash grows by appending, a line longer than the buffer is built up over several `read` calls, and a buffer longer than the line simply leaves a remainder in the stash. This works for `BUFFER_SIZE=1` and for very large values.
- **Memory safety.** Every allocation is freed once it is no longer needed: the temporary buffer after each append, and the old stash after each trim. On end of file or on error, the stash is freed and set to `NULL`, so there are no leaks.

**Data structures.** The only structure is a heap-allocated string stored in the static variable. No linked lists or other structures are needed.

## Instructions

**Compilation**

Compile the source files together with your own `main.c`, and define the buffer size at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

If `BUFFER_SIZE` is not defined on the command line, the header provides a default value.

**Usage**

Include `get_next_line.h` in your own `main.c`, open a file with `open` to get a file descriptor, and call `get_next_line(fd)` in a loop. Each call returns the next line, and the loop stops when it returns `NULL`. The caller owns each returned string and must `free` it after use.

**Testing suggestions**
- Try several buffer sizes, such as `-D BUFFER_SIZE=1`, `-D BUFFER_SIZE=42` and `-D BUFFER_SIZE=10000000`.
- Test an empty file, a file with no trailing newline, a file with only newlines, a very long line, and an invalid file descriptor.
- Check for leaks with Valgrind or `-fsanitize=address`.

## Resources

**References**
- `man 2 read`, `man 2 open`, `man 3 malloc`.
- GeeksforGeeks articles on static variables, file handling and dynamic memory allocation in C.
- Stack Overflow questions and answers on `read`, static variables and memory management in C.

**How AI was used**

AI (Claude) was used only for help with C syntax and for understanding compiler and runtime errors. It was not used to design the algorithm or to write the project code.
