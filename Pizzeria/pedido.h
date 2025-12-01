#pragma once

// -----------------------------------------------------------
// pedido.h
// Estructura básica que representa un pedido de pizza.
// Este tipo se comparte entre las colas y los hilos.
// -----------------------------------------------------------
struct Pedido {
    int id_pedido;   // Identificador único del pedido
    int id_cliente;  // Identificador del cliente 
    int tipo_pizza;  //(entero, ej. 0,1,2)
};
