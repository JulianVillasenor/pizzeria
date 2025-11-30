#pragma once

#include <atomic>
#include "colas.h"

struct Contexto {
    int numClientes;
    int numCocineros;
    int numRepartidores;

    // Ya no se generarán más pedidos cuando sea true
    std::atomic<bool> pedidosTerminados{false};

    // Colas compartidas
    ColaPedidos* colaPedidos{nullptr};
    ColaPizzasListas* colaPizzas{nullptr};

    // Estadísticas
    std::atomic<int> pedidosGenerados{0};
    std::atomic<int> pedidosHorneados{0};
    std::atomic<int> pedidosEntregados{0};
};
