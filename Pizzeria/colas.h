#pragma once
#include "pedido.h"

// -----------------------------------------------------------
// colas.h
// Declaración de las colas utilizadas en la simulación.
// Integrantes 3 y 5 pueden extender estas clases si quieren
// más funcionalidad (estadísticas, capacidad máxima, etc.).
// -----------------------------------------------------------

class ColaPedidos {
public:
    // Inserta un pedido en la cola de pedidos.
    void push(const Pedido& p);

    // Obtiene un pedido de la cola.
    // Devuelve true si pudo sacar un pedido, false si no había.
    bool pop(Pedido& p);
};

class ColaPizzasListas {
public:
    // Inserta una pizza lista (pedido ya horneado) en la cola.
    void push(const Pedido& p);

    // Obtiene una pizza lista de la cola.
    // Devuelve true si pudo sacar algo, false si la cola estaba vacía.
    bool pop(Pedido& p);
};
