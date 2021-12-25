#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include "dlist.h"
using namespace std;
template <class T>
bool Dlist<T>::isEmpty() const //Check whether is empty
{
    return (first == NULL);
};

template <class T>
void Dlist<T>::insertFront(T *op) //Insert to front
{
    node* temp = new node;
    temp->op = op;
    temp->prev = NULL;
    temp->next = first;
    if(first!=NULL)
    {
        first->prev = temp;
    }
    else
    {
        last = temp;
    }
    first = temp;
}

template <class T>
void Dlist<T>::insertBack(T *op) //Insert to back
{
    node *temp = new node;
    temp->op = op;
    temp->prev = last;
    temp->next = NULL;
    if(last!=NULL)
    {
        last->next = temp;
    }
    else
    {
        first = temp;
    }
    last = temp;
}

template <class T>
T* Dlist<T>::removeFront() //TODO Empty Check
{
    if(first == NULL)
    {
        throw emptyList();
    }
    node* temp = first;
    first = temp->next;
    if(first!= NULL)
    {
        first->prev = NULL;
    }
    else
    {
        last = NULL;
    }
    T* op = temp->op;
    delete temp;
    return op;
}

template <class T>
T* Dlist<T>::removeBack() //TODO Empty Check
{
    if(last == NULL)
    {
        throw emptyList();
    }
    node* temp = last;
    last = temp->prev;
    if(last != NULL)
    {
        last->next = NULL;
    }
    else
    {
        first = NULL;
    }
    T* op = temp->op;
    delete temp;
    return op;
}

template <class T>
Dlist<T>::Dlist():first(NULL),last(NULL){} //Constructor 

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l) //Copy function
{
    copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T> &l) //Assignment function
{
    removeAll();
    copyAll(l);
}

template <class T>
Dlist<T>::~Dlist() //Destructor
{
    removeAll();
}

template <class T>
void Dlist<T>::removeAll()//Remove all function
{
    while(!isEmpty())
    {
        delete removeFront();
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l)//Copy All function
{
    if(l->isEmpty())
    {
        return;
    }
    node* current = l->first;
    do
    {
        T* op = new T;
        *op = *(current->op);
        insertBack(op);
        current = current->next;
    } while (current!=NULL);
}

#endif
