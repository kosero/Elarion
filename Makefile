CC = clang++
CFLAGS = -std=c++20 -pedantic -Wall -Wextra -O3 -Wconversion -Wnull-dereference -pipe -fno-common -fstack-protector-strong -I$(INC_DIR)
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL -lenet

SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build

SRCS := $(shell find $(SRC_DIR) -name '*.cxx')
OBJS := $(patsubst $(SRC_DIR)/%.cxx,$(BUILD_DIR)/%.o,$(SRCS))
TARGET = $(BUILD_DIR)/Elarion

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cxx
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(TARGET)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(BUILD_DIR)

