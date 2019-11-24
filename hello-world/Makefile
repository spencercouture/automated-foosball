OBS = hello-world.o
FLAGS = -g
GCC = g++
INCLUDE = -I/usr/local/include/opencv4
LIBS = -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -l opencv_imgcodecs

all: hello-world

clean: rm *.o

hello-world: hello-world.cpp
	${GCC} hello-world.cpp ${FLAGS} ${INCLUDE} ${LIBS} -o hello-world.o

