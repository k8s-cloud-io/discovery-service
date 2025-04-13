CXX=c++
CPPFLAGS=-I./src/include -Wall -Wextra -Wno-deprecated -Wunused -pedantic -funroll-all-loops -Os -std=c++20 -MMD -MP
LDFLAGS=

CPPFLAGS+=$(shell pkg-config --cflags libxml-2.0) \
	$(shell pkg-config --cflags gio-2.0) \
	$(shell pkg-config --cflags gdk-pixbuf-2.0) \
	$(shell pkg-config --cflags sqlite3) \
	$(shell pkg-config --cflags libcurl) \
	$(shell pkg-config --cflags jsoncpp)

LDFLAGS+=$(shell pkg-config --libs libxml-2.0) \
	$(shell pkg-config --libs gio-2.0) \
	$(shell pkg-config --libs gdk-pixbuf-2.0) \
	$(shell pkg-config --libs sqlite3) \
	$(shell pkg-config --libs libcurl) \
	$(shell pkg-config --libs jsoncpp)

TARGET_EXEC := discovery-service
BUILD_DIR := .obj
SRCS := $(shell find src -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(TARGET_EXEC)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	mkdir -p ./bin
	$(CXX) $(CPPFLAGS) $(OBJS) -o ./bin/$(TARGET_EXEC) $(LDFLAGS)

# Build step for C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf ./build
	rm -rf ./bin
	rm -rf ./.bin
	rm -rf ./.obj
	rm -rf cmake-build*
	rm -f sqlite3.db
