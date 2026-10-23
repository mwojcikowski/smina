BASE ?= /ucrt64
C_PLATFORM = -DWIN32 -D_WIN32 -DBOOST_TIMER_ENABLE_DEPRECATED
GPP = g++
CPP_STANDARD = -std=c++14
C_OPTIONS = -O3 -DNDEBUG -g -march=native
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

# MSYS2 UCRT64 Boost libraries use the -mt suffix
ifneq ($(wildcard $(BASE)/lib/libboost_filesystem-mt.*),)
    BOOST_LIBS = -lboost_iostreams-mt -lboost_timer-mt -lboost_thread-mt -lboost_serialization-mt -lboost_filesystem-mt -lboost_program_options-mt -lboost_date_time-mt
endif

PLATFORM_LIBS = -lws2_32 -lmswsock
LDFLAGS = -static-libgcc -static-libstdc++
ALL_TARGETS = smina tosmina fromsmina libsmina.a copy_plugins

include ../../makefile_common

# Automatically deploy OpenBabel format plugins next to executables
copy_plugins:
	@if [ -d "$(BASE)/lib/openbabel" ]; then cp -u $(BASE)/lib/openbabel/*/*.obf . 2>/dev/null || true; fi



