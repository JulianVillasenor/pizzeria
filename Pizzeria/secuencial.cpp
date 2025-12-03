// -----------------------------------------------------------
// secuencial.cpp
// Versión secuencial de la simulación de la pizzería.
//
// NO usa hilos: procesa a cada cliente completo (pedido -> horno -> entrega)
// uno por uno.
// Sirve para comparar contra main.cpp (versión multihilo).
// -----------------------------------------------------------

#include <iostream>
#include <chrono>
#include <thread>

#include "contexto.h"   // Aquí debe estar definido Contexto y Pedido

// Si en tu proyecto Pedido está definido en otro header (por ejemplo "tipos.h"
// o "pedido.h"), inclúyelo también:
// #include "pedido.h"

int main() {
    std::cout << "=== Simulacion Pizzeria Secuencial ===\n";

    // Puedes ajustar este valor o preguntarlo al usuario
    int numClientes = 5;
    std::cout << "Numero de clientes a simular [defecto 5]: ";
    int entrada;
    if (std::cin >> entrada && entrada > 0) {
        numClientes = entrada;
    }

    // Preparamos el contexto (REUTILIZAMOS el mismo tipo Contexto del proyecto)
    Contexto ctx{};
    ctx.numClientes     = numClientes;
    ctx.numCocineros    = 1; // No se usan realmente en secuencial, pero por si acaso
    ctx.numRepartidores = 1;
    ctx.pedidosGenerados = 0;
    ctx.pedidosHorneados = 0;
    ctx.pedidosEntregados = 0;
    ctx.pedidosTerminados = false;

    // Medimos el tiempo total de la simulación
    auto inicio = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ctx.numClientes; ++i) {
        Pedido p;
        p.id_pedido  = i;
        p.id_cliente = i;
        p.tipo_pizza = i % 3; // por ejemplo, 3 tipos de pizza

        // 1) Llegada del cliente y toma del pedido
        ctx.pedidosGenerados++;
        std::cout << "[Secuencial] Pedido generado: " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // 2) Hornear la pizza
        std::cout << "[Secuencial] Horneando pedido " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        ctx.pedidosHorneados++;

        // 3) Entregar la pizza
        std::cout << "[Secuencial] Entregando pedido " << p.id_pedido << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        ctx.pedidosEntregados++;
    }

    ctx.pedidosTerminados = true;

    auto fin = std::chrono::high_resolution_clock::now();
    auto msTotales = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();

    std::cout << "\n=== Estadisticas finales (Secuencial) ===\n";
    std::cout << "Pedidos generados:  " << ctx.pedidosGenerados.load() << "\n";
    std::cout << "Pedidos horneados:  " << ctx.pedidosHorneados.load() << "\n";
    std::cout << "Pedidos entregados: " << ctx.pedidosEntregados.load() << "\n";
    std::cout << "Tiempo total:       " << msTotales << " ms\n";
    std::cout << "Simulacion secuencial finalizada.\n";

    return 0;
}