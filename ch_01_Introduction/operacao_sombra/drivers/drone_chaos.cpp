#include "../include/types.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Este driver gera o "Lixo" que o teu sistema deve filtrar
std::vector<DroneStatus> generate_chaotic_data(int drone_id) {
    std::vector<DroneStatus> batch;
    long long now = 1700000000000;

    // Dado legítimo
    batch.push_back({drone_id, 10.0, 20.0, now});
    
    // DUPLICADO (Teste de Idempotência)
    batch.push_back({drone_id, 10.0, 20.0, now});
    
    // ANOMALIA TEMPORAL (Dado atrasado/Jitter)
    batch.push_back({drone_id, 9.5, 19.5, now - 5000}); 
    
    // MOVIMENTO IMPOSSÍVEL (O "Fantasma")
    batch.push_back({drone_id, 500.0, 900.0, now + 100});

    return batch;
}