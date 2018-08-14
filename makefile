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
ifeq ($(shell uname -s), Darwin)
    LIBGL = -framework OpenGL
else
    LIBGL = -lGL
endif

##############################################################################
# COMPILATION RULES
##############################################################################

dirs:
	if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi
	if [ ! -d "$(BIN)" ]; then mkdir $(BIN); fi

one: $(OBJ)/one.o $(OBJ)/init.oh $(OBJ)/draw.oh
	$(CC) -o $@ $? $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.oh: $(SRC)/%.c $(SRC)/%.h
	$(CC) -c -o $@ $< $(CFLAGS)

##############################################################################
# CLEANUP RULES
##############################################################################

clean:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*
