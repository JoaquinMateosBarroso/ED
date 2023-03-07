/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <sstream>
#include <stdexcept>
#include <cassert>

#include "slist.hpp"

template <class T>
SNode<T>::SNode (T const& it)
{
    //
    _item = it;
    _next = nullptr;
    //
    assert(!has_next());
}

template <class T>
SNode<T>::SNode (T const& it, SNode<T>::Ref& next)
{
    //
    _item = it;
    _next = next;
    //
}

template <class T>
SNode<T>::~SNode()
{
    //TODO
    //hint: if std::shared_ptr is used for the references, nothing todo.

    //
}

template <class T>
typename SNode<T>::Ref SNode<T>::create(T const& it, SNode<T>::Ref next)
{
    return std::make_shared<SNode<T>> (it, next);
}

template <class T>
T SNode<T>::item() const
{
    T it;
    //
    it = _item;
    //
    return it;
}

template <class T>
bool SNode<T>::has_next() const
{
    bool has = false;
    //
    has = (_next==nullptr) ? false : true;
    //
    return has;
}

template <class T>
typename SNode<T>::Ref SNode<T>::next() const
{
    SNode<T>::Ref n;
    //
    n = _next;
    //
    return n;
}

template <class T>
void SNode<T>::set_item(const T& new_it)
{
    //
    _item = new_it;
    //
    assert(item()==new_it);
}

template <class T>
void SNode<T>::set_next(SNode<T>::Ref n)
{
    //
    _next = n;
    //
    assert(n == next());
}

template<class T>
SList<T>::SList ()
{
    //
    _head = nullptr;
    _current = nullptr;
    _size = 0;

    //
    assert(is_empty());
}

template<class T>
SList<T>::~SList()
{
    //TODO

    //

}

template<class T>
typename SNode<T>::Ref SList<T>::head() const
{
    typename SNode<T>::Ref h;
    //
    h = _head;
    //
    return h;
}

template<class T>
typename SList<T>::Ref SList<T>::create()
{
    return std::make_shared<SList<T>> ();
}

template<class T>
typename SList<T>::Ref SList<T>::create(std::istream& in) noexcept(false)
{
    auto list = SList<T>::create();
    std::string token;
    in >> token;

    //
    //Hint: use std::istringstream to convert from "string" to template
    // parameter T type.
    // Throw std::runtime_error("Wrong input format.") exception when an input
    // format error was found.

    T aux_t;
    if (token == "[]")
    {
        return list;
    }
    if (token != "[")
    {
        throw std::runtime_error("Wrong input format.");
    }
    in >> token;
    while (token != "]")
    {
        if (token == "]")
        {
            if (!list->is_empty())
            {
                list->goto_first();
            }
            return list;
        }
        std::istringstream aux(token);
        aux >> aux_t;
        if (in.fail() or aux.fail())
        {
            throw std::runtime_error("Wrong input format.");
        }
        list->insert(aux_t);
        while (list->has_next())
        {
            list->goto_next();
        }
        in >> token;
    }

    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //
    ret_val = (_head == nullptr) and (_size == 0);
    //
    return ret_val;
}

template<class T>
size_t SList<T>::size () const
{
    size_t ret_val = 0;
    //
    ret_val = _size;
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //
    return _head -> item();
    //
    return f;
}

template<class T>
T SList<T>::current() const
{    
    assert(! is_empty());
    T c;
    //
    c = _current -> item();
    //
    return c;
}

template<class T>
bool SList<T>::has_next() const
{
    assert(!is_empty());
    bool ret_val = false;
    //
    ret_val = (_current->next() != nullptr);
    //
    return ret_val;
}

template<class T>
T SList<T>::next() const
{
    assert(has_next());
    T ret_val = false;
    //
    ret_val = _current -> next() -> item();
    //
    return ret_val;
}


template<class T>
bool SList<T>::has(T const& it) const
{
    bool found = false;
    //
    //Hint: you can reuse SList::find() but you must remember to restore 
    // the old the cursor position. In this way we assure not modify the state of the list.
    //Hint: use const_cast<> to remove constness of this.
    auto aux = _head;
    while (aux->item() != it and aux->next() != nullptr)
    {
        aux = aux->next();
    }
    found = (aux->item() == it);
    //
    return found;
}

