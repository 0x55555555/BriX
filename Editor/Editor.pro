QT += core gui opengl widgets

SOURCES += \
    main.cpp \
    BxLevelScene.cpp \
    BxLevelView.cpp \
    BxMainWindow.cpp \
    BxBaseAttribute.cpp \
    BxIntAttribute.cpp \
    BxNodeActor.cpp \
    BxNodePath.cpp \
    BxNodePathPoint.cpp \
    BxNodeLine.cpp

HEADERS += \
    BxMainWindow.h \
    BxLevelScene.h \
    BxLevelView.h \
    BxBaseAttribute.h \
    BxIntAttribute.h \
    BxAttributes.h \
    BxNodeActor.h \
    BxNodePath.h \
    BxNodePathPoint.h \
    BxNodeLine.h

OTHER_FILES += \
    ../../Desktop/test.json
