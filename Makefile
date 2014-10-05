NAME:=course.exe

CC:= gcc
LN:= gcc
INCLUDES:= -Isrc -Iinclude
CFLAGS:= $(INCLUDES)
LIBS:=

SOURCE:= $(wildcard src/*)
OBJ_FILES:= $(patsubst %.c, obj/%.o, $(SOURCE))

all: bin/$(NAME)


bin/$(NAME): $(OBJ_FILES)
	mkdir -p $(@D)
	$(LN) $^ $(LDFLAGS) -o $@

obj/%.o:%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf obj/ bin/
