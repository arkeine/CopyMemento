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
    int undoCount() const;
    int redoCount() const;

private:
    QStack<T*> stackUndo;
    T *current;
    QStack<T*> stackRedo;
    int max;

    void aligneMaximum();
};

#endif // COPYMEMENTO_H
