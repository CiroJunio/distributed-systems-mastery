#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <exception>

// CAPÍTULO 1: Abertura (Openness)
// Sistemas distribuídos precisam de interfaces padronizadas para que
// diferentes componentes (drones de marcas diferentes) possam conversar.
struct DroneStatus {
    int drone_id;
    double pos_x;
    double pos_y;
    long long timestamp; // A "Âncora de Causalidade" do sistema.
};

// CAPÍTULO 1: Robustez e Tratamento de Erros
// Em SD, falhas são a regra, não a exceção. 
// "Fail-Fast" é uma estratégia de sobrevivência.
class TemporalAnomalyException : public std::exception {
    const char* what() const noexcept override { return "ANOMALIA TEMPORAL: Dado do passado recebido!"; }
};

// Exemplo de Transparência de Falha (futura): avisar quando um nó sumiu.
class NodePartitionException : public std::exception {
    const char* what() const noexcept override { return "PARTIÇÃO DE REDE: Nó inacessível!"; }
};

#endif