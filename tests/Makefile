SRC_DIR := src
BIN_DIR := bin

SRC := $(wildcard $(SRC_DIR)/*.c)
BIN := $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%)

CFLAGS  := -g -Wall -Werror
CPPFLAGS := -I..
LDFLAGS := -L..
LDLIBS  := -lmem

.PHONY: all clean

all: $(BIN)

$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

$(BIN_DIR):
	mkdir -p $@

clean:
	$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
