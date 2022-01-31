CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu90 -ggdb3 -c -I. -Itransaction/ -Iprovided/ -I../../crypto -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

SRC0 = $(wildcard *.c) $(wildcard transaction/*.c) $(wildcard provided/*.c)
OBJS = $(patsubst %.c, %.o, $(SRC))
STATIC = libhblk_blockchain.a

.PHONY: $(STATIC)

$(STATIC): $(OBJS)
	ar  rcs $(STATIC) $(OBJS)
