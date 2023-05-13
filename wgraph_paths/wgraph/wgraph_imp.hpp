/**
 * @file graph_utils_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <string>

#include "wgraph.hpp"

/** GraphNode implementation **/

template<class T>
WNode<T>::WNode(size_t label, T const& v)
{
    //
    label_ = label;
    item_ = v;
    is_visited_ = false;
    //
    assert(item()==v);
    assert(!is_visited());
}

template<class T>
T WNode<T>::item() const
{
    T ret_v;
    //
    ret_v = item_;
    //
    return ret_v;
}

template<class T>
size_t  WNode<T>::label() const
{
    size_t ret_v = 0;
    //
    ret_v = label_;
    //
    return ret_v;
}

template<class T>
bool  WNode<T>::is_visited() const
{
    bool ret_v = false;
    //
    ret_v = is_visited_;
    //
    return ret_v;
}

template<class T>
void WNode<T>::set_item(T const& v)
{
    //
    item_ = v;
    //
    assert(item()==v);
}


template<class T>
void WNode<T>::set_visited(bool new_st)
{
    //
    is_visited_ = new_st;
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

/** GraphEdge implementation **/

template<class T, class E>
WEdge<T,E>::WEdge(NodeRef u, NodeRef v, FMatrix::Ref wmat)
{
    //
    node1_ = u;
    node2_ = v;
    weight_ = wmat->get(u->label(), v->label());
    //
}

template<class T, class E>
E WEdge<T,E>::weight() const
{
    E ret_val=std::numeric_limits<float>::infinity();
    //
    ret_val = weight_;
    //
    return ret_val;
}

template<class T, class E>
bool WEdge<T,E>::has(NodeRef const& n) const
{
    bool ret_val = false;
    //
    ret_val = ((n->label()==node1_->label()) or (n->label()==node2_->label()));
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::other(NodeRef const& n) const
{
    assert(has(n));
    NodeRef ret_val;
    //
    ret_val = (n->label()==node1_->label() ? node2_: node1_);

    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::first() const
{
    NodeRef ret_val;
    //
    ret_val = node1_;
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::second() const
{
    NodeRef ret_val;
    //
    ret_val = node2_;
    //
    return ret_val;
}

template<class T, class E>
void WEdge<T,E>::set_weight(E const& v)
{
    //
    weight_ = v;
    //
    assert(weight()==v);
}


/** WGraph implementation **/
template<class T>
WGraph<T>::WGraph (size_t capacity, float default_weight)
{
    assert(capacity>0);

    //TODO
    //Remember: this a weighted graph, so all the nodes are connected with
    //          infinite weight by default.
    matrix_ = FMatrix::create(capacity, capacity, default_weight);
    nodes_ = std::vector<NodeRef>();

    current_node_ = 0;
    current_edge_ = 0;
    capacity_ = capacity;
    //

    assert(is_empty());
    assert(!has_current_node());
    assert(!has_current_edge());
}

template<class T>
bool WGraph<T>::is_empty() const
{
    bool ret_v = true;
    //
    ret_v = (size()==0);
    //
    assert(!ret_v || size()==0);
    return ret_v;
}

template<class T>
bool WGraph<T>::is_full() const
{
    bool ret_v = true;
    //
    ret_v = (size() == capacity_);
    //
    assert(!ret_v || size()==capacity());
    return ret_v;
}

template<class T>
size_t WGraph<T>::size() const
{
    size_t ret_v = 0;
    //
    ret_v = nodes_.size();
    //
    return ret_v;
}

template<class T>
size_t WGraph<T>::capacity() const
{
    size_t ret_v = 0;
    //
    ret_v = capacity_;
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has(NodeRef u) const
{
    assert (u != nullptr);
    bool ret_v = true;
    //
    ret_v = (u->label() < capacity() and node(u->label(u)) == u);
    //
    assert(!ret_v || (u->label()<capacity() && node(u->label())==u));
    return ret_v;
}

template<class T>
bool WGraph<T>::are_adjacent (NodeRef u, NodeRef v) const
{
    assert( has(u) && has(v) );
    bool ret_v = false;
    //
    //Remember: this a Weighted graph so a node u is adjacent to v if the
    //          edge's weight is less than infinite.
    // Hint: use std::numeric_limits<float> facet to get infinite as float value.
    ret_v = (matrix_->get(u->label(), v->label()) < std::numeric_limits<float>::infinity());
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has_current_node () const
{
    bool ret_v = false;
    //
    //Hint: use attribute _size to mark "end".
    ret_v = (current_node_ < size());
    //
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::current_node () const
{
    assert(has_current_node());
    NodeRef ret_v;
    //
    ret_v = node(current_node_);
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has_current_edge () const
{
    bool ret_v = false;    
    //
    //Remember: first it must exist a current node.
    //Hint: use value size() to mark "end".
    ret_v = (has_current_node() and current_edge_ < size() and
             matrix_->get(current_node_, current_edge_) < std::numeric_limits<float>::infinity());
    //
    assert(!ret_v || has_current_node());
    return ret_v;
}

template<class T>
float WGraph<T>::current_weight () const
{
    assert(has_current_edge());
    float ret_v = 0.0;
    //
    ret_v = matrix_->get(current_node_, current_edge_);
    //
    assert(ret_v<std::numeric_limits<float>::infinity());
    return ret_v;
}

template<class T>
FMatrix::Ref WGraph<T>::weight_matrix() const
{
    FMatrix::Ref mat;
    //
    mat = matrix_;
    //
    return mat;
}

template<class T>
float WGraph<T>::weight(size_t u_label, size_t v_label) const
{
    assert(u_label<size());
    assert(v_label<size());
    float ret_v = 0.0;
    //
    ret_v = matrix_->get(u_label, v_label);
    //
    assert(ret_v == weight(node(u_label), node(v_label)));
    return ret_v;
}

template<class T>
float WGraph<T>::weight (NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    float ret_v = 0.0;
    //
    ret_v = matrix_->get(u->label(), v->label());
    //
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v=nullptr;
    //
    ret_v = WEdge<T, float>::create(u, v, matrix_);
    //
    assert(ret_v->first()==u);
    assert(ret_v->second()==v);
    assert(ret_v->weight()==weight(u, v));
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(size_t u_label, size_t v_label) const
{
    assert(u_label<size());
    assert(v_label<size());
    EdgeRef ret_v=nullptr;
    //
    //Hint: use the static method WEdge::create().
    ret_v = WEdge<T, float>::create(node(u_label), node(v_label), matrix_);
    //
    assert(ret_v->first()->label()==u_label);
    assert(ret_v->second()->label()==v_label);
    assert(ret_v->weight()==weight(u_label, v_label));
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::current_edge() const
{
    assert(has_current_edge());
    EdgeRef ret_v = nullptr;
    //
    //Hint: use the static method WEdge::create().
    ret_v = WEdge<T, float>::create(current_node(), node(current_edge_), matrix_);
    //
    assert(ret_v->first()==current_node() && ret_v->weight()<std::numeric_limits<float>::infinity());
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::node(size_t label) const
{
    assert(label<size());
    NodeRef n;
    //
    n = nodes_[label];
    //
    return n;
}

template<class T>
void WGraph<T>::set_visited(bool state)
{
    //
    // Remember: we only have visited flag in nodes, no one in edges.
    for (size_t i = 0; i < size(); i++)
    {
        nodes_[i]->set_visited(state);
    }
    //
}

template<class T>
void WGraph<T>::goto_first_node()
{
    assert(!is_empty());
    //
    //Remember: the edge's cursor must be initialized too.
    current_node_ = 0;
    goto_first_edge();
    //
    assert(!has_current_edge()||current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_first_edge()
{
    assert(has_current_node());
    //
    // Remember: we consider here edges with weight < infinite.
    current_edge_ = -1;
    goto_next_edge();

    //
    assert(!has_current_edge()||current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_next_node()
{
    assert(has_current_node());
    //
    // Remember: you must update the edge cursor too.
    current_node_++;
    goto_first_edge();
    //
    assert(has_current_node() || !has_current_edge());
    assert(!has_current_edge() || (current_edge()->first() == current_node()));
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_next_edge()
{
    assert(has_current_edge());
    //
    // Remember: we consider here edges with weight < infinite.
    do
    {
        current_edge_++;
    } while(!has_current_edge() and current_edge_ < size());
    //
    assert(!has_current_edge() || current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_node(NodeRef u)
{
    assert(has(u));
    //
    // Remember: update edge cursor too.
    current_node_ = u->label();
    goto_first_edge();
    //
    assert(!has_current_edge() || current_edge()->first()==u);
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_edge(NodeRef u, NodeRef v)
{
    assert(has(u));
    assert(has(v));
    assert(weight(u, v) < std::numeric_limits<float>::infinity());
    //
    //Remember: node and edge cursors must be initialized too.
    goto_node(u);
    current_edge_ = v->label();

    //
    assert(current_node()==u);
    assert(current_edge()->first()==u);
    assert(current_edge()->second()==v);
    assert(current_weight()==weight(u,v));
}

template<class T>
void WGraph<T>::goto_edge(EdgeRef e)
{
    assert(has(e->first()));
    assert(has(e->second()));
    assert(e->weight() < std::numeric_limits<float>::infinity());
    //
    //Remember: node and edge cursors must be initialized too.
    goto_edge(e->first_node(), e->second_node());

    //
    assert(current_node()==e->first());
    assert(current_edge()->second()==e->second());
    assert(current_weight()==e->weight());
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::find_node(typename T::key_t const& key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    //TODO
    // Remember: update node and edge cursors.
    // Remember: The item.key() is used to look for.
    goto_first_node();
    find_next_node(key);
    ret_v = current_node();

    //
    assert((ret_v==nullptr) || (has_current_node() && current_node()==ret_v));
    assert(!has_current_node() || current_node()->item()==key);
    assert(!has_current_edge() || current_edge()->first()==current_node());
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::find_next_node(typename T::key_t const& key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    //
    // Remember: update node and edge cursors.
    // Remember: The item.key() is used to look for.
    for (size_t i = current_node_; i < size(); i++)
    {
        if (key == nodes_[i]->item().key())
        {
            ret_v = node(i);
            current_node_ = i;
            break;
        }
    }
    goto_first_edge();
    //
    assert((ret_v==nullptr) || (has_current_node() && current_node()==ret_v));
    assert(!has_current_node() || current_node()->item()==key);
    assert(!has_current_edge() || current_edge()->first()==current_node());
    return ret_v;
}

template<class T>
void WGraph<T>::set_current_weight(float new_w)
{
    assert(has_current_edge());
    //
    // Remember: set infinite as new weight invalidates edge_cursor.
    matrix_->set(current_node_, current_edge_, new_w);
    current_edge_--;
    goto_next_edge();
    //
    assert(new_w < std::numeric_limits<float>::infinity() || !has_current_edge());
}

template<class T>
void WGraph<T>::set_weight(size_t u_label, size_t v_label, float new_w)
{
    assert(u_label<size());
    assert(v_label<size());
    //
    // Remember: set infinite as new weight could invalidate the edge cursor if it is currently points to this edge.
    matrix_->set(u_label, v_label, new_w);
    //
    assert(new_w == weight(u_label, v_label));
    assert(!has_current_edge() || current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::set_weight(NodeRef u, NodeRef v, float new_w)
{
    assert(has(u));
    assert(has(v));
    //
    // Remember: set infinite as new weight could invalidate the edge cursor if it is currently points to this edge.
    matrix_->set(u->label(), v->label(), new_w);
    //
    assert(weight(u, v)==new_w);
    assert(!has_current_edge() || current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::add_node(T const& v)
{
    assert(! is_full());
    //
    // Remember: update node and edge cursors.
    auto node = WNode<T>::create(nodes_.size(), v);
    nodes_.push_back(node);
    goto_node(node);
    goto_first_edge();
    //
    assert(has_current_node());
    assert(!has_current_edge());
}

template <class T>
std::ostream&
WGraph<T>::fold(std::ostream& out) const
{
    //
    //Hint: the Matrix template has a fold method.
    out << "[ " << capacity() << " " << size() << " ";
    for (size_t i = 0; i < size(); i++)
    {
        out << nodes_[i]->item() << " ";

    }

    matrix_->fold(out);
    out << " ]";
    //
    return out;
}

template <class T>
WGraph<T>::WGraph (std::istream& input) noexcept(false)
{
    //TODO
    //Remember: capacity is the max number of nodes that the graph could have.
    //          size is the current number of nodes (size <= capacity).
    //Hint: The Matrix template has a unfold method.
    std::string text;
    size_t quantity;
    T aux_T;
    input >> text;
    if (text != "[")
    {
        throw std::runtime_error("Wrong input format.");
    }
    input >> capacity_;
    input >> quantity;
    for (size_t i = 0; i < quantity; i++)
    {
        input >> aux_T;
        nodes_.push_back(WNode<T>::create(i, aux_T));
    }
    matrix_ = FMatrix::create(input);

    input >> text;

    //
    assert(!has_current_node());
    assert(!has_current_edge());
}

template <class T>
typename WGraph<T>::Ref WGraph<T>::create (std::istream & input)
{
    return std::make_shared<WGraph<T>>(input);

}

template<class T>
typename WGraph<T>::Ref create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    typename WGraph<T>::Ref graph = nullptr; //The returned graph.

    //TODO    
    //Remember: Throw std::runtime_error("Wrong graph") when detecting a wrong
    //          input format.
    //Remember: key_t type is used to give the edge's ends.
    bool is_directed;
    size_t num_edges;

    std::string aux_text;
    size_t aux_size;
    T aux_T;
    float aux_float;
    //TODO
    //First: Determine if it is directed or undirected.
    in >> aux_text;
    if (aux_text == "DIRECTED")
    {
        is_directed = true;
    }
    else if (aux_text == "UNDIRECTED")
    {
        is_directed = false;
    }
    else
    {
        throw std::runtime_error("Wrong graph");
    }

    //

    //TODO
    //Second: get the number of nodes and create a wgraph with this capacity.
    in >> aux_size;
    graph = WGraph<T>::create(aux_size);
    //

    //TODO
    //Third: load the N T data items and adding the nodes.

    in.ignore();
    std::istringstream aux;
    for (size_t i = 0; i < aux_size; i++)
    {
        std::getline(in, aux_text);
        aux = std::istringstream(aux_text);
        aux >> aux_T;
        graph->add_node(aux_T);

    }
    //

    //TODO
    //Fourth: load the number of edges.
    in >> num_edges;
    //

    //TODO
    //Fifth: load the N edges.
    //Remember: Use T::key_t type to load the edge's ends.
    //Remember: if the input graph is UNDIRECTED we simulated this with a WGraph
    //          duplicating each input edge (u,v) making too the (v,u) edge with same weight
    //          with the same weight.
    T aux1;
    size_t aux_row;
    T aux2;
    size_t aux_column;
    typename T::key_t key1;
    typename T::key_t key2;

    for (size_t i = 0; i < num_edges; i++)
    {
         in >> key1;
         in >> key2;

        aux_row = graph->find_node(key1)->label();
        aux_column = graph->find_node(key2)->label();
        // T::key_t borrarcout = aux1.key();

        in >> aux_float;
        graph->set_weight(aux_row, aux_column, aux_float);
        if (!is_directed)
        {
            graph->set_weight(aux_column, aux_row, aux_float);
        }
    }

    //

    return graph;
}

