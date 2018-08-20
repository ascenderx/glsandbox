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

$(OBJ)/%.o: $(SRC)/%.$(CEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.oh: $(SRC)/%.$(CEXT) $(SRC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.oo: $(SRC)/%.$(C++EXT) $(UHEADERS)
	$(C++) -c -o $@ $< $(CFLAGS)

$(OBJ)/%.ooh: $(SRC)/%.$(C++EXT) $(SRC)/%.$(H++EXT) $(UHEADERS)
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

UOBJECTS = $(OBJ)/utilinit.oh $(OBJ)/utilinput.oh $(OBJ)/utildraw.oh $(OBJ)/utildebug.oh
UHEADERS = $(SRC)/utiltypes.h

##############################################################################
# BINARY RULES
##############################################################################

OBJECTS1 = # currently empty
one: $(OBJ)/one.o $(UOBJECTS) $(UHEADERS) $(OBJECTS1)
	$(CC) -o $(BIN)/$@ $< $(UOBJECTS) $(OBJECTS1) $(LFLAGS)
