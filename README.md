# GLSandbox
Sandbox/playground for OpenGL and WebGL projects

## Desktop OpenGL
### Compilation
To compile a binary, use GNU/LLVM Make.
Make sure the folders `obj` and `bin` exist by first running `make dirs`.

For example, to compile a binary named `test` with dependencies `something.c` and `something.h`:
- Include the target in the **BINARY RULES** section at the bottom of the makefile:
```
TESTOBJECTS = $(OBJ)/something.ho
test: $(OBJ)/test.o $(TESTOBJECTS)
[\t] $(CC) -o $(BIN)/$@ $< $(TESTOBJECTS) $(LFLAGS) $(INCLIB)
```
  - Be sure to include any extra includes in the rule and the compilation lines, using the `$(OBJ)/*.ho` (C) or `$(OBJ)/*.hoo` (C++) formats.
  - NOTE: Adding `$(INCLIB)` (alias for `-Llib/{macos, linux} -lutils`) is necessary in order to use the `libutils` OpenGL/GLFW wrapper library. This will necessitate including the header files during object-compilation using `$(LIBHEAD)` (alias for `-Ilib/headers`), which is done automatically using the provided makefile.

- Navigate to the folder in a Unix/Unix-like terminal and type `make test`.

To reset `bin/{macos, linux}` and `obj` for user binary recompliation, run `make cleanbin`.

To reset `lib/{clang, gcc}` for library recompilation, run `make cleanlib`.

To reset `bin/{macos, linux}`, `obj` and `lib/{clang, gcc}` for complete recompliation, run `make cleanall`.

To recompile the helper `libutils` library, run `make libutils`.

To remove `obj` but keep `bin/{macos, linux}`, run `make rmobj`.

### Execution
To run your compiled binary, navigate to the repository's root directory in a Unix/Unix-like terminal and run the program there.

For example, to run `test`, navigate to the root directory and run `bin/test` or change to the `bin` subdirectory and run `./test`.

## Browser WebGL
### Execution
