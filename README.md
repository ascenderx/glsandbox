# GLSandbox
Sandbox/playground for OpenGL projects

## Compilation
To compile a binary, use GNU/LLVM Make.
For example, to compile a binary named "test" with dependencies "something.c" and "something.h":
- Include the target in the "BINARY RULES" section at the bottom of the makefile:
```
    test: $(OBJ)/test.o $(INCLUDES) $(OBJ)/something.oh
	    $(CC) -o $@ $? $(LFLAGS)
```
- Be sure to include any extra includes after the `$(INCLUDES)` directive, using the `$(OBJ)/*.oh` format.
- Navigate to the folder in a terminal and type `make test`.