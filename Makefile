#!/usr/bin/make -f

# sudo apt install pkg-config cython3 libpython3-dev zlib1g-dev libzstd-dev \
#     libxml2-dev libsdl2-dev libsdl2-image-dev

PACKAGES= python3-embed

CC= gcc
CXX= g++
RM= rm --force --verbose

PYTHON= python3
CYTHON= cython3

PKGCONFIG= pkg-config

ifndef PACKAGES
PKG_CONFIG_CFLAGS=
PKG_CONFIG_LDFLAGS=
PKG_CONFIG_LIBS=
else
PKG_CONFIG_CFLAGS=`pkg-config --cflags $(PACKAGES)`
PKG_CONFIG_LDFLAGS=`pkg-config --libs-only-L $(PACKAGES)`
PKG_CONFIG_LIBS=`pkg-config --libs-only-l $(PACKAGES)`
endif

CFLAGS= \
	-Wall \
	-fwrapv \
	-fstack-protector-strong \
	-Wall \
	-Wformat \
	-Werror=format-security \
	-Wdate-time \
	-D_FORTIFY_SOURCE=2 \
	-fPIC

LDFLAGS= \
	-Wl,-O1 \
	-Wl,-Bsymbolic-functions \
	-Wl,-z,relro \
	-Wl,--as-needed \
	-Wl,--no-undefined \
	-Wl,--no-allow-shlib-undefined

CYFLAGS= \
	-3 \
	--cplus \
	-X language_level=3 \
	-X boundscheck=False

CSTD=-std=c17
CPPSTD=-std=c++17

OPTS= -O2 -g

DEFS= \
	-DWANT_ZLIB \
	-DWANT_ZSTD \
	-DMINIZ_NO_STDIO \
	-DNDEBUG

INCS= \
	-Isource

CYINCS= \
	-Icython

LIBS=

all: general_simple_sample.bin general_advanced_sample.bin efll.so

PYX_SRCS= \
	examples/cython/example.pyx

C_SRCS= \

CPP_SRCS= \
	source/FuzzyComposition.cpp \
	source/Fuzzy.cpp \
	source/FuzzyInput.cpp \
	source/FuzzyIO.cpp \
	source/FuzzyOutput.cpp \
	source/FuzzyRuleAntecedent.cpp \
	source/FuzzyRuleConsequent.cpp \
	source/FuzzyRule.cpp \
	source/FuzzySet.cpp

PYX_CPPS= $(subst .pyx,.cpp,$(PYX_SRCS))
PYX_OBJS= $(subst .pyx,.o,$(PYX_SRCS))

OBJS= $(PYX_OBJS) $(subst .c,.o,$(C_SRCS)) $(subst .cpp,.o,$(CPP_SRCS))

SIMPLE_SRCS= examples/general_simple_sample/general_simple_sample.cpp
SIMPLE_OBJS= $(subst .cpp,.o,$(SIMPLE_SRCS)) $(OBJS)

general_simple_sample.bin: $(SIMPLE_OBJS)
	$(CXX) $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $+ $(LIBS) $(PKG_CONFIG_LIBS)

ADVANCED_SRCS= examples/general_simple_sample/general_simple_sample.cpp
ADVANCED_OBJS= $(subst .cpp,.o,$(ADVANCED_SRCS)) $(OBJS)

general_advanced_sample.bin: $(ADVANCED_OBJS)
	$(CXX) $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $+ $(LIBS) $(PKG_CONFIG_LIBS)

efll.so: $(OBJS)
	$(CXX) -shared $(CPPSTD) $(CSTD) $(LDFLAGS) $(PKG_CONFIG_LDFLAGS) -o $@ $+ $(LIBS) $(PKG_CONFIG_LIBS)

%.o: %.cpp
	$(CXX) $(CPPSTD) $(OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

%.o: %.c
	$(CC) $(CSTD) $(OPTS) -o $@ -c $< $(DEFS) $(INCS) $(CFLAGS) $(PKG_CONFIG_CFLAGS)

%.cpp: %.pyx
	$(CYTHON) $(CYFLAGS) $(CYINCS) -o $@ $<

clean:
	$(RM) $(OBJS)
	$(RM) $(subst .pyx,.cpp,$(PYX_SRCS))
	$(RM) $(subst .pyx,_api.cpp,$(PYX_SRCS))
	$(RM) $(subst .pyx,.h,$(PYX_SRCS))
	$(RM) $(subst .pyx,_api.h,$(PYX_SRCS))
	@find . -name '*.o' -exec $(RM) {} +
	@find . -name '*.a' -exec $(RM) {} +
	@find . -name '*.so' -exec $(RM) {} +
	@find . -name '*.pyc' -exec $(RM) {} +
	@find . -name '*.pyo' -exec $(RM) {} +
	@find . -name '*.bak' -exec $(RM) {} +
	@find . -name '*~' -exec $(RM) {} +
	@$(RM) core

.PHONY: all clean
