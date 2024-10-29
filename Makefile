CLIENT_DIR = client
SERVER_DIR = server

all: build

build:
	$(MAKE) -C $(CLIENT_DIR)
	$(MAKE) -C $(SERVER_DIR)

clean:
	$(MAKE) -C $(CLIENT_DIR) clean
	$(MAKE) -C $(SERVER_DIR) clean
