CC=gcc
#CCFLAGS=-Wall
CCFLAGS=-g
LDFLAGS=-lm
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=hexa

all: $(TARGET)

$(TARGET): $(OBJECTS);\
    $(CC) -g -o $@ $^ $(LDFLAGS) 

%.o: %.c %.h;\
    $(CC) $(CCFLAGS) -c $<

%.o: %.c;\
    $(CC) $(CCFLAGS) -c $<

clean:;\
    rm -f *.o *-*.pgm $(TARGET);\