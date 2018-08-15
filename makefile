##############################################################################
# COMPILATION RULES
##############################################################################

# directories
BIN    = bin
OBJ    = obj
SRC    = src
CEXT   = c
HEXT   = h
C++EXT = cc # or c++, cpp, C, cxx, etc.
H++EXT = hh # or h++, hpp, H, hxx, h, etc.

$(OBJ)/%.o: $(SRC)/%.$(CEXT) $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.oh: $(SRC)/%.$(CEXT) $(SRC)/%.$(HEXT) $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.oo: $(SRC)/%.$(C++EXT) $(HEADERS)
	$(C++) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.ooh: $(SRC)/%.$(C++EXT) $(SRC)/%.$(H++EXT) $(HEADERS)
	$(C++) -c -o $@ $< $(CFLAGS)

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

##############################################################################
# LIBRARY DEFINITIONS
##############################################################################

# test for correct OpenGL flag
# is it macOS?
ifeq ($(shell uname -s), Darwin)
    LIBGL = -framework OpenGL
# otherwise, it's Linux, Unix, etc.
else
    LIBGL = -lGL
endif

# compilation / linking flags
LIBGLU  = -lglfw # alternatively, -lglu, -lglut, -lglew, -lglfw, etc.
LIBMATH = -lm
LFLAGS  = $(LIBGL) $(LIBGLU) $(LIBMATH)
CFLAGS  = -Wall

##############################################################################
# INCLUDE FILES
##############################################################################

OBJECTS = $(OBJ)/utilinit.oh $(OBJ)/utilinput.oh $(OBJ)/utildraw.oh
HEADERS = $(SRC)/utiltypes.h

##############################################################################
# BINARY RULES
##############################################################################

OBJECTS1 = 
one: $(OBJ)/one.o $(OBJECTS) $(HEADERS) $(OBJECTS1)
	$(CC) -o $(BIN)/$@ $< $(OBJECTS) $(OBJECTS1) $(LFLAGS)
