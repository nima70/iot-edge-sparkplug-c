CC = gcc

# Directories
SRC_DIR = ./src
INCLUDE_DIR = ./include
LIB_DIR = ./lib

# Output
TARGET_PUB = publisher
TARGET_SUB = subscriber

# Files
PUB_SRC = $(SRC_DIR)/publisher.c
SUB_SRC = $(SRC_DIR)/subscriber.c

OBJS_PUB = $(PUB_SRC:.c=.o)
OBJS_SUB = $(SUB_SRC:.c=.o)

# Flags
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -g
LDFLAGS = -L$(LIB_DIR) -ltahu -lmosquitto

# Build
all: $(TARGET_PUB) $(TARGET_SUB)

$(TARGET_PUB): $(OBJS_PUB)
	$(CC) -o $@ $^ $(LDFLAGS)

$(TARGET_SUB): $(OBJS_SUB)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# Clean
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET_PUB) $(TARGET_SUB)
