CXX=g++

CFLAGS= -O3 -Wall -I/usr/local/include -I/usr/X11R6/include -I/usr/include -I/opt/include -I/

LFLAGS= -L/usr/X11R6/lib -L/opt/lib -lGL -lGLU -lX11 -lXext -lpthread -lm -lGLEW

.cpp.o:
	${CXX} -c ${CFLAGS} $<
%.o:    %.cxx
	${CXX} -c ${CFLAGS} $<

%.fltk: %.o
	${CXX} $< -lglut -lfltk -lfltk_gl -lfltk_forms -lfltk_images ${LFLAGS} -o $@

%.sdl:  %.o
	${CXX} $< -lSDL ${LFLAGS} -o $@

%.glfw: %.o 
	${CXX} $< -lglfw ${LFLAGS} -o $@  

%.glut: %.o
	${CXX} $< -lglut ${LFLAGS} -o $@  

clean:
	rm a.out *.o *~ core
