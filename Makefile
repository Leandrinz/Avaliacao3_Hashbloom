HBLOOM := ./bin/hashbloom
GERADOR := ./bin/gerador

SRC_HBLOOM := $(shell find ./programa/src/ -name "*.c")
SRC_GERADOR := $(shell find ./dados/ -name "*.c")

ARGS :=
FLAGS :=


# Roda casualmente o programa
normal: compilar
	@./$(HBLOOM) $(ARGS)


# Roda casualmente o gerador
gerador: compilar
	@./$(GERADOR) $(ARGS)


# Chama o GDB para fazer debug
debug d: FLAGS += -g
debug d: compilar
	gdb $(HBLOOM) -q


# Apenas compila os binários
compilar:
	@mkdir -p bin
	@gcc $(FLAGS) $(SRC_HBLOOM) -o $(HBLOOM)
	@gcc $(FLAGS) $(SRC_GERADOR) -o $(GERADOR)


.PHONY: normal gerador debug d compilar
