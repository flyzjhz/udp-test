.PHONY:clean
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))
CC=gcc
LIBS = 
LDFLAGS:= -lpthread
TARGET=server
$(TARGET):$(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)
all:
	$(TARGET)
clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
