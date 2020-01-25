FLAGS = -g
GCC = g++
INCLUDE = -I/usr/local/include/opencv4
LIBS = -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -l opencv_imgcodecs
CPP_FILES = ImageProcessing/ImageProcessor.cpp

all: main tests

clean:
	rm main speedtest

main: ${CPP_FILES}
	${GCC} main.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o main

tests: ${TESTING_CPP_FILES}
	${GCC} Tests/SpeedTest.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o speedtest


