FLAGS = -g
GCC = g++
INCLUDE = -I/usr/local/include/opencv4 -I/usr/include/spinnaker
LIBS = -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -l opencv_imgcodecs -lSpinnaker -lopencv_video
CPP_FILES = ImageProcessing/ImageProcessor.cpp CameraCapture/CameraCapture.cpp
MAIN_TARGETS = main
TEST_TARGETS = speedtest spinnakertest videorecord

all: ${MAIN_TARGETS} ${TEST_TARGETS}

clean:
	rm -f ${MAIN_TARGETS} ${TEST_TARGETS}

main: ${CPP_FILES}
	${GCC} main.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o main

tests: speedtest spinnakertest videorecord

speedtest: ${CPP_FILES}
	${GCC} Tests/SpeedTest.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o speedtest

spinnakertest: ${CPP_FILES}
	${GCC} Tests/SpinnakerTest.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o spinnakertest

videorecord: ${CPP_FILES}
	${GCC} Tests/VideoRecord.cpp ${CPP_FILES} ${FLAGS} ${INCLUDE} ${LIBS} -o videorecord

