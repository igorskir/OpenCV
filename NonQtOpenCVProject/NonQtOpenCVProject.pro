TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include (Common\\OpenCV.pri)

#INCLUDEPATH += C:\\OpenCV-3.1\\build\\include

#CONFIG(debug,debug|release)
#{
#    LIBS += -LC:\\OpenCV-3.1\\mybuild\\lib\\Debug \
#        -lopencv_videostab310d \
#        -lopencv_videoio310d \
#        -lopencv_video310d \
#        -lopencv_ts310d \
#        -lopencv_superres310d \
#        -lopencv_stitching310d \
#        -lopencv_shape310d \
#        -lopencv_photo310d \
#        -lopencv_objdetect310d \
#        -lopencv_ml310d \
#        -lopencv_imgproc310d \
#        -lopencv_imgcodecs310d \
#        -lopencv_highgui310d \
#        -lopencv_flann310d \
#        -lopencv_features2d310d \
#        -lopencv_core310d \
#        -lopencv_calib3d310d
#}

#CONFIG(release,debug|release)
#{
#    LIBS += -LC:\\OpenCV-3.1\\mybuild\\lib\\Release \
#        -lopencv_videostab310 \
#        -lopencv_videoio310 \
#        -lopencv_video310 \
#        -lopencv_ts310 \
#        -lopencv_superres310 \
#        -lopencv_stitching310 \
#        -lopencv_shape310 \
#        -lopencv_photo310 \
#        -lopencv_objdetect310 \
#        -lopencv_ml310 \
#        -lopencv_imgproc310 \
#        -lopencv_imgcodecs310 \
#        -lopencv_highgui310 \
#        -lopencv_flann310 \
#        -lopencv_features2d310 \
#        -lopencv_core310 \
#        -lopencv_calib3d310
#}
