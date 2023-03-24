/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include "btree.hpp"

template<class T>
BTNode<T>::BTNode (T const& it, BTNode<T>::Ref l,
                   BTNode<T>::Ref r)
{
  //
  item_ = it;
  left_ = l;
  right_ = r;
  //
  assert(item()==it);
  assert(left()==l);
  assert(right()==r);
}

template<class T>
typename BTNode<T>::Ref BTNode<T>::create(T const& it,
                                          BTNode<T>::Ref left,
                                          BTNode<T>::Ref right)
{
    return std::make_shared<BTNode<T>> (it, left, right);
}

template<class T>
T BTNode<T>::item() const
{

    T ret_v;
    //
    ret_v = item_;
    //
    return ret_v;
}



template<class T>
typename BTNode<T>::Ref BTNode<T>::left() const
{

    typename BTNode<T>::Ref child;
    //
    child = left_;
    //
    return child;
}


template<class T>
typename BTNode<T>::Ref BTNode<T>::right() const
{

    typename BTNode<T>::Ref child;
    //
    child = right_;
    //
    return child;
}

template<class T>
void BTNode<T>::set_item(const T& new_it)
{
    //
    item_ = new_it;
    //
    assert(item()==new_it);
}

template<class T>
void BTNode<T>::set_left(BTNode<T>::Ref new_child)
{
    //
    left_ = new_child;
    //
    assert(left()==new_child);
}

template<class T>
void BTNode<T>::set_right(BTNode<T>::Ref new_child)
{
    //
    right_ = new_child;
    //
    assert(right()==new_child);
}

/**
 * ADT BTree.
 * Models a BTree of T.
 */
template<class T>
BTree<T>::BTree ()
    {
        //
        root_ = nullptr;
        //
        assert(is_empty());
    }

    template<class T>
    BTree<T>::BTree (const T& it)
    {
        //
        root_ = BTNode<T>::create(it);
        //
        assert(!is_empty());
        assert(item()==it);
        assert(left()->is_empty());
        assert(right()->is_empty());
    }

template<class T>
typename BTree<T>::Ref BTree<T>::create()
  {
      return std::make_shared<BTree<T>> ();
  }

template<class T>
  typename BTree<T>::Ref BTree<T>::create(T const& item)
  {
      return std::make_shared<BTree<T>>(item);
  }

template<class T>
  typename BTree<T>::Ref BTree<T>::create (std::istream& in) noexcept(false)
  {
      auto tree = BTree<T>::create();
      std::string token;
      //
      //Remember: throw std:runtime_error exception with text
      //"Wrong input format." when an input format error is found.
      T aux;
      
      in >> token;
      if (token != "[]" and token != "[")
      {
        throw std::runtime_error("Wrong input format.");
      }
      if (token == "[]")
      {
        return tree;
      }
      in >> token;
      std::istringstream input(token);
      input >> aux;
      if (in.fail() or input.fail())
      {
        throw std::runtime_error("Wrong input format.");
      }
      tree = BTree<T>::create(aux);
      tree->set_left(BTree<T>::create(in));
      tree->set_right(BTree<T>::create(in));
      in >> token;
      if (in.fail() or token  != "]")
      {
        throw std::runtime_error("Wrong input format.");
      }
      //
      return tree;
  }

template<class T>
  bool BTree<T>::is_empty () const
  {
      bool ret_v = false;
      //
      ret_v = (root_ == nullptr);
      //
      return ret_v;
  }

template<class T>
  T BTree<T>::item() const
  {
      assert(!is_empty());
      T ret_v;
      //
      ret_v = root_->item();
      //
      return ret_v;
  }

template<class T>
  typename BTree<T>::Ref BTree<T>::left() const
  {
      assert(!is_empty());
      BTree<T>::Ref subtree = nullptr;
      //
      //Hint: use the private constructor given a root node.
      subtree = BTree<T>::create(root_->left());

      //
      return subtree;
  }

template<class T>
  typename BTree<T>::Ref BTree<T>::right() const
  {
      assert(!is_empty());
      BTree<T>::Ref subtree = nullptr;
      //
      //Hint: use the private constructor given a root node.
      subtree = BTree<T>::create(root_->right());
      //
      return subtree;
  }

template<class T>
  std::ostream& BTree<T>::fold(std::ostream& out) const
  {
      //
      if (is_empty())
      {
        out << "[]";
      }
      else
      {
        out << "[ " << root_->item() << " ";
        left()->fold(out);
        out << " ";
        right()->fold(out);
        out << " ]"; 
      }
      //
      return out;
  }

  template<class T>
    void BTree<T>::create_root(const T& it)
    {
        assert(is_empty());
        //
        root_ = BTNode<T>::create(it, nullptr, nullptr);
        //
        assert(!is_empty());
        assert(item()==it);
        assert(left()->is_empty());
        assert(right()->is_empty());

    }

template<class T>
  void BTree<T>::set_item(const T& new_it)
  {
      assert(!is_empty());
      //
      root_->set_item(new_it);
      //
      assert(item()==new_it);
  }

template<class T>
  void BTree<T>::set_left(typename BTree<T>::Ref new_left)
  {
      assert(!is_empty());
      //
      root_->set_left(new_left->root());
      //
      assert(left()->root()==new_left->root());
  }

template<class T>
  void BTree<T>::set_right(typename BTree<T>::Ref new_right)
  {
      assert(!is_empty());
      //
      root_->set_right(new_right->root());
      //
      assert(right()->root()==new_right->root());
  }

template<class T>
  BTree<T>::BTree (typename BTNode<T>::Ref n)
  {
      //
      root_ = n;
      //
      assert(root()==n);
  }

template<class T>
typename BTree<T>::Ref BTree<T>::create(typename BTNode<T>::Ref root)
  {
      //We cannot use std::make_shared here
      //because the constructor is protected.
      typename BTree<T>::Ref tree ( new BTree<T>(root) );
      return tree;
  }

template<class T>
  typename BTNode<T>::Ref BTree<T>::root() const
  {
      typename BTNode<T>::Ref node;
      //
      node = root_;
      //
      return node;
  }

template<class T>
  void BTree<T>::set_root(typename BTNode<T>::Ref new_root)
  {
      //
      root_ = new_root;
      //
      assert(root()==new_root);
  }

