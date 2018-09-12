##############################################################################
# COMPILATION RULES
##############################################################################

# directories
BIN      = bin
OBJ      = obj
SRC      = src
LIB      = lib
LIBSRC   = include
CEXT     = c
HEXT     = h
CPPEXT   = cc # or c++, cpp, C, cxx, etc.
HPPEXT   = hh # or h++, hpp, H, hxx, h, etc.

# User objects
$(OBJ)/%.o: $(SRC)/%.$(CEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

# User objects with user headers
$(OBJ)/%.ho: $(SRC)/%.$(CEXT) $(SRC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

# Included / builtin objects with headers
$(OBJ)/%.hio: $(LIBSRC)/%.$(CEXT) $(LIBSRC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PICFLAGS)

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
	if [ ! -d "$(LIB)" ]; then mkdir $(LIB); fi

cleanbin:
	rm -f $(BIN)/*
	rm -f $(OBJ)/*

cleanlib:
	rm -f $(LIB)/*

cleanall:
	make cleanbin
	make cleanlib

rmobj:
	rm -f $(OBJ)

wipe:
	rm -r -f $(BIN)
	rm -r -f $(OBJ)
	rm -r -f $(LIB)

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

# library rules
ARCHIVER = ar
ARCHOPTS = -ruv
LIBRER   = ranlib
LIBNAME  = utils
LIBRARY  = lib$(LIBNAME)
INCLIB   = -L$(LIB) -l$(LIBNAME)
INCLUDES = -I$(LIBSRC)

# compilation / linking flags
LIBGLU   = -lglfw # alternatively, -lglu, -lglut, -lglew, -lglfw, etc.
LIBMATH  = -lm
LFLAGS   = $(LIBGL) $(LIBGLU) $(LIBMATH)
CSTD     = -std=gnu11
WARNS    = -Wall -Wextra -Wno-unused-parameter
OPTIMIZE = -O2
CFLAGS   = $(WARNS) $(CSTD) $(OPTIMIZE)
PICFLAGS = -fPIC

##############################################################################
# INCLUDE FILES
##############################################################################

UOBJECTS = \
	$(OBJ)/utilinit.hio  \
	$(OBJ)/utilinput.hio \
	$(OBJ)/utildraw.hio  \
	$(OBJ)/utildebug.hio \
	$(OBJ)/utiltext.hio
UHEADERS = $(LIBSRC)/utiltypes.h

##############################################################################
# BINARY RULES
##############################################################################

OBJECTS1 = $(OBJ)/one-player.ho
one: $(OBJ)/one.o $(OBJECTS1) $(LIBRARY)
	$(CC) -o $(BIN)/$@ $< $(OBJECTS1) $(LFLAGS) $(INCLIB)

$(LIBRARY): $(UOBJECTS) $(UHEADERS)
	$(ARCHIVER) $(ARCHOPTS) $(LIB)/$(LIBRARY).a $(UOBJECTS)
	$(LIBRER) $(LIB)/$(LIBRARY).a
