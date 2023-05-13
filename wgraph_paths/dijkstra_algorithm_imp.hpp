/**
 * @file dijkstra_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <tuple>
#include <queue>
#include <limits>
#include <functional>

#include "dijkstra_algorithm.hpp"


template<class T>
void dijkstra_algorithm(typename WGraph<T>::Ref g,
                        std::vector<size_t>& predecessors,
                        std::vector<float>& distances)
{
    assert(g->has_current_node());

    //TODO
    //Hint: initialize distances with inf.
    //Hint: Initialize the vector of predecessors so that each vertex is a
    //      predecessor of itself.
    //Hint: use the the template tuple para represent edges. Set the fields so
    //      the tuples will be sorted properly.
    //      @see: https://en.cppreference.com/w/cpp/utility/tuple
    // Hint: you can use the keyword "using" to create an alias "Tuple"
    for (size_t i = 0; i < g->size(); i++)
    {
        distances.push_back(std::numeric_limits<float>::infinity());
        predecessors.push_back(i);
    }
    std::list<std::tuple<size_t, size_t, float>> pendientes;

    typename WNode<T>::Ref nodo_actual = g->current_node();

    pendientes.push_back(std::tuple<size_t, size_t, float>(g->current_node()->label(), g->current_node()->label(), 0.0));

    while (!pendientes.empty())
    {
        auto t = pendientes.front();
        pendientes.pop_front();
        auto u = std::get<0>(t);
        if (!g->node(u)->is_visited())
        {
            predecessors[u] = std::get<1>(t);
            distances[u] = std::get<2>(t);
            g->node(u)->set_visited(true);
            g->goto_node(g->node(u));
            while (g->has_current_edge())
            {
                auto v = g->current_edge()->other(g->node(u))->label();
                if (!g->node(v)->is_visited())
                {
                    auto i = pendientes.end();
                    for (; i != pendientes.begin() and std::get<2>(*i) > (distances[u] + g->current_weight()); i--){}
                    
                    pendientes.insert(i, std::tuple<size_t, size_t, float> (v, u, distances[u] + g->current_weight()));

                    // pendientes.push_back( std::tuple<size_t, size_t, float> (v, u, distances[u] + g->current_weight()));
                }
                g->goto_next_edge();
            }
        }

    }
    

    //
}


inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t>const& predecessors)
{
    assert(src<predecessors.size());
    assert(dst<predecessors.size());
    assert(predecessors[src]==src);
    std::list<size_t> path;
    //TODO

    //
    return path;
}

