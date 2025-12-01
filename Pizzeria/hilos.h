#pragma once
#include "contexto.h"

// -----------------------------------------------------------
// hilos.h
// Declaración de las funciones que representan
// la lógica de cada tipo de hilo de la simulación.
//
// Integrante 2  →  hiloTomarPedidos
// Integrante 4  →  hiloCocinero
// Integrante 6  →  hiloRepartidor
// -----------------------------------------------------------

// Hilo que simula la llegada de clientes y creación de pedidos.
void hiloTomarPedidos(Contexto& ctx);

// Hilo que simula a un cocinero horneando pizzas.
void hiloCocinero(Contexto& ctx, int idCocinero);

// Hilo que simula a un repartidor/mesero entregando pizzas.
void hiloRepartidor(Contexto& ctx, int idRepartidor);
