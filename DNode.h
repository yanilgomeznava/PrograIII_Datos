#ifndef DNODO_H
#define DNODO_H

template <typename t>
class DNode
{
public:
    t element;
    DNode<t> *previous, *next;

    DNode(DNode<t> *pPrevious = NULL, DNode<t> *pNext = NULL)
    {
        previous = pPrevious;
        next = pNext;
    }

    DNode(t pElement, DNode<t> *pPrevious = NULL, DNode<t> *pNext = NULL)
    {
        element = pElement;
        previous = pPrevious;
        next = pNext;
    }
};

#endif // DNODO_H
