#include <stdexcept>
#include <iostream>
#include "DNode.h"

template <typename e>
class DLinkedList
{
private:
    DNode<e> *head, *current, *tail;
    int size;

public:
    DLinkedList()
    {
        head = current = new DNode<e>();
        head->next = tail = new DNode<e>(head);
        size = 0;
    }

    ~DLinkedList()
    {
        clear();
        delete head;
        delete tail;
    }

    bool isEmpty() {
        return head->next == tail;
    }

    void insert(e element)
    {
        current->next = new DNode<e>(element, current, current->next);
        current->next->next->previous = current->next;
        size++;
    }

    void append(e element)
    {
        tail->previous = new DNode<e>(element, tail->previous, tail);
        tail->previous->previous->next = tail->previous;
        size++;
    }

    e remove() throw (std::runtime_error)
    {
        if(current->next == tail) {
            throw std::runtime_error("No hay elemento actual.");
        }

        DNode<e> *aux = current->next;
        e res = aux->element;
        current->next = current->next->next;
        current->next->previous = current;

        size--;
        delete aux;
        return res;
    }

    e getElement() throw (std::runtime_error)
    {
        if(current->next == tail) {
            throw std::runtime_error("No hay elemento actual.");
        }

        return current->next->element;
    }

    void clear()
    {
        while(head->next != tail) {
            current = head->next;
            head->next = head->next->next;
            delete current;
        }

        tail->previous = current = head;
        size = 0;
    }

    void goToStart()
    {
        current = head;
    }

    void goToEnd()
    {
        current = tail->previous;
    }

    void goToPos(int pos) throw (std::runtime_error)
    {
        if((pos < 0) || (pos > size)) {
            throw std::runtime_error("Indice fuera de rango.");
        }

        current = head;

        for(int i = 0; i < pos; i++) {
            current = current->next;
        }
    }

    void previous() throw (std::runtime_error)
    {
        if(current->previous == NULL) {
            throw std::runtime_error("No hay elementos previos.");
        }

        current = current->previous;
    }

    void next() throw (std::runtime_error)
    {
        if(current->next == tail) {
            throw std::runtime_error("No hay elementos posteriores.");
        }

        current = current->next;
    }

    int getPos()
    {
        DNode<e> *aux = head;
        int pos = 0;

        while(aux != current) {
            aux = aux->next;
            pos++;
        }

        return pos;
    }

    int getSize()
    {
        return size;
    }

    void linkList(DLinkedList<e> *forwardList) throw (std::runtime_error)
    {
        if(forwardList->getSize() == 0) {
            throw std::runtime_error("La lista ha concatenar se encuentra vacia.");
        }

        forwardList->goToStart();

        for(int i = 0; i < forwardList->getSize(); i++) {
            append(forwardList->getElement());
            i < forwardList->getSize() - 1 ? forwardList->next() : forwardList->goToStart();
        }
    }
};
