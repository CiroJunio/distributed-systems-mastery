# Estágio 1: Compilação (O Forjador)
FROM alpine:3.18 AS builder
RUN apk add --no-cache g++ make cmake

WORKDIR /app
COPY . .
# Compilação estática para garantir portabilidade total no Alpine
RUN g++ -O3 -std=c++17 core/engine.cpp io/network_stub.cpp tests/sanity_check.cpp -o build/operacao_sombra

# Estágio 2: Runtime (A Trincheira)
FROM alpine:3.18
RUN apk add --no-cache libstdc++

WORKDIR /root/
COPY --from=builder /app/build/operacao_sombra .

# Comando padrão
ENTRYPOINT ["./operacao_sombra"]