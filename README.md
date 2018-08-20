# GLSandbox
Sandbox/playground for OpenGL and WebGL projects

## Compilation
To compile a binary, use GNU/LLVM Make.
Make sure the folders `obj` and `bin` exist by first running `make dirs`.

For example, to compile a binary named `test` with dependencies `something.c` and `something.h`:
- Include the target in the **BINARY RULES** section at the bottom of the makefile:
```
TESTOBJECTS = $(OBJ)/something.oh
test: $(OBJ)/test.o $(UOBJECTS) $(UHEADERS) $(TESTOBJECTS)
[\t] $(CC) -o $(BIN)/$@ $< $(UOBJECTS) $(TESTOBJECTS) $(LFLAGS)
```
  - Be sure to include any extra includes after the `$(UOBJECTS)` directive in the rule and the compilation lines, using the `$(OBJ)/*.oh` (C) or `$(OBJ)/*.ooh` (C++) formats.
- Navigate to the folder in a Unix/Unix-like terminal and type `make test`.

To reset `bin` and `obj` for recompliation, run `make clean`.
To remove `bin` and `obj` for code distribution, run `make rmdirs`.

## Execution
To run your compiled binary, navigate to the repository's root directory in a Unix/Unix-like terminal and run the program there.

For example, to run `test`, navigate to the root directory and run `bin/test` or change to the `bin` subdirectory and run `./test`.
