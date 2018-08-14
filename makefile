##############################################################################
# PRECOMPILATION DEFINITIONS
##############################################################################

# compilation / linking flags
LFLAGS = $(LIBGL) $(LIBGLU) -lm
CFLAGS = -Wall
LIBGLU = -lglfw # alternatively, -lglu, -lglut, -lglew, -lglfw, etc.

# directories
BIN = bin
OBJ = obj
SRC = src

# test for correct OpenGL flag
# is it macOS?
ifeq ($(shell uname -s), Darwin)
    LIBGL = -framework OpenGL
# otherwise, it's Linux, Unix, etc.
else
    LIBGL = -lGL
endif

##############################################################################
# COMPILATION RULES
##############################################################################

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.oh: $(SRC)/%.c $(SRC)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

##############################################################################
# INCLUDE FILES
##############################################################################

INCLUDES = $(OBJ)/init.oh $(OBJ)/input.oh $(OBJ)/draw.oh

##############################################################################
# CUSTOM BINARY RULES
##############################################################################

one: $(OBJ)/one.o $(INCLUDES)
	$(CC) -o $@ $? $(LFLAGS)

##############################################################################
# DIRECTORY RULES
##############################################################################

dirs:
	if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi
	if [ ! -d "$(BIN)" ]; then mkdir $(BIN); fi

clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

rmdirs:
	rm -r -f $(BIN)
	rm -r -f $(OBJ)