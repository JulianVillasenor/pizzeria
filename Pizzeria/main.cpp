// -----------------------------------------------------------
// main.cpp
// INTEGRANTE 1 — Administrador / MainController (Julian)
//
// Este archivo coordina toda la simulación:
//  - Define parámetros globales (N cocineros, M repartidores, clientes)
//  - Crea el contexto compartido
//  - Crea e inicia los hilos de:
//      * TomarPedidos
//      * Cocineros
//      * Repartidores
//  - Espera a que terminen y muestra estadísticas finales.
// -----------------------------------------------------------

#include <iostream>
#include <vector>
#include <thread>

#include "hilos.h"
#include "contexto.h"

// Parámetros por defecto de la simulación.
// Se pueden ajustar para hacer pruebas con más carga.
constexpr int NUM_CLIENTES_DEFAULT     = 5; // Número de clientes a simular
constexpr int NUM_COCINEROS_DEFAULT    = 3; // Número de cocineros (hilos)
constexpr int NUM_REPARTIDORES_DEFAULT = 2; // Número de repartidores (hilos)

int main() {
    std::cout << "=== Simulacion Pizzeria Multihilo ===\n";

    // 1. Definir parámetros globales
    int numClientes     = NUM_CLIENTES_DEFAULT;
    int numCocineros    = NUM_COCINEROS_DEFAULT;
    int numRepartidores = NUM_REPARTIDORES_DEFAULT;

    // 2. Crear las colas compartidas
    ColaPedidos colaPedidos;       // Cola de pedidos por atender
    ColaPizzasListas colaPizzas;  // Cola de pizzas ya horneadas

    // 3. Preparar el contexto global que se pasará por referencia a los hilos
    Contexto ctx;
    ctx.numClientes     = numClientes;
    ctx.numCocineros    = numCocineros;
    ctx.numRepartidores = numRepartidores;
    ctx.colaPedidos     = &colaPedidos;
    ctx.colaPizzas      = &colaPizzas;

    // 4. Crear el vector donde guardaremos los hilos
    std::vector<std::thread> hilos;

    // 4.1 Hilo de TomarPedidos (Integrante 2)
    hilos.emplace_back([&ctx]() {
        hiloTomarPedidos(ctx);
    });

    // 4.2 Hilos de cocineros (Integrante 4)
    for (int i = 0; i < numCocineros; ++i) {
        hilos.emplace_back([&ctx, i]() {
            hiloCocinero(ctx, i);
        });
    }

    // 4.3 Hilos de repartidores (Integrante 6)
    for (int j = 0; j < numRepartidores; ++j) {
        hilos.emplace_back([&ctx, j]() {
            hiloRepartidor(ctx, j);
        });
    }

    // 5. Esperar a que todos los hilos terminen
    for (auto& th : hilos) {
        if (th.joinable()) {
            th.join();
        }
    }

    // 6. Mostrar estadísticas finales de la simulación
    std::cout << "\n=== Estadisticas finales ===\n";
    std::cout << "Pedidos generados:  " << ctx.pedidosGenerados.load() << "\n";
    std::cout << "Pedidos horneados:  " << ctx.pedidosHorneados.load() << "\n";
    std::cout << "Pedidos entregados: " << ctx.pedidosEntregados.load() << "\n";
    std::cout << "Simulacion finalizada exitosamente.\n";

    return 0;
}
