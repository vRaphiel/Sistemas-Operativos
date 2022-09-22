.PHONY: clean all

BIN = \
	echo_client_inet                     \
	server-blocking				 \
	server-blocking_2				\
	server-fcntl					\
	server-pselect					\
	server-pselect-full


SRC = $(BIN:=.c)

.c:
	$(CC) -D_POSIX_C_SOURCE=200809L $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

all: $(BIN)

clean:
	rm -f $(BIN)
