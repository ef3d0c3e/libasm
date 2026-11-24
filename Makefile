NAME := libasm.a
NA := nasm
NAFLAGS := -f elf64
CFLAGS ?= -std=c99 -Wall -Wextra -Wconversion -pedantic -Og -ggdb
ARFLAGS := rcs

SRCS := $(wildcard src/*.s)
OBJS := $(addprefix build/,$(SRCS:.s=.o))
TEST_SRCS := $(wildcard test/*.c)
TEST_OBJS := $(addprefix build/,$(TEST_SRCS:.c=.o))

build/%.o: %.s
	@mkdir -p $(@D)
	$(NA) $(NAFLAGS) $< -o $@

build/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I./src -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

tests: $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) -I./src $(TEST_OBJS) -o $@ $(NAME)
	./tests

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	$(RM) -rf ./build
	$(RM) -f $(NAME)
	$(RM) -f tests

.PHONY: clean
re: clean all
