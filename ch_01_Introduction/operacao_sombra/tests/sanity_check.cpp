#include "../core/engine.hpp"
#include <cassert>
#include <iostream>

// CAPÍTULO 1: Testando a Promessa de Coerência
void test_temporal_coherence() {
    TelemetryMiddleware middleware;
    
    // Simulamos a rede enviando dados fora de ordem:
    DroneStatus future_data = {1, 10.0, 10.0, 2000}; // Chega primeiro
    DroneStatus past_data = {1, 11.0, 11.0, 1000};   // Chega depois (atrasado)

    middleware.ingest_telemetry(future_data);
    
    try {
        // O sistema deve ser inteligente o suficiente para saber que
        // 1000 vem antes de 2000, mesmo que tenha chegado depois.
        middleware.ingest_telemetry(past_data);
    } catch (const TemporalAnomalyException& e) {
        // Se cair aqui, o Middleware cumpriu o seu papel de proteger a verdade.
        std::cout << "Sanity Check: O middleware rejeitou o passado corretamente." << std::endl;
        return;
    }
    
    // Se o sistema aceitar o dado velho, ele quebrou a "Single System Image".
    assert(false && "O sistema aceitou um dado do passado sem disparar exceção!");
}