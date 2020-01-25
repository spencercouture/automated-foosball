FLAGS = -g
GCC = g++
INCLUDE = -I/usr/local/include/opencv4
LIBS = -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -l opencv_imgcodecs
CPP_FILES = main.cpp
TESTING_CPP_FILES = Tests/SpeedTest.cpp

all: main

clean:
	rm main speedtest

main: ${CPP_FILES}
	${GCC} ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o main

tests: ${TESTING_CPP_FILES}
	${GCC} ${TESTING_CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o speedtest


