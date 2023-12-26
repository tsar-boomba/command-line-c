.PHONY: all clean

CC = clang
CFLAGS = -Wall -Wextra -std=c17 -pedantic -Ilib
LDFLAGS = -lm

BIN_PATHS := $(wildcard bin/*/)

BINS := $(BIN_PATHS:bin/%/=%)
# Build echo by default
BIN ?= echo
BIN_SRC := $(shell find bin/${BIN}/src -type f -name '*.c')

all: lib bins
	@echo "All done! :D"

lib: ${patsubst lib/%.c, lib/%.o, ${wildcard lib/*.c}}

lib/%.o: lib/%.c
	@echo "[Compiling library: $<]"
	@mkdir -p out/lib
	@${CC} ${CFLAGS} -c -o out/${strip ${patsubst lib/%.c, %.o, $@}} $<

bins: ${BINS:%=bin-%}

bin-%:
	@$(MAKE) bin BIN=${strip ${patsubst bin-%, %, $@}}

# Make a single bin based on BIN variable
bin: ${BIN_SRC:bin/${BIN}/src/%.c=bin/${BIN}/src/%.o}
	@echo "[Linkning binary: ${BIN}]"
	@mkdir -p out/bin
	@${CC} ${LDFLAGS} -o out/bin/${BIN} ${wildcard out/lib/*.o} ${BIN_SRC:bin/${BIN}/src/%.c=out/obj/${BIN}/%.o}

# Compile "bin/BIN/src/folder/file.c" to "out/obj/BIN/folder/file.o"
# foler/file.o
bin/${BIN}/src/%.o: bin/${BIN}/src/%.c
	@echo "[Compiling source: $<]"
	@mkdir -p out/obj/${BIN}/${dir ${strip ${patsubst bin/${BIN}/src/%.o, %.o, $@}}}
	@${CC} ${CFLAGS} -c -o out/obj/${BIN}/${strip ${patsubst bin/${BIN}/src/%.o, %.o, $@}} $<

clean:
	@rm -rf out/
