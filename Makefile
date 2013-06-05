CXX=g++
AR =ar

SRC_DIR=src
SRC_FILES=$(shell ls $(SRC_DIR)/*.cc)
OBJ_FILES=$(SRC_FILES:%.cc=%.o)
LIB_DIR=lib
#TEXTURE_PATH=-texturepath /Users/urota/work/textures/
CXX_FLAGS=`ode-config --cflags` -Wall -O2
INCLUDE_DIRS:=-I./include

all: library samples

%.o:%.cc
	$(CXX) -c $(CXX_FLAGS) $(LD_FLAGS) $(FRAMEWORK_FLAGS) $(INCLUDE_DIRS) -o $@ $<

library:$(OBJ_FILES)
	mkdir -p lib
	$(AR) rc $(LIB_DIR)/libeasyode.a $(OBJ_FILES)

samples: library
	$(MAKE) -C sample

.PHONY: clean
clean:
	rm -rf $(OBJ_FILES) $(LIB_DIR)
	$(MAKE) clean -C sample

