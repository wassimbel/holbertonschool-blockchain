CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -I. -lssl -lcrypto
SRC = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
STATIC = libhblk_crypto.a

.PHONY: $(STATIC)

$(STATIC): $(OBJS)
	ar  rcs $(STATIC) $(OBJS)

