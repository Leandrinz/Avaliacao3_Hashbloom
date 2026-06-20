EXEC := bin/hashbloom
ARGS :=

CODIGOS := $(shell find ./programa/src/ -name "*.c")
FLAGS :=


# Roda casualmente o programa
normal: compilar
	@./$(EXEC) $(ARGS)


# Chama o GDB para fazer debug
debug d: FLAGS += -g
debug d: compilar
	gdb $(EXEC) -q


# Apenas compila o binário
compilar:
	@mkdir -p bin
	gcc $(FLAGS) $(CODIGOS) -o $(EXEC)


.PHONY: normal debug d compilar
