#include <iostream>
#include <thread>
#include <chrono>
#include "hilos.h"
#include "pedido.h"

void hiloTomarPedidos(Contexto& ctx) {
    for (int i = 0; i < ctx.numClientes; ++i) {
        Pedido p;
        p.id_pedido  = i;
        p.id_cliente = i;
        p.tipo_pizza = i % 3;

        ctx.colaPedidos->push(p);
        ctx.pedidosGenerados++;

        std::cout << "[TomarPedidos] Pedido generado: " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    ctx.pedidosTerminados = true;
    std::cout << "[TomarPedidos] No habra mas pedidos.\n";
}

void hiloCocinero(Contexto& ctx, int idCocinero) {
    while (true) {
        Pedido p;
        bool ok = ctx.colaPedidos->pop(p);
        if (!ok) {
            if (ctx.pedidosTerminados) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        std::cout << "[Cocinero " << idCocinero << "] Horneando pedido " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        ctx.pedidosHorneados++;
        ctx.colaPizzas->push(p);
    }

    std::cout << "[Cocinero " << idCocinero << "] Terminando hilo.\n";
}

void hiloRepartidor(Contexto& ctx, int idRepartidor) {
    while (true) {
        Pedido p;
        bool ok = ctx.colaPizzas->pop(p);

        if (!ok) {
            if (ctx.pedidosTerminados &&
                ctx.pedidosHorneados.load() >= ctx.pedidosGenerados.load()) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            continue;
        }

        std::cout << "[Repartidor " << idRepartidor << "] Entregando pedido " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

        ctx.pedidosEntregados++;
    }

    std::cout << "[Repartidor " << idRepartidor << "] Terminando hilo.\n";
}
