##############################################################################
# COMPILATION RULES
##############################################################################

# directories
BIN      = bin
OBJ      = obj
SRC      = src
INC      = include
CEXT     = c
HEXT     = h
CPPEXT   = cc # or c++, cpp, C, cxx, etc.
HPPEXT   = hh # or h++, hpp, H, hxx, h, etc.
INCLUDES = -I$(INC) 

# User objects
$(OBJ)/%.o: $(SRC)/%.$(CEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

# User objects with user headers
$(OBJ)/%.ho: $(SRC)/%.$(CEXT) $(SRC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

# Included / builtin objects with headers
$(OBJ)/%.hio: $(INC)/%.$(CEXT) $(INC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

# User objects (C++)
$(OBJ)/%.oo: $(SRC)/%.$(CPPEXT) $(UHEADERS)
	$(C++) -c -o $@ $< $(CFLAGS) $(INCLUDES)

# User objects with user headers (C++)
$(OBJ)/%.hoo: $(SRC)/%.$(CPPEXT) $(SRC)/%.$(HPPEXT) $(UHEADERS)
	$(C++) -c -o $@ $< $(CFLAGS) $(INCLUDES)

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
CSTD    = -std=gnu11
WARNS   = -Wall
CFLAGS  = $(WARNS) $(CSTD)

##############################################################################
# INCLUDE FILES
##############################################################################

UOBJECTS = \
	$(OBJ)/utilinit.hio  \
	$(OBJ)/utilinput.hio \
	$(OBJ)/utildraw.hio  \
	$(OBJ)/utildebug.hio \
	$(OBJ)/utiltext.hio
UHEADERS = $(INC)/utiltypes.h

##############################################################################
# BINARY RULES
##############################################################################

OBJECTS1 = $(OBJ)/one-player.ho
one: $(OBJ)/one.o $(UOBJECTS) $(UHEADERS) $(OBJECTS1)
	$(CC) -o $(BIN)/$@ $< $(UOBJECTS) $(OBJECTS1) $(LFLAGS)
