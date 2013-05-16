
CPP_FILES = $(wildcard Chorus/XML/*.cpp \
						Chorus/app/*.cpp \
						Chorus/camera/*.cpp \
						Chorus/console/*.cpp \
						Chorus/content/*.cpp \
						Chorus/core/*.cpp \
						Chorus/debug/*.cpp \
						Chorus/draw/*.cpp \
						Chorus/input/*.cpp \
						Chorus/particle_system/*.cpp \
						Chorus/*.cpp \
						Game/*.cpp )

LIBS = -lm -lSDL -lSDL_image -lGLEW -lGL -lGLU
INC_SDL = -I/usr/include/SDL 
INC_GLEW = -I/usr/include/GL
INC = $(INC_SDL) $(INC_GLEW)
CFALGS = -D _unix_

chorus: $(CPP_FILES)
	g++  -o $@ $^ $(LIBS) $(INC) $(CFALGS)

clean: 
	rm -rf chorus

fresh: clean chorus