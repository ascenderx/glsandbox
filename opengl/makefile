##############################################################################
# COMPILATION RULES
##############################################################################

# directories
PLAT     =
BIN      = bin
BINDIR   = $(BIN)/$(PLAT)
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
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBHEAD)

# User objects with user headers
$(OBJ)/%.ho: $(SRC)/%.$(CEXT) $(SRC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBHEAD)

# Included / builtin objects with headers
$(OBJ)/%.hio: $(LIBSRC)/%.$(CEXT) $(LIBSRC)/%.$(HEXT) $(UHEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(PICFLAGS)

# User objects (C++)
$(OBJ)/%.oo: $(SRC)/%.$(CPPEXT) $(UHEADERS)
	$(C++) -c -o $@ $< $(CFLAGS) $(LIBHEAD)

# User objects with user headers (C++)
$(OBJ)/%.hoo: $(SRC)/%.$(CPPEXT) $(SRC)/%.$(HPPEXT) $(UHEADERS)
	$(C++) -c -o $@ $< $(CFLAGS) $(LIBHEAD)

##############################################################################
# DIRECTORY RULES
##############################################################################

dirs:
	if [ ! -d "$(OBJ)" ]; then mkdir $(OBJ); fi
	if [ ! -d "$(BINDIR)" ]; then mkdir -p $(BINDIR); fi
	if [ ! -d "$(LIBDIR)" ]; then mkdir -p $(LIBDIR); fi

cleanbin:
	rm -f $(BINDIR)/*
	rm -f $(OBJ)/*

cleanlib:
	rm -f $(LIBDIR)/*

cleanall:
	make cleanbin
	make cleanlib

rmobj:
	rm -rf $(OBJ)

wipe:
	rm -rf $(BINDIR)
	rm -rf $(OBJ)
	rm -rf $(LIBDIR)

##############################################################################
# LIBRARY DEFINITIONS
##############################################################################

# test for correct OpenGL flag and library folder
# is it macOS?
ifeq ($(shell uname -s), Darwin)
    LIBGL = -framework OpenGL
	LIBDIR = $(LIB)/clang
	PLAT = macos
# otherwise, it's Linux, Unix, etc.
else
    LIBGL = -lGL
	LIBDIR = $(LIB)/gcc
	ifeq ($(shell uname -s), Linux)
		PLAT = linux
	endif
endif

# library rules
ARCHIVER = ar
ARCHOPTS = -ruv
LIBRER   = ranlib
LIBNAME  = utils
LIBRARY  = lib$(LIBNAME)
LIBHEAD  = -I$(LIBDIR)
INCLIB   = -L$(LIBDIR) -l$(LIBNAME)

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
one: $(OBJ)/one.o $(OBJECTS1)
	$(CC) -o $(BINDIR)/$@ $< $(OBJECTS1) $(LFLAGS) $(INCLIB) $(LFLAGS)

$(LIBRARY): $(UOBJECTS) $(UHEADERS)
	$(ARCHIVER) $(ARCHOPTS) $(LIBDIR)/$(LIBRARY).a $(UOBJECTS)
	$(LIBRER) $(LIBDIR)/$(LIBRARY).a
	cp $(LIBSRC)/*.h $(LIBDIR)/
