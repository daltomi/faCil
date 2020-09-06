APP := test

CLIBS ?=
CLIBS_RELEASE := -Wl,-s,--sort-common,--as-needed,-z,relro

CFLAGS += -std=gnu99 -D_GNU_SOURCE_
CFLAGS_RELEASE := -O3 -flto -fstack-protector-strong
CFLAGS_DEBUG := -Wall -Wextra -pedantic -O0 -ggdb -DDEBUG

CC := gcc

SOURCE := $(wildcard *.c)

OBJ := $(patsubst %.c,%.o,$(SOURCE))

release: CFLAGS += $(CFLAGS_RELEASE)
release: CLIBS += $(CLIBS_RELEASE)
release: $(APP)

debug: CFLAGS += $(CFLAGS_DEBUG)
debug: $(APP)

$(APP): $(OBJ)
		$(CC) $(OBJ) $(CLIBS) -o $(APP)

.o:
		$(CC) $(CFLAGS) -c $<

clean:
		rm $(APP) *.o

