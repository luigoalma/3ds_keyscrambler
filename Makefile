CC = gcc
INCLUDE_CONST_C = 0
ifeq ($(INCLUDE_CONST_C),0)
	CFLAGS = -Wall -static-libgcc
else
	CFLAGS = -Wall -static-libgcc -DINCLUDE_CONSTANT_C
endif
TARGET = 3ds_keyscrambler
OBJS = src/main.o src/UnScrambler.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TARGET)
