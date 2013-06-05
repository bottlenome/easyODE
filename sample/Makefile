CXX=g++

TARGET=sample sample13
TEXTURE_PATH=-texturepath /Users/urota/work/textures/
CXX_FLAGS=`ode-config --cflags` -Wall -O2
LD_FLAGS:=-ldrawstuff -leasyode
CXX_FLAGS+=`ode-config --libs`
FRAMEWORK_FLAGS=-framework GLUT -framework OpenGL
INCLUDE_DIRS:=-I../include
LIB_DIRS:=-L../lib/

all: $(TARGET)

sample:sample.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LIB_DIRS) $(LD_FLAGS) $(FRAMEWORK_FLAGS) $(INCLUDE_DIRS)

sample13:sample13.cc
	$(CXX) -o $@ $^ $(CXX_FLAGS) $(LIB_DIRS) $(LD_FLAGS) $(FRAMEWORK_FLAGS) $(INCLUDE_DIRS)

.PHONY:clean
clean:
	rm -rf $(TARGET)

