#include "engine.hpp"
#include <iostream>
#include <algorithm>
#include "../include/types.hpp"

// CAPÍTULO 1: Transparência de Falha e Consistência
// O Ingestor atua como o "filtro de realidade" do sistema.
void TelemetryMiddleware::ingest_telemetry(DroneStatus data) {
    // Buscamos o estado atual do drone. 
    // Em SD, o "Estado" é a única verdade, pois a rede é instável.
    auto it = global_fleet_state.find(data.drone_id);
    
    // CAPÍTULO 1: Lidando com as "Falácias da Computação Distribuída"
    // Falácia #1: A rede é confiável. (Mentira: mensagens atrasam e chegam fora de ordem).
    if (it != global_fleet_state.end()) {
        // MECANISMO DE COERÊNCIA: Se o dado novo é mais velho que o que já temos,
        // a rede nos entregou uma mensagem "do passado".
        if (data.timestamp <= it->second.timestamp) {
            // Rejeitar o passado garante a CONSISTÊNCIA SEQUENCIAL do sistema.
            throw TemporalAnomalyException(); 
        }
    }
    // TRANSPARÊNCIA DE ATUALIZAÇÃO: O sistema esconde a complexidade da rede
    // e mantém apenas a versão mais recente e válida para o usuário.
    global_fleet_state[data.drone_id] = data;
}

// CAPÍTULO 1: Transparência de Acesso
// O usuário pede um dado e o middleware esconde se ele existe ou se falhou.
DroneStatus TelemetryMiddleware::get_unified_status(int drone_id) {
    // O middleware decide o que é uma resposta "coerente".
    if (global_fleet_state.count(drone_id)) {
        return global_fleet_state[drone_id];
    }
    else {
        // Se o drone não existe, retornamos um estado neutro.
        // Isso mantém a "Single System Image" (imagem de sistema único).
        return DroneStatus{drone_id, 0, 0, 0};
    }
}

// CAPÍTULO 1: Visão Coerente (Single System Image)
// O objetivo final de um sistema distribuído é parecer um computador só.
std::vector<DroneStatus> TelemetryMiddleware::get_all_drones() {
    std::vector<DroneStatus> fleet;
    // O Middleware agrega os dados de vários nós independentes (drones)...
    for (auto const& [id, status] : global_fleet_state) {
        // ...e os entrega como uma coleção única para a aplicação superior.
        fleet.push_back(status);
    }
    return fleet;
}