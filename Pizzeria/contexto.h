#pragma once

#include <atomic>
#include "colas.h"

// -----------------------------------------------------------
// contexto.h
// Estructura que contiene todo el contexto compartido
// entre los hilos de la simulación.
// Aquí se guardan:
//   - Parámetros globales (N cocineros, M repartidores, etc.)
//   - Referencias a las colas compartidas
//   - Estadísticas globales
// -----------------------------------------------------------

struct Contexto {
    int numClientes;      // Número total de clientes a atender
    int numCocineros;     // Número de hilos cocineros
    int numRepartidores;  // Número de hilos repartidores

    // Bandera que indica que ya no se generarán más pedidos.
    // Se pone en true cuando el hilo de TomarPedidos termina.
    std::atomic<bool> pedidosTerminados{false};

    // Punteros a las colas compartidas
    ColaPedidos* colaPedidos{nullptr};      // Cola de pedidos por atender
    ColaPizzasListas* colaPizzas{nullptr};  // Cola de pizzas listas para entregar

    // Contadores atómicos para estadísticas globales
    std::atomic<int> pedidosGenerados{0};   // Cuántos pedidos se generaron
    std::atomic<int> pedidosHorneados{0};   // Cuántos pedidos ya se hornearon
    std::atomic<int> pedidosEntregados{0};  // Cuántos pedidos se entregaron
};
