# Comandos de Automação SRE
.PHONY: setup build run clean profile monitor

setup:
	docker compose build

build:
	g++ -O3 -std=c++17 core/engine.cpp io/network_stub.cpp tests/sanity_check.cpp -o build/operacao_sombra

run:
	docker compose up

clean:
	docker compose down
	rm -rf build/*

# MONITOR DE SINAIS VITAIS: Acompanhe o estrangulamento em tempo real
monitor:
	docker stats --format "table {{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}\t{{.MemPerc}}\t{{.NetIO}}"

# Perfilamento simples de memória (Exige valgrind no host ou container)
profile:
	valgrind --tool=massif ./build/operacao_sombra