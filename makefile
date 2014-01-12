######################
#  library makefile  #
######################

# components
USE_COMPRESSION = 0
USE_NETWORK = 0
USE_SOUND = 0

# code folders
SOURCE_DIRS  = 
LIBRARY_DIRS = library library/bitmap library/math library/math/kine \
				library/noise library/opengl library/script \
				library/storage library/threading library/timing \
				library/voxels \
				$(if USE_COMPRESSION, library/compression) \
				$(if USE_NETWORK, library/network) \
				$(if USE_SOUND, library/sound) \

# build options
# Superfast:
# -Ofast -msse4.1 -ffast-math -mfpmath=both -march=native -flto -fwhole-program
# Fast:
# -Ofast -msse4.1 -ffast-math -mfpmath=both -march=native
# Debug:
# -ggdb3
BUILDOPT = -ggdb3
# output file
OUTPUT   = ./liblibrary.a

##############################################################

# compiler
CC = g++ $(BUILDOPT) -std=c++11
# compiler flags
CCFLAGS = -c -Wall -Wno-write-strings -Iinc -Iinclude
# linker flags
ifeq ($(OS),Windows_NT)
	LFLAGS  = -Llib/win -static -lpthread -lbassdll -lglfw3 -lgdi32 -lopengl32 -llzo2 -lws2_32 -ltcc
else
	LFLAGS  = -Llib/linux -lpthread -lbass -llzo2 -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lXi -ltcc -ldl
endif

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

# link all OBJS using CC and link with LFLAGS, then output to OUTPUT
all: $(CXXOBJS) $(CCOBJS) $(CCRES)
	ar cr $(OUTPUT) $(CXXOBJS) $(CCOBJS) $(CCRES)

# remove each known .o file, and output
clean:
	$(RM) $(CXXOBJS) $(CCOBJS) $(OUTPUT)

