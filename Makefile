CC = gcc
OPTIMIZATION_FLAG = -O0
CC_FLAGS = -Wall -Wextra -pedantic $(OPTIMIZATION_FLAG) -std=c11

SRC_ENTRY_FILE = src/main.c
SRC_FILES = src/linebuffer.c src/word.c

BUILD_OUTFILE = justify

build: $(SRC_ENTRY_FILE) $(SRC_FILES)
	$(CC) $(SRC_ENTRY_FILE) $(SRC_FILES) -o $(BUILD_OUTFILE) $(CC_FLAGS)

build_optimized: $(SRC_ENTRY_FILE) $(SRC_FILES)
	$(MAKE) OPTIMIZATION_FLAG=-O3 build

memcheck:
	$(MAKE) build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(BUILD_OUTFILE)

clean:
	rm -f $(BUILD_OUTFILE) $(TEST_OUTFILE)

