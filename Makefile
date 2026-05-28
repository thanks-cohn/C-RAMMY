CC=gcc
CFLAGS=-Wall -Wextra -O2

all: rammyd rammyctl

rammyd: src/rammyd.c
	$(CC) $(CFLAGS) -o rammyd src/rammyd.c

rammyctl: src/rammyctl.c
	$(CC) $(CFLAGS) -o rammyctl src/rammyctl.c

smoke: all
	bash scripts/smoke_local.sh

clean:
	rm -f rammyd rammyctl
