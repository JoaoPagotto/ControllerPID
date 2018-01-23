QT += core gui widgets charts

TARGET = ControllerPID

TEMPLATE = app

#------------------------------------------------------------------------------

win32-msvc2015 {
   #Disable optimizations
   QMAKE_CXXFLAGS_DEBUG -= -O2 # optimizes code for maximum speed.
   QMAKE_CXXFLAGS_DEBUG -= -O1 # optimizes code for minimum size.
   QMAKE_CXXFLAGS_DEBUG += -Od # disables optimization, speeding
                               # compilation and simplifying debugging.

   RC_FILE = ControllerPID.rc
   DEFINES += _CRT_SECURE_NO_WARNINGS
}

#------------------------------------------------------------------------------

linux {
   QMAKE_LFLAGS += -Wl,-rpath,\\$\$ORIGIN
}

#------------------------------------------------------------------------------

macx {
   QMAKE_LFLAGS += -Wl,-rpath,\\$\$ORIGIN
}

#------------------------------------------------------------------------------

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    PidCtrl.cpp \
    PidCtrlModel.cpp

HEADERS += \
    mainwindow.h \
    PidCtrl.h \
    PidCtrlModel.h

FORMS += mainwindow.ui

OTHER_FILES += ControllerPID.rc
