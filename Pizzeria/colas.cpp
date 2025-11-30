#include "colas.h"
#include <queue>
#include <mutex>

class ColaImpl {
public:
    void push(const Pedido& p) {
        std::lock_guard<std::mutex> lock(mtx_);
        cola_.push(p);
    }

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
    std::queue<Pedido> cola_;
    std::mutex mtx_;
};

// Instancias internas para cada cola
static ColaImpl colaPedidosImpl;
static ColaImpl colaPizzasImpl;

void ColaPedidos::push(const Pedido& p) {
    colaPedidosImpl.push(p);
}

bool ColaPedidos::pop(Pedido& p) {
    return colaPedidosImpl.pop(p);
}

void ColaPizzasListas::push(const Pedido& p) {
    colaPizzasImpl.push(p);
}

bool ColaPizzasListas::pop(Pedido& p) {
    return colaPizzasImpl.pop(p);
}
