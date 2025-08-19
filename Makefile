# ========================
# Project configuration
# ========================
BINARY       := cfetch
SRC_DIRS     := src
INCLUDE_DIRS := . ./src/include
BUILD_DIR    := build

CC           := gcc
CFLAGS       := -Wall -Wextra -g -fsanitize=address -O0 -MP -MD $(foreach D,$(INCLUDE_DIRS),-I$(D))
LDFLAGS      := -fsanitize=address

# ========================
# Source / Object files
# ========================
# Find all .c files recursively in SRC_DIRS
CFILES := $(shell find $(SRC_DIRS) -type f -name '*.c')

# Map .c files to build directory .o files
OBJECTS  := $(patsubst %.c,$(BUILD_DIR)/%.o,$(CFILES))
DEPFILES := $(patsubst %.c,$(BUILD_DIR)/%.d,$(CFILES))

# ========================
# Default target
# ========================
all: $(BINARY)

# ========================
# Link the binary
# ========================
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# ========================
# Compile .c files into .o files
# ========================
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ========================
# Clean
# ========================
clean:
	rm -rf $(BINARY) $(BUILD_DIR)

# ========================
# Distribute
# ========================
distribute: clean
	tar zcvf dist.tgz *

# ========================
# Git diff helper
# ========================
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# ========================
# Include dependency files
# ========================
-include $(DEPFILES)

# ========================
# Phony targets
# ========================
.PHONY: all clean distribute diff
