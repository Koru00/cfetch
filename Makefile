BINARY = cfetch
CODEDIRS = . lib
INCDIRS = . ./include/
BUILD_DIR = build

CC = gcc
OPT = -O0
DEPFLAGS = -MP -MD
CFLAGS = -Wall -Wextra -g -fsanitize=address $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)
LDFLAGS = -fsanitize=address   # <-- link-time flags

CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(CFILES))
DEPFILES = $(patsubst %.c, $(BUILD_DIR)/%.d, $(CFILES))

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)   # <-- add LDFLAGS here

$(BUILD_DIR)/%.o: %.c | $(dir $(BUILD_DIR)/%.o)
	$(CC) $(CFLAGS) -c -o $@ $<

$(dir $(BUILD_DIR)/%.o):
	mkdir -p $@

clean:
	rm -rf $(BINARY) $(BUILD_DIR)

distribute: clean
	tar zcvf dist.tgz *

diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

-include $(DEPFILES)

.PHONY: all clean distribute diff