template<class T>
void SList<T>::fold(std::ostream& out) const
{
    //
    out << "[";

    if (is_empty())
    {
        out << "]";
        return ;
    }

    typename SNode<T>::Ref aux = _head;

    while (aux -> has_next())
    {
        out << " " << aux -> item();
        aux = aux -> next();
    }
    out << " " << aux -> item() << " ]";

    //
}

template<class T>
void SList<T>::set_current(T const& new_v)
{
    assert(!is_empty());
    //
    _current -> set_item(new_v);
    //
    assert(current()==new_v);
}


template<class T>
void SList<T>::push_front(T const& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //
    //Remeber to update current if current is in the head.



    auto aux_ = SNode<T>::create(new_it, _current);
    aux_ -> set_next(_head);

    if (_current == _head)
    {
        _current = aux_;
    }
    _head = aux_;


    _size += 1;
    //
    assert(front()==new_it);
    assert(size() == (old_size+1));
}

template<class T>
void SList<T>::insert(T const& new_it)
{
#ifndef NDEBUG
    bool old_is_empty = is_empty();
    size_t old_size = size();
    T old_item;
    if (!old_is_empty)
        old_item = current();
#endif
    //

    if (is_empty())
    {
        push_front(new_it);
    }

    else{
        auto aux = SNode<T>::create(new_it, _current);

        aux -> set_item(new_it);
        aux -> set_next(_current -> next());
        _current -> set_next(aux);
        _size += 1;
    }


    //
    assert(!old_is_empty || (front()==new_it && current()==new_it));
    assert(old_is_empty || (old_item == current() && has_next() && next()==new_it));
    assert(size()==(old_size+1));
}

template<class T>
void SList<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_head_next = head()->next();
#endif
    //
    if (_size == 1)
    {
        _current = nullptr;
        _head = nullptr;
    }
    else
    {
        _head = _head -> next();
        if (_current == _head)
        {
                _current =_current -> next();
        }
    }
    _size -= 1;

    //
    assert(is_empty() || head() == old_head_next);
    assert(size() == (old_size-1));
}


template<class T>
void SList<T>::remove()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    bool old_has_next = has_next();
    T old_next;
    if (has_next())
        old_next=next();
#endif
    //
    //Case 1: current is the head.

    //Case 2: remove in a middle position.

    //Case 3: remove the last element.
    //Remember to locate previous of prev_.

    if (_current == _head)
    {
        _head = _head->next();
        _current = _head;
    }
    else if (!has_next())
    {
        typename SNode<T>::Ref prev_ = head();
        while(prev_ -> next() != _current)
        {
            prev_ = prev_->next();
        }
        _current = prev_;
        _current -> set_next(nullptr);
    }
    else
    {
        typename SNode<T>::Ref prev_ = _head;
        while (prev_->next() != _current)
        {
            prev_ = prev_->next();
        }
        prev_->set_next(_current->next());
        _current = prev_->next();
    }
    _size -= 1;


    //
    assert(!old_has_next || current()==old_next);
    assert(size() == (old_size-1));
}

template<class T>
void SList<T>::goto_next()
{
    assert(has_next());
#ifndef NDEBUG
    auto old_next = next();
#endif
    //
    _current = _current -> next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //
    _current = _head;

    //
    assert(current()==front());
}

template<class T>
bool SList<T>::find(T const& it)
{
    assert(!is_empty());
    bool found = false;
    //

    _current = _head;
    if (_current -> item() == it)
    {
        found = true;
    }
    else if (_head->next()->has_next())
    {
        found = find_next(it);
    }
    else
    {
        found = (_current -> item() == it);
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

template<class T>
bool SList<T>::find_next(T const& it)
{
    assert(has_next());
    bool found = false;
    //

    _current = _current -> next();

    if (_current->item() == it)
    {
        found = true;
    }
    else{
        while (_current -> has_next() and !found)
        {
            _current = _current -> next();
            found = (_current -> item() == it);
        }
    }


    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

