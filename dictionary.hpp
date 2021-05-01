#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <stdexcept>
#include "stack.hpp"

#define DICTIONARY_ALLOCATED_BLOCK 0x10


template<typename KeyType, typename ValueType>
struct Node
{
    KeyType key;
    ValueType value;

    Node() = default;


    Node& operator=(const Node<KeyType, ValueType> & other)
    {
        key = other.key;
        value = other.value;
        return *this;
    }
};






template<typename KeyType, typename ValueType>
class Dictionary
{
private:
    Node<KeyType, ValueType> *_dataptr;
    unsigned int _count = 0;
    unsigned int _allocated = DICTIONARY_ALLOCATED_BLOCK;
    unsigned int _currentIterator = 0;

    void Reallocate();

    Node<KeyType, ValueType> * _root = nullptr;
    
    int findKey(const KeyType & key) const;
    int findParent(const KeyType &key) const;

public:

    Dictionary();
    ~Dictionary();

    void Insert(const KeyType & key, const ValueType & value);

    ValueType Remove(const KeyType & key);

    Stack<KeyType> Keys() const;

    bool IsEmpty() const;

    bool Contains(const KeyType & key) const;

    ValueType At(const KeyType & key) const;
};


template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::Dictionary()
{
    _dataptr = new Node<KeyType, ValueType> [_allocated];
    for(int i = 0; i < _allocated; i++)
    {
        _dataptr[i].key = -1;
    }

}

template<typename KeyType, typename ValueType>
Dictionary<KeyType, ValueType>::~Dictionary()
{
    delete[] _dataptr;
}


template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::Insert(const KeyType & key, const ValueType & value)
{ 
    if(_count == _allocated)
    {
        Reallocate();
    }
    if(_count == 0)
    { 
        _dataptr[_count].value = value;
        _dataptr[_count].key = key;
       _count++;
        
        return;
    }
    else 
    {
        int ind = 0;
        for(int i = 0; i < _count; i++)
        {
            if(key < _dataptr[ind].key)
            {
                 ind = (2*ind)+1;
                if(_dataptr[ind].key == -1)
                {
                    _dataptr[ind].value = value;
                    _dataptr[ind].key = key;
                    _count++;
                    return;
                }
               
            }
            if(key > _dataptr[ind].key)
            {
        
                ind = (2*ind)+2;
                if(_dataptr[ind].key == -1)
                {
                    _dataptr[ind].value = value;
                    _dataptr[ind].key = key;
                    _count ++;
                    return;
                }
            }
        }
    }
    return;
}

template<typename KeyType, typename ValueType>
ValueType Dictionary<KeyType, ValueType>::Remove(const KeyType & key)
{
   int loc = findKey(key);
    if(loc < 0)
    {
        throw new std::range_error("out of bounds error");
    }
    
    ValueType tmp = _dataptr[loc].value;
    _dataptr[loc].key = -1;
    _count --;
    return tmp;
}

// 1)   creates a vector of keys
// 2)   calls InOrderKeys on the root and adds all keys of the tree into the 
//      vector of Keys.
template<typename KeyType, typename ValueType>
Stack<KeyType> Dictionary<KeyType, ValueType>::Keys() const
{
   
    Stack<uint32_t> keys; 
    for(int i = 0; i < _count; i++)
    {   
        keys.AddItem(_dataptr[i].key);

    }
   
    return keys;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::IsEmpty() const
{   
    return _count == 0;
}

template<typename KeyType, typename ValueType>
bool Dictionary<KeyType, ValueType>::Contains(const KeyType & key) const
{
    return findKey(key) > -1;
}

template<typename KeyType, typename ValueType>
ValueType Dictionary<KeyType, ValueType>::At(const KeyType & key) const
{
    return _dataptr[findKey(key)].value;
}

template<typename KeyType, typename ValueType>
int Dictionary<KeyType, ValueType>::findKey(const KeyType & key ) const
{
   if(IsEmpty())
    {
        return -1;
    }
    int i = 0 ; 
    int ind = 0;

    // Root 
    if(_dataptr[i].key == key)
    {
        return i;
    }
    while(i < _count)
    {
        if(_dataptr[ind].key > key)
        {
            ind = 2*i+1;
            if(_dataptr[ind].key == key)
            {
                return ind;
            }
        }

        else
        {
            ind = 2*i+2;
            if(_dataptr[ind].key == key)
            {
                return ind;
            }
        }
        i++;
    }
    return -1;
}
template<typename KeyType, typename ValueType>
int Dictionary<KeyType, ValueType>::findParent(const KeyType & key) const
{
    if(IsEmpty())
    {
       return -1;
    }
   else
   {
       int i = findKey(key);
       if(i < 0)
       {
           return -1;
       }
       int parent = (i-1)/2;
       return parent;

    }
    return -1;
}

template<typename KeyType, typename ValueType>
void Dictionary<KeyType, ValueType>::Reallocate()
{
    _allocated += DICTIONARY_ALLOCATED_BLOCK;
    Node<KeyType, ValueType> * tmpList = new Node<KeyType, ValueType>[_allocated];
    
    for(int i = 0; i < _count; i++)
    {
        tmpList[i].key = _dataptr[i].key;
        tmpList[i].value = _dataptr[i].value;
    }
    delete _dataptr;
    _dataptr = tmpList;
}

#endif