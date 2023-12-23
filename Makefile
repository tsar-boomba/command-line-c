.PHONY: all clean

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

CC = clang
CFLAGS = -Wall -Wextra -std=c11 -pedantic
LDFLAGS = -lm

BIN_PATHS := $(wildcard bin/*/)

BINS := $(BIN_PATHS:bin/%/=%)
# Build echo by default
BIN ?= echo
BIN_SRC := $(shell find bin/${BIN}/src -type f -name '*.c')

all: lib bins

lib: ${wildcard lib/*.c}

lib/%.c:
	@mkdir -p out/lib
	${CC} ${CFLAGS} -c -o out/lib/${strip ${patsubst lib/%.c, %.o, $@}} $@

bins: ${BINS:%=bin-%}

bin-%:
	@$(MAKE) bin BIN=${strip ${patsubst bin-%, %, $@}}

# Make a single bin based on BIN variable
bin: ${BIN_SRC:bin/${BIN}/src/%.c=bin/${BIN}/src/%.o}
	@mkdir -p out/bin
	${CC} ${LDFLAGS} -o out/bin/${BIN} bin/${BIN}/src/main.c

# Compile "bin/BIN/src/folder/file.c" to "out/obj/BIN/folder/file.o"
# foler/file.o
bin/${BIN}/src/%.o: bin/${BIN}/src/%.c
	@mkdir -p out/obj/${BIN}/${dir ${strip ${patsubst bin/${BIN}/src/%.o, %.o, $@}}}
	${CC} ${CFLAGS} -c -o out/obj/${BIN}/${strip ${patsubst bin/${BIN}/src/%.o, %.o, $@}} $<

clean:
	@rm -rf out/
