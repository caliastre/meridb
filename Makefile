# -*- MakeFile -*-

TARGET := meridb

BUILD_DIR := build
SRC_DIR := src

CC := gcc
CFLAGS := -std=c99 -Wall -Wextra
CPPFLAGS := -I$(SRC_DIR) -MMD -MP

LIBS :=
LDFLAGS := $(addprefix -l,$(LIBS))

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $($(OBJS):.o=.d)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)

run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

-include $(DEPS)
