#include "copymemento.h"

/*============================================*/
//  CONSTRUCTOR / DESTRUCTOR
/*============================================*/

template<typename T>
CopyMemento<T>::CopyMemento()
{
    max = 0;
    currentObject = 0;
}

template<typename T>
CopyMemento<T>::~CopyMemento()
{
    clear();
}

/*============================================*/
//  ASSESSOR / MUTATOR
/*============================================*/

template<typename T>
void CopyMemento<T>::save(const T &o)
{
    if(&o == 0) return;

    qDeleteAll(stackRedo);
    stackRedo.clear();

    if(currentObject != 0)
    {
        stackUndo.push(currentObject);
        aligneMaximum();
    }

    currentObject = new T(o);
}

template<typename T>
void CopyMemento<T>::clear()
{
    if(currentObject != 0)
    {
        delete currentObject;
        currentObject = 0;
    }

    qDeleteAll(stackRedo);
    stackRedo.clear();
    qDeleteAll(stackUndo);
    stackUndo.clear();
}

template<typename T>
void CopyMemento<T>::setMaximumSaving(int max)
{
    this->max = max;
    aligneMaximum();
}

template<typename T>
int CopyMemento<T>::maximumSaving() const
{
    return max;
}

template<typename T>
T CopyMemento<T>::undo()
{
    Q_ASSERT_X(stackUndo.size() > 0, "undo",
               "CopyMemento undo list is empty");

    if(currentObject != 0)
    {
        stackRedo.push(currentObject);
    }

    currentObject = stackUndo.pop();
    return *currentObject;
}

template<typename T>
T CopyMemento<T>::redo()
{
    Q_ASSERT_X(stackRedo.size() > 0, "redo",
               "CopyMemento redo list is empty");

    if(currentObject != 0)
    {
        stackUndo.push(currentObject);
    }

    currentObject = stackRedo.pop();
    return *currentObject;
}


template<typename T>
T CopyMemento::current() const
{
    return *currentObject;
}

template<typename T>
int CopyMemento<T>::undoCount() const
{
    return stackUndo.size();
}

template<typename T>
int CopyMemento<T>::redoCount() const
{
    return stackRedo.size();
}

template<typename T>
bool CopyMemento::hasCurrent() const
{
    return currentObject != 0;
}

/*============================================*/
//  PRIVATE
/*============================================*/

template<typename T>
void CopyMemento<T>::aligneMaximum()
{
    if(stackUndo.size() > max && max > 0)
    {
        for (int i = stackUndo.size(); i > max; --i)
        {
            T *t = stackUndo.last();
            stackUndo.removeLast();
            delete t;
        }
    }
}

