##############################################################################
# COMPILATION RULES
##############################################################################

# directories
BIN      = bin
BINDIR   = $(BIN)/$(PLAT)
OBJ      = obj
SRC      = src
LIB      = lib/utils
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
	if [ ! -d "$(LIBHEADD)" ]; then mkdir -p $(LIBHEADD); fi

cleanbin:
	rm -f $(BINDIR)/*
	rm -f $(OBJ)/*

cleanlib:
	rm -f $(LIBDIR)/*.a
	rm -f $(LIBHEADD)/*.h

cleanall:
	make cleanbin
	make cleanlib

rmobj:
	rm -rf $(OBJ)

##############################################################################
# LIBRARY DEFINITIONS
##############################################################################

# test for correct OpenGL flag and library folder
# is it macOS?
ifeq ($(shell uname -s), Darwin)
    LIBGL = -framework OpenGL
	PLAT = macos
# otherwise, it's Linux, Unix, etc.
else
    LIBGL = -lGL
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
LIBHEADD = $(LIB)/headers
LIBHEAD  = -I$(LIBHEADD)
LIBUTILS = -L$(LIBDIR) -l$(LIBNAME)
LIBDIR   = $(LIB)/$(PLAT)

# compilation / linking flags
#LIBGLU    = -lglfw # alternatively, -lglu, -lglut, -lglew, -lglfw, etc.
#LFLAGS   = $(LIBGL) $(LIBGLU) $(LIBMATH)
LIBMATH   = -lm
PKGCFGDIR = env PKG_CONFIG_PATH=./lib/glfw/$(PLAT)
PKGCFGCFL = `pkg-config --cflags glfw3`
PKGCFGLIB = `pkg-config --static --libs glfw3`
LIBGLFW   = $(PKGCFGCFL) $(PKGCFGLIB)
LFLAGS    = $(LIBGL) $(LIBMATH) $(LIBUTILS) $(LIBGLFW)
CSTD      = -std=gnu11
WARNS     = -Wall -Wextra -Wno-unused-parameter
OPTIMIZE  = -O2
CFLAGS    = $(WARNS) $(CSTD) $(OPTIMIZE)
PICFLAGS  = -fPIC

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

OBJECTS1 = $(OBJ)/one.o $(OBJ)/one-player.ho
one: $(OBJECTS1)
	$(PKGCFGDIR) $(CC) -o $(BINDIR)/$@ $? $(LFLAGS)

$(LIBRARY): $(UOBJECTS) $(UHEADERS)
	$(ARCHIVER) $(ARCHOPTS) $(LIBDIR)/$(LIBRARY).a $(UOBJECTS)
	$(LIBRER) $(LIBDIR)/$(LIBRARY).a
	cp $(LIBSRC)/*.h $(LIBHEADD)/
