PROGRAM = TTMS

C_SOURCES = $(shell find ./ -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

myArgs = -Wall -g

ALL: $(PROGRAM) 

$(PROGRAM):$(C_OBJECTS)
	@echo link...
	gcc $^ -o $@ $(myArgs)

$(C_OBJECTS):%.o:%.c
	@echo compile...
	gcc -c $< -o $@ $(myArgs)

clean:
	-rm -rf $(C_OBJECTS) $(PROGRAM)

.PHONY: clean ALL
