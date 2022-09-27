SRC_DIR := src
BIN_DIR := bin

SRC := $(wildcard $(SRC_DIR)/*.c)
BIN := $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

CFLAGS  := -g -Wall -Werror
LDFLAGS := -L..
LDLIBS  := -lmem

.PHONY: all clean

all: $(BIN)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

$(BIN_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
