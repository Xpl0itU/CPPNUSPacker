TARGET_EXEC := CPPNUSPacker

CXXFLAGS := -g -std=c++20 -Ofast -fpermissive
LDFLAGS := -lcrypto

BUILD_DIR := build
SRC_DIRS := src
INCLUDE_DIRS := include

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
INC_DIRS := $(shell find $(INCLUDE_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

./$(TARGET_EXEC): $(OBJS)
	g++ $(CXXFLAGS) $(INC_FLAGS) $(OBJS) -o $@ $(LDFLAGS)
#	strip -s $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	g++ $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf CPPNUSPacker $(BUILD_DIR)