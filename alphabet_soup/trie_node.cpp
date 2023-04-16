/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>

#include "trie_node.hpp"

TrieNode::TrieNode (bool is_key_state)
{
    //
    is_key_ = is_key_state;
    map_ = std::map<char, TrieNode::Ref>();
    current_ = map_.end();
    //
    assert(is_key()==is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return std::make_shared<TrieNode>(is_key_state);
}

TrieNode::~TrieNode()
{}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    //
    ret_val = is_key_;
    //
    return ret_val;
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //
    ret_v = map_.count(k);
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref node = nullptr;
    //
    node = map_.at(k);
    //
    return node;
}

bool
TrieNode::current_exists() const
{
    bool ret_val = true;
    //
    ret_val = (current_ != map_.end());

    //
    return ret_val;
}

TrieNode::Ref
TrieNode::current_node() const
{
    assert(current_exists());
    TrieNode::Ref node = nullptr;
    //
    node = current_->second;

    //
    return node;
}

char
TrieNode::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //
    symbol = current_->first;
    //
    return symbol;
}

void
TrieNode::set_is_key_state(bool new_state)
{
    //
    is_key_ = new_state;
    //
    assert(is_key()==new_state);
}

bool
TrieNode::find_child(char s)
{
    bool found = false;
    //
    current_ = map_.find(s);

    found = current_exists();

    //
    assert(found || !current_exists());
    assert(!found || current_symbol()==s);
    return found;
}

void
TrieNode::goto_first_child()
{
    //
    current_ = map_.begin();
    //
}

void
TrieNode::goto_next_child()
{
    assert(current_exists());
    //
    current_++;
    //
}

void
TrieNode::set_child(char k, Ref node)
{
    assert(node != nullptr);
    //
    map_.insert(std::pair<char, TrieNode::Ref>(k, node));
    find_child(k);
    //
    assert(current_symbol()==k);
    assert(current_node()==node);
}

std::ostream&
TrieNode::fold(std::ostream& out) const
{
    //
    //Hint: review c++ input/output manipulators at
    //      https://en.cppreference.com/w/cpp/io/manip


    out << "[ ";
    out << (is_key_? "T": "F");

    auto aux = map_.begin();
    while (aux != map_.end())
    {
        out << " "<< std::hex << (uint16_t)aux->first << " ";
        aux->second->fold(out);
        aux++;
    }
    out << " ]";
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //
    std::string aux;
    in >> aux;

    if (aux != "[")
    {
        throw std::runtime_error("wrong input format.");
    }
    in >> aux;
    if (aux != "]")
    {
        if (aux != "T" and aux != "F")
        {
            throw std::runtime_error("wrong input format.");
        }

        node = create(aux == "T");

        in >> aux;
        while (aux != "]")
        {

            auto aux2 = stoi(aux, nullptr, 16);
            char valor = (char)aux2;
            node->set_child(valor, create(in));
            
            in >> aux;
            
        }
    }
    else
    {
        throw std::runtime_error("wrong input format.");
    }

    //
    return node;
}
