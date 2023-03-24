/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //
    // Hint: when you call a template into other template maybe you need
    // to specialize the call.
    height = -1;
    if (!t->is_empty())
    {
        // Now minimum height is gonna be 0
        height = 0; 
        int left_height = compute_height<T>(t->left()); 
        int right_height = compute_height<T>(t->right()); 
        // Add maximum
        height += left_height > right_height ? left_height : right_height;
        height += 1;
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if (!t->is_empty())
    {
        ret_val = 1;
        ret_val += compute_size<T>(t->left());
        ret_val += compute_size<T>(t->right());
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //
    // Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if (retVal and !tree->is_empty())
    {
        retVal = retVal and p(tree);
        retVal = retVal and prefix_process<T, Processor>(tree->left(), p);
        retVal = retVal and prefix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //
    // Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if (retVal and !tree->is_empty())
    {
        retVal = retVal and infix_process<T, Processor>(tree->left(), p);
        retVal = retVal and p(tree);
        retVal = retVal and infix_process<T, Processor>(tree->right(), p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if (retVal and !tree->is_empty())
    {
        retVal = retVal and postfix_process<T, Processor>(tree->left(), p);
        retVal = retVal and postfix_process<T, Processor>(tree->right(), p);
        retVal = retVal and p(tree);
    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.
    std::queue<typename BTree<T>::Ref> frontera;
    if (!tree->is_empty())
    {
        frontera.push(tree);
        while (go_on and !frontera.empty())
        {
            auto aux = frontera.front();
            frontera.pop();
            go_on = p(aux);
            if (!(aux->left())->is_empty())
            {
                frontera.push(aux->left());
            }if (!(aux->right())->is_empty())
            {
                frontera.push(aux->right());
            } 
        }
    }
    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto aux_print = [&out](typename BTree<T>::Ref aux_tree)
    {
        out << aux_tree->item() << " ";
        return true;
    };
    // A veces no hay que completar la plantilla
    prefix_process<T>(tree, aux_print);
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto aux_print = [&out](typename BTree<T>::Ref aux_tree)
    {
        out << aux_tree->item() << " ";
        return true;
    };
    // A veces no hay que completar la plantilla
    infix_process<T>(tree, aux_print);
    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto aux_print = [&out](typename BTree<T>::Ref aux_tree)
    {
        out << aux_tree->item() << " ";
        return true;
    };
    // A veces no hay que completar la plantilla
    postfix_process<T>(tree, aux_print);
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto aux_print = [&out](typename BTree<T>::Ref aux_tree)
    {
        out << aux_tree->item() << " ";
        return true;
    };
    breadth_first_process<T>(tree, aux_print);
    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto compare = [&it, &count](typename BTree<T>::Ref aux_tree)
    {
        count += 1;
        return aux_tree->item() != it;
    };
    found = !prefix_process<T>(tree, compare);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto noteq = [&it, &count](typename BTree<T>::Ref tree)
    {
        count ++;
        return tree->item() != it;
    };
    found = !infix_process<T>(tree, noteq);


    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto noteq = [&it, &count](typename BTree<T>::Ref tree)
    {
        count ++;
        return tree->item() != it;
    };
    found = !postfix_process<T>(tree, noteq);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto noteq = [&it, &count](typename BTree<T>::Ref tree)
    {
        count++;
        return tree->item() != it;
    };

    found = !breadth_first_process<T>(tree, noteq);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    T* anterior = nullptr;
    auto ordenado = [&anterior](typename BTree<T>::Ref const& tree)
    {

        //Hace falta idea feliz; mejor con muchos ifs
        if (tree->is_empty())
        {
            return true;
        }
        if (anterior == nullptr)
        {
            anterior = new T(tree->item());
            return true;
        }
        T* aux = anterior;
        anterior = new T(tree->item());
        return tree->item() > *aux;
    };
    ret_val = infix_process<T>(tree, ordenado);
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO
    auto noigual = [&v](typename BTree<T>::Ref const& tree)
    {
        return tree->item() != v;
    };
    ret_val = !postfix_process<T>(tree, noigual);

    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO
    if (tree->is_empty())
    {
        tree->create_root(v);
    }
    else{
        if (tree->item() != v)
        {
            if (v < tree->item())
            {
                if (tree->left()->is_empty())
                {
                    tree->set_left(BTree<T>::create(v));
                }
                else
                {
                    insert_in_order(tree->left(), v);
                }
            }
            else
            {            
                if (tree->right()->is_empty())
                {
                    tree->set_right(BTree<T>::create(v));
                }
                else
                {
                    insert_in_order(tree->right(), v);
                }
            }
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
