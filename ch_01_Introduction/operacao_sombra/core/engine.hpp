#include "../include/types.hpp"
#include <map>
#include <vector>

class TelemetryMiddleware {
private:
    // O seu estado interno (Cuidado com os 50MB!)
    std::map<int, DroneStatus> global_fleet_state;

public:
    // CAMADA 2: Transparência de Falha
    // Se o nó local falhar, deve consultar os peers
    void ingest_telemetry(DroneStatus data);
    
    // CAMADA 3: Coerência (Mecanismo de Desempate)
    DroneStatus get_unified_status(int drone_id);
    
    std::vector<DroneStatus> get_all_drones();
};