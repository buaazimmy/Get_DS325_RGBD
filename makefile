INC_DIR = ./inc
DEBUG = -g #-pg
INCLUDE = -I/opt/softkinetic/DepthSenseSDK/include
CFLAGS = -pipe  -Wall -Wmissing-prototypes -Wmissing-declarations $(DEBUG) $(INCLUDE) -D_REENTRANT -D_GNU_SOURCE
CFLAGS += -O6
CFLAGS += $(shell if [ -d /usr/include/mysql ]; then echo "-I/usr/include/mysql"; fi)
CFLAGS += $(shell if [ -d /usr/local/include/mysql ]; then echo "-I/usr/local/include/mysql"; fi)
LIBS = -L/opt/softkinetic/DepthSenseSDK/lib -lDepthSense -lDepthSensePlugins -lturbojpeg


HEADS = $(wildcard $(INC_DIR)/*.h)

SOURCES = $(wildcard ./src/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
TARGET = DepthSense
CC=gcc


all: ${TARGET}
${TARGET}: $(OBJS)
	g++ $(INCLUDE) depthsense.cpp -o ${TARGET} $(LIBS)

clean:
	rm -f ./src/*.o ${TARGET} 
