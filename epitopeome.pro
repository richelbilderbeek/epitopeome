# Builds the entire project

################################################################################
# Files
################################################################################

# Entry point for this project
SOURCES += \
    cpp/main_test.cpp \
    cpp/test_calc_binding_freqs_cpp.cpp \
    cpp/test_create_epitopeome_cpp.cpp \
    cpp/test_create_epitopeome_file_cpp.cpp \
    cpp/test_create_locatome_cpp.cpp \
    cpp/test_split_str_cpp.cpp \
    src/calc_binding_freqs_cpp.cpp \
    src/create_epitopeome_cpp.cpp \
    src/create_epitopeome_file_cpp.cpp \
    src/create_locatome_cpp.cpp \
    src/split_str_cpp.cpp \
    cpp/test_do_elutes_bind.cpp

HEADERS += \
    src/calc_binding_freqs_cpp.h \
    src/create_epitopeome_cpp.h \
    src/create_epitopeome_file_cpp.h \
    src/create_locatome_cpp.h \
    src/split_str_cpp.h

INCLUDEPATH += \
    cpp \
    src

RESOURCES += \
    epitopeome.qrc

################################################################################
# Compiling, linking and tools
################################################################################
# C++11
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

# High warning levels
# SFML goes bad with -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wnon-virtual-dtor -pedantic -Werror -Wshadow

# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {

  DEFINES += NDEBUG

  # GNU/Linux
  unix:!macx {
    # gprof
    QMAKE_CXXFLAGS += -pg
    QMAKE_LFLAGS += -pg
  }
}

CONFIG(debug, debug|release) {

  # GNU/Linux
  unix:!macx {
    # gcov
    QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
    LIBS += -lgcov

    # helgrind, for helgrind and memcheck
    QMAKE_LFLAGS += -pthread -Wl,--no-as-needed

    # UBSAN
    QMAKE_CXXFLAGS += -fsanitize=undefined
    QMAKE_LFLAGS += -fsanitize=undefined
    LIBS += -lubsan
  }
}

################################################################################
# Boost
################################################################################

# Boost.Test
LIBS += -lboost_unit_test_framework

################################################################################
# Qt5
################################################################################
QT += core gui

# QResources give this error
QMAKE_CXXFLAGS += -Wno-unused-variable

# Fixes
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable
