######################
#  library makefile  #
######################

# (1) select which components to use
#USE_COMPRESSION = library/compression
#USE_NETWORK = library/network
#USE_SCRIPT  = library/script
USE_SOUND   = library/sound
USE_OPENGL  = library/opengl library/voxels

# (2) select build options
# Fast:
# -Ofast -msse4.1 -ffast-math -mfpmath=both -march=native
# Debug:
# -ggdb3
BUILDOPT = -Ofast -msse2 -m32
# output file
OUTPUT   = ./liblibrary.a
OUTTEST  = ./test

##############################################################

# code folders
SOURCE_DIRS  = src
LIBRARY_DIRS = library library/bitmap library/math library/math/kine \
				library/noise library/storage library/threading library/timing \
				$(USE_OPENGL) $(USE_COMPRESSION) $(USE_NETWORK) $(USE_SCRIPT) $(USE_SOUND)

# compiler
CC = g++ $(BUILDOPT) -std=c++11
# compiler flags
CCFLAGS = -c -MMD -Wall -Wextra -Wno-write-strings -Iinc -Iinclude
# linker flags
LDFLAGS = -m32 -Llib/win32 -static -lbassdll -lglfw3 -lgdi32 -lglew32s -lopengl32

##############################################################

# make pipeline
DIRECTORIES = $(LIBRARY_DIRS) $(SOURCE_DIRS)
CCDIRS  = $(foreach dir, $(DIRECTORIES), $(dir)/*.c)
CCMODS  = $(wildcard $(CCDIRS))
CXXDIRS = $(foreach dir, $(DIRECTORIES), $(dir)/*.cpp)
CXXMODS = $(wildcard $(CXXDIRS))

# compile each .c to .o
.c.o:
	$(CC) $(CCFLAGS) $< -o $@

# compile each .cpp to .o
.cpp.o:
	$(CC) $(CCFLAGS) $< -o $@

# convert .c to .o
CCOBJS  = $(CCMODS:.c=.o)
# convert .cpp to .o
CXXOBJS = $(CXXMODS:.cpp=.o)
# convert .o to .d
DEPENDS = $(CXXOBJS:.o=.d)

# link all OBJS using CC and link with LFLAGS, then output to OUTPUT
all: $(CXXOBJS) $(CCOBJS)
	ar cr $(OUTPUT) $(CXXOBJS) $(CCOBJS)
	$(CC) $(CXXOBJS) $(CCOBJS) $(LDFLAGS) -o $(OUTTEST)

# remove each known .o file, and output
clean:
	$(RM) $(CXXOBJS) $(CCOBJS) $(OUTPUT) $(OUTTEST)

-include $(DEPENDS)
