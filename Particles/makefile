#changing platform dependant stuff, do not change this
# Linux (default)
LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -Wall -std=c++11
CC=g++
EXEEXT=
RM=rm

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
	# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

PROGRAM_NAME= A2

 
run: $(PROGRAM_NAME)
	./$(PROGRAM_NAME)$(EXEEXT)

#run:
#	$(CC) $(CFLAGS) mathLib2D.cpp A2.cpp -o a2
#	./a2

$(PROGRAM_NAME): A2.o 
	$(CC) -o $@ $^ $(CFLAGS) mathLib2D.cpp $(LDFLAGS) 
	# added mathLib2D.cpp so that it knows where to get it

clean:
	$(RM) *.o $(PROGRAM_NAME)$(EXEEXT)
