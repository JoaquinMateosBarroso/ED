/**
 * @file trie.cpp
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
#include "trie.hpp"

Trie::Trie()
{
    //
    prefix_ = "";
    root_ = nullptr;
    //
    assert(is_empty());
}

Trie::Ref Trie::create()
{    
    return std::make_shared<Trie>();
}

Trie::Trie(TrieNode::Ref root_node, std::string const& pref)
{
    //
    root_ = root_node;
    prefix_ = pref;
    //
    assert(prefix() == pref);
}

Trie::Ref Trie::create(TrieNode::Ref root_node, std::string const& prefix)
{
    //We cannot use std::make_shared here
    //because the constructor is protected.
    typename Trie::Ref trie ( new Trie(root_node, prefix));
    return trie;
}

Trie::Ref Trie::create(std::istream& in) noexcept(false)
{
    Trie::Ref trie = nullptr;
    //TODO


    //
    return trie;
}

bool
Trie::is_empty() const
{
    bool ret_v=true;
    //
    ret_v = (root_ == nullptr);
    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    //
    ret_val = prefix_;
    //
    return ret_val;
}

bool
Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    //
    ret_val = root_->is_key();
    //
    return ret_val;
}


TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node = nullptr;
    //
    node = root_;
    //
    return node;
}

bool
Trie::has(std::string const& k) const
{
    assert(!is_empty());
    bool found = false;
    //
    //Hint: use find_node() to do this.
    //Remember: The Trie can have a prefix==k but does not store the key k.   

    auto aux = find_node(k);
    
    found = ((aux != nullptr) and (aux->is_key()));
    
    //
    return found;
}

static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> & keys)
{
    //TODO
    //Remember: node->is_key() means the prefix is a key too.
    
    //
}


void
Trie::retrieve(std::vector<std::string>& keys) const
{
    assert(!is_empty());
    //TODO
    //Remember add the subtrie's prefix to the retrieve keys.

    //
}

Trie::Ref
Trie::child(std::string const& pref) const
{
    assert(!is_empty());
    Trie::Ref ret_v = Trie::create();
    //
    //Hint: use find_node() to do this.
    auto aux = find_node(pref);
    ret_v = Trie::create(aux, (aux? pref: ""));
    //
    assert(ret_v != nullptr);
    return ret_v;
}

bool
Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO
    ret_val = root_->current_exists();
    //
    return ret_val;
}

Trie::Ref
Trie::current() const
{
    assert(current_exists());
    Trie::Ref trie = nullptr;
    //TODO
    trie = Trie::create(root_->current_node(), prefix_+current_symbol());
    //
    return trie;
}

char
Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO
    symbol = root_->current_symbol();
    //
    return symbol;
}

void
Trie::insert(std::string const& k)
{
    assert(k != "");
    //
    if (is_empty())
    {
        root_ = TrieNode::create(false);
        prefix_ = "";
    }
    auto current_ptr = root_;
    for (unsigned i = 0; i < k.size(); i++)
    {
        if (!(current_ptr->has(k[i])))
        {
            current_ptr->set_child(k[i], TrieNode::create(false));
        }
        current_ptr = current_ptr->child(k[i]);
    }
    current_ptr->set_is_key_state(true);

    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const& pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    //
    //Remember: the prefix "" must return the trie's root node
    if (pref == "")
    {
        node = root_;
    }
    else
    {
        unsigned i = 0;
        auto current = root_;
        while((i < pref.size()) and (current->has(pref[i])))
        {
            current = current->child(pref[i]);
            i++;
        }
        node = ((i==pref.size())? current: nullptr);
    }
    //
    return node;
}

std::ostream&
Trie::fold(std::ostream& out) const
{
    //TODO
    if (is_empty())
    {
        out << "[]";
    }
    else
    {
        out << "[ \"" << prefix_ << "\" ";
        root_->fold(out);
        out << " ]";
    }


    //
    return out;
}

bool
Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    //TODO
    found = root_->find_child(symbol);
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol()==symbol);
    return found;
}

void
Trie::goto_first_symbol()
{
    assert(!is_empty());
    //TODO
    root_->goto_first_child();
    // std::cout << "COSAS\n";
    // root_->fold(std::cout);
    //
    assert(!current_exists() ||
           current()->prefix()==prefix()+current_symbol());
}

void
Trie::goto_next_symbol()
{
    assert(current_exists());
    //TODO
    root_->goto_next_child();
    //
}
