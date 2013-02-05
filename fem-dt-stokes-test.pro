TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    basesolver.cpp \
    cnscheme.cpp \
    solverfactory.cpp \
    drscheme.cpp \
    settings.cpp \
    implicitscheme.cpp \
    prscheme.cpp \
    lbscheme.cpp

HEADERS += \
    basesolver.h \
    cnscheme.h \
    solverfactory.h \
    drscheme.h \
    settings.h \
    domains.h \
    implicitscheme.h \
    prscheme.h \
    lbscheme.h

OTHER_FILES += \
    ufl/Stream.ufl \
    ufl/Stokes.ufl \
    ufl/DR4.ufl \
    ufl/DR3.ufl \
    ufl/DR2.ufl \
    ufl/DR1.ufl \
    ufl/StokesGrad.ufl \
    ufl/PR4.ufl \
    ufl/PR3.ufl \
    ufl/PR2.ufl \
    ufl/PR1.ufl \
    ufl/LB3.ufl \
    ufl/LB2.ufl \
    ufl/LB1.ufl \
    ufl/CN2.ufl \
    ufl/CN1.ufl \
    start.sh

LIBS += -ldolfin

QMAKE_CXXFLAGS_WARN_OFF += unused-parameter
