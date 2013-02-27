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
    prscheme.cpp \
    lbscheme.cpp \
    imscheme.cpp

HEADERS += \
    basesolver.h \
    cnscheme.h \
    solverfactory.h \
    drscheme.h \
    settings.h \
    domains.h \
    prscheme.h \
    lbscheme.h \
    imscheme.h

OTHER_FILES += \
    ufl/DR4.ufl \
    ufl/DR3.ufl \
    ufl/DR2.ufl \
    ufl/DR1.ufl \
    ufl/PR4.ufl \
    ufl/PR3.ufl \
    ufl/PR2.ufl \
    ufl/PR1.ufl \
    ufl/LB3.ufl \
    ufl/LB2.ufl \
    ufl/LB1.ufl \
    ufl/CN2.ufl \
    ufl/CN1.ufl \
    start.sh \
    ufl/IM.ufl

LIBS += -ldolfin
