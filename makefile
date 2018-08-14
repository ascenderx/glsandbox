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

$(BIN)/one: $(BIN)/one.exec $(OBJ)/draw.o
	mv $(BIN)/one.exec $(BIN)/one

$(BIN)/%.exec: $(OBJ)/%.o
	if [ ! -d "$(BIN)" ]; then mkdir $(BIN); fi
	$(CC) -o $@ $? $(LFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi
	$(CC) -c -o $@ $? $(CFLAGS)

##############################################################################
# CLEANUP RULES
##############################################################################

clean:
	rm $(BIN)/*
	rm $(OBJ)/*
