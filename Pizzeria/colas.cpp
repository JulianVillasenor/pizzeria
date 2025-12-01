// -----------------------------------------------------------
// colas.cpp
// Implementación básica de las colas utilizadas en la simulación.
//
// Nota:
//  - Se utiliza una clase interna ColaImpl con std::queue y std::mutex
//    para representar una cola protegida frente a accesos concurrentes.
//  - Por ahora no se usan condition_variable para bloquear hilos cuando
//    la cola está vacía. Eso se puede agregar como mejora.
// -----------------------------------------------------------

#include "colas.h"
#include <queue>
#include <mutex>

// Clase interna que implementa una cola protegida con mutex.
class ColaImpl {
public:
    // Inserta un pedido en la cola.
    void push(const Pedido& p) {
        std::lock_guard<std::mutex> lock(mtx_);
        cola_.push(p);
    }

    // Saca un pedido de la cola.
    // Devuelve true si se obtuvo un elemento, false si la cola estaba vacía.
    bool pop(Pedido& p) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (cola_.empty()) {
            return false;
        }
        p = cola_.front();
        cola_.pop();
        return true;
    }

private:
    std::queue<Pedido> cola_; // Estructura FIFO de pedidos
    std::mutex mtx_;          // Protege el acceso concurrente a la cola
};

// Instancias globales internas (una para cada tipo de cola).
// Podría cambiarse a miembros dentro de Contexto o hacerse más flexible,
// pero para esta práctica es suficiente.
static ColaImpl colaPedidosImpl;
static ColaImpl colaPizzasImpl;

// Métodos de ColaPedidos que delegan en la implementación interna
void ColaPedidos::push(const Pedido& p) {
    colaPedidosImpl.push(p);
}

bool ColaPedidos::pop(Pedido& p) {
    return colaPedidosImpl.pop(p);
}

// Métodos de ColaPizzasListas que delegan en la implementación interna
void ColaPizzasListas::push(const Pedido& p) {
    colaPizzasImpl.push(p);
}

bool ColaPizzasListas::pop(Pedido& p) {
    return colaPizzasImpl.pop(p);
}
