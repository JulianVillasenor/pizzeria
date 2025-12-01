// -----------------------------------------------------------
// hilos.cpp
// Implementación de la lógica de cada tipo de hilo:
//
//  - hiloTomarPedidos: simula la llegada de clientes y creación de pedidos.
//  - hiloCocinero: procesa pedidos de la cola de pedidos y "hornea" pizzas.
//  - hiloRepartidor: toma pizzas listas y las "entrega" a los clientes.
//
// Esta es una versión funcional básica que sirve de ejemplo.
// Los integrantes pueden extenderla con tiempos aleatorios, más datos,
// mediciones detalladas, etc.
// -----------------------------------------------------------

#include <iostream>
#include <thread>
#include <chrono>

#include "hilos.h"
#include "pedido.h"

// -----------------------------------------------------------
// hiloTomarPedidos
// Genera numClientes pedidos y los inserta en la cola de pedidos.
// Marca pedidosTerminados en true cuando ya no habrán más pedidos.
// -----------------------------------------------------------
void hiloTomarPedidos(Contexto& ctx) {
    for (int i = 0; i < ctx.numClientes; ++i) {
        Pedido p;
        p.id_pedido  = i;      // Usamos i como identificador de pedido
        p.id_cliente = i;      // En esta simulación, cliente = pedido
        p.tipo_pizza = i % 3;  // Tres tipos de pizza (0,1,2)

        ctx.colaPedidos->push(p);
        ctx.pedidosGenerados++;

        std::cout << "[TomarPedidos] Pedido generado: " << p.id_pedido << "\n";

        // Simula tiempo entre la llegada de clientes
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // No se generarán más pedidos
    ctx.pedidosTerminados = true;
    std::cout << "[TomarPedidos] No habra mas pedidos.\n";
}

// -----------------------------------------------------------
// hiloCocinero
// Extrae pedidos de la cola de pedidos, "hornea" las pizzas y
// las pasa a la cola de pizzas listas.
// Termina cuando ya no hay más pedidos por procesar y el hilo
// de TomarPedidos ha marcado pedidosTerminados.
// -----------------------------------------------------------
void hiloCocinero(Contexto& ctx, int idCocinero) {
    while (true) {
        Pedido p;
        bool ok = ctx.colaPedidos->pop(p);

        if (!ok) {
            // Si no hay pedido disponible
            if (ctx.pedidosTerminados) {
                // Ya no se generarán pedidos nuevos: podemos terminar
                break;
            }
            // Aún podrían llegar pedidos, esperamos un poco y seguimos
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        // Simula el proceso de hornear la pizza
        std::cout << "[Cocinero " << idCocinero
                  << "] Horneando pedido " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        ctx.pedidosHorneados++;
        ctx.colaPizzas->push(p);
    }

    std::cout << "[Cocinero " << idCocinero << "] Terminando hilo.\n";
}

// -----------------------------------------------------------
// hiloRepartidor
// Toma pizzas de la cola de pizzas listas y simula su entrega.
// Termina cuando:
//   - Ya no se generarán pedidos nuevos (pedidosTerminados == true), y
//   - La cantidad de pedidos horneados es igual a la cantidad
//     de pedidos generados (ya no queda nada pendiente).
// -----------------------------------------------------------
void hiloRepartidor(Contexto& ctx, int idRepartidor) {
    while (true) {
        Pedido p;
        bool ok = ctx.colaPizzas->pop(p);

        if (!ok) {
            // No hay pizzas listas en este momento.
            // Verificamos si ya se terminó todo el trabajo.
            if (ctx.pedidosTerminados &&
                ctx.pedidosHorneados.load() >= ctx.pedidosGenerados.load()) {
                // No habrá más pizzas que entregar, podemos terminar.
                break;
            }
            // Aún podrían llegar pizzas, esperamos un poco.
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        // Simula el proceso de entrega de la pizza al cliente
        std::cout << "[Repartidor " << idRepartidor
                  << "] Entregando pedido " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        ctx.pedidosEntregados++;
    }

    std::cout << "[Repartidor " << idRepartidor << "] Terminando hilo.\n";
}
