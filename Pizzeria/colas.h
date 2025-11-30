#pragma once
#include "pedido.h"

class ColaPedidos {
public:
    void push(const Pedido& p);
    bool pop(Pedido& p);
};

class ColaPizzasListas {
public:
    void push(const Pedido& p);
    bool pop(Pedido& p);
};
