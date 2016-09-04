SOURCES += \
    main.cpp \
    classifier.cpp \
    facedetector.cpp \
    thread.cpp \
    worker.cpp

LIBS += -L/home/young/multithread/build-FaceRelease-Desktop_Qt_5_5_0_GCC_64bit-Release/dlib-18.18 -ldlib -lpthread -lX11 -ljpeg
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_imgcodecs

# caffe
INCLUDEPATH += /home/young/multithread/build-FaceRelease-Desktop_Qt_5_5_0_GCC_64bit-Release \
              /home/young/multithread/build-FaceRelease-Desktop_Qt_5_5_0_GCC_64bit-Release/caffe/include \
              /home/young/multithread/build-FaceRelease-Desktop_Qt_5_5_0_GCC_64bit-Release/caffe/src \
              /usr/local/include \
              #/home/young/devtools/dlib-19.1/dlib/all/source.cpp \

              

LIBS += -L/home/young/multithread/build-FaceRelease-Desktop_Qt_5_5_0_GCC_64bit-Release/caffe/lib -lcaffe

# cuda
#INCLUDEPATH += /usr/local/cuda/include
#LIBS += -L/usr/local/cuda/lib64
#LIBS += -lcudart -lcublas -lcurand


# other dependencies
LIBS += -lglog -lgflags -lprotobuf -lboost_system -lboost_thread  -latlas

HEADERS += \
    classifier.h \
    facedetector.h \
    classifier.h \
    facedetector.h \
    thread.h \
    worker.h

