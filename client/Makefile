CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -pthread
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC_DIR = src
NAME = client

all: $(NAME)

$(NAME): $(SRC_DIR)/*.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(NAME)
