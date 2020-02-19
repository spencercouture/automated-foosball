FLAGS = -g
GCC = g++
INCLUDE = -I/usr/local/include/opencv4 -I/usr/include/spinnaker
LIBS = -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -l opencv_imgcodecs -lSpinnaker -lopencv_video
CPP_FILES = ImageProcessing/ImageProcessor.cpp CameraCapture/CameraCapture.cpp

all: main tests

clean:
	rm -f *.o

main: ${CPP_FILES}
	${GCC} main.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o main.o

tests: speedtest spinnakertest videorecord

speedtest: ${CPP_FILES}
	${GCC} Tests/SpeedTest.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o speedtest.o

spinnakertest: ${CPP_FILES}
	${GCC} Tests/SpinnakerTest.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o spinnakertest.o

videorecord: ${CPP_FILES}
	${GCC} Tests/VideoRecord.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o videorecord.o
