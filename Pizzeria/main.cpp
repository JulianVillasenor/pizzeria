#include <iostream>
#include <vector>
#include <thread>

#include "hilos.h"
#include "contexto.h"

constexpr int NUM_CLIENTES_DEFAULT     = 5;
constexpr int NUM_COCINEROS_DEFAULT    = 3;
constexpr int NUM_REPARTIDORES_DEFAULT = 2;

int main() {
    std::cout << "=== Simulacion Pizzeria Multihilo ===\n";

    int numClientes     = NUM_CLIENTES_DEFAULT;
    int numCocineros    = NUM_COCINEROS_DEFAULT;
    int numRepartidores = NUM_REPARTIDORES_DEFAULT;

    ColaPedidos colaPedidos;
    ColaPizzasListas colaPizzas;

    Contexto ctx;
    ctx.numClientes     = numClientes;
    ctx.numCocineros    = numCocineros;
    ctx.numRepartidores = numRepartidores;
    ctx.colaPedidos     = &colaPedidos;
    ctx.colaPizzas      = &colaPizzas;

    std::vector<std::thread> hilos;

    // Hilo de tomar pedidos (Integrante 2)
    hilos.emplace_back([&ctx]() {
        hiloTomarPedidos(ctx);
    });

    // Hilos de cocineros (Integrante 4)
    for (int i = 0; i < numCocineros; ++i) {
        hilos.emplace_back([&ctx, i]() {
            hiloCocinero(ctx, i);
        });
    }

    // Hilos de repartidores (Integrante 6)
    for (int j = 0; j < numRepartidores; ++j) {
        hilos.emplace_back([&ctx, j]() {
            hiloRepartidor(ctx, j);
        });
    }

    // Esperar a que todos los hilos terminen
    for (auto& th : hilos) {
        if (th.joinable()) {
            th.join();
        }
    }

    std::cout << "\n=== Estadisticas finales ===\n";
    std::cout << "Pedidos generados:  " << ctx.pedidosGenerados.load() << "\n";
    std::cout << "Pedidos horneados:  " << ctx.pedidosHorneados.load() << "\n";
    std::cout << "Pedidos entregados: " << ctx.pedidosEntregados.load() << "\n";
    std::cout << "Simulacion finalizada exitosamente.\n";

    return 0;
}
