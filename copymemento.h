#ifndef COPYMEMENTO_H
#define COPYMEMENTO_H

#include <QStack>

template<typename T>
class CopyMemento
{
public:
    CopyMemento();
    ~CopyMemento();

    void save(const T &o);
    void clear();
    void setMaximumSaving(int max);
    int maximumSaving() const;
    T undo();
    T redo();
    T current() const;
    int undoCount() const;
    int redoCount() const;
    bool hasCurrent() const;

private:
    QStack<T*> stackUndo;
    T *currentObject;
    QStack<T*> stackRedo;
    int max;

    void aligneMaximum();
};

#endif // COPYMEMENTO_H
