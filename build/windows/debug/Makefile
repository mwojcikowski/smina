BASE ?= /ucrt64
C_PLATFORM = -DWIN32 -D_WIN32 -DBOOST_TIMER_ENABLE_DEPRECATED
GPP = g++
CPP_STANDARD = -std=c++14
C_OPTIONS = -O0 -g -Wall
BOOST_LIB_VERSION =
BOOST_INCLUDE = $(BASE)/include

# Support both openbabel3 (default in modern MSYS2) and openbabel-2.0
ifneq ($(wildcard $(BASE)/include/openbabel3),)
    OPENBABEL_INCLUDE = $(BASE)/include/openbabel3
else
    OPENBABEL_INCLUDE = $(BASE)/include/openbabel-2.0
endif

ifneq ($(wildcard $(BASE)/include/eigen3),)
    EIGEN_INCLUDE = -I $(BASE)/include/eigen3
endif

PLATFORM_LIBS = -lws2_32 -lmswsock
LDFLAGS = -static-libgcc -static-libstdc++

include ../../makefile_common
