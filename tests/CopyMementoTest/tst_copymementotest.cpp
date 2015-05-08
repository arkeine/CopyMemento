#include <QString>
#include <QtTest>
#include "../../copymemento.cpp"

/*============================================*/
//  DECLARATION
/*============================================*/

class CopyMementoTest : public QObject
{
    Q_OBJECT

public:
    CopyMementoTest();

    struct Data{
        int value;
    };

private Q_SLOTS:
    void testSave();
    void testUndoRedo();
    void testClear();
    void testRemoveRedo();
};

CopyMementoTest::CopyMementoTest()
{
}

/*============================================*/
//  TESTS CASES
/*============================================*/

void CopyMementoTest::testSave()
{
    CopyMemento<Data> memento;
    memento.setMaximumSaving(2);
    Data d;

    d.value = 0;
    memento.save(d);
    QCOMPARE(memento.undoCount(), 0);
    QCOMPARE(memento.redoCount(), 0);
    d.value = 1;
    memento.save(d);
    QCOMPARE(memento.undoCount(), 1);
    QCOMPARE(memento.redoCount(), 0);
    d.value = 2;
    memento.save(d);
    QCOMPARE(memento.undoCount(), 2);
    QCOMPARE(memento.redoCount(), 0);
    d.value = 3;
    memento.save(d);
    QCOMPARE(memento.undoCount(), 2);
    QCOMPARE(memento.redoCount(), 0);
}

void CopyMementoTest::testUndoRedo()
{
    CopyMemento<Data> memento;
    Data d;

    d.value = 0;
    memento.save(d);
    d.value = 1;
    memento.save(d);
    d.value = 2;
    memento.save(d);
    d.value = 3;
    memento.save(d);

    QCOMPARE(memento.undo().value, 2);
    QCOMPARE(memento.redoCount(), 1);
    QCOMPARE(memento.undo().value, 1);
    QCOMPARE(memento.redoCount(), 2);
    QCOMPARE(memento.undo().value, 0);
    QCOMPARE(memento.redoCount(), 3);

    QCOMPARE(memento.redo().value, 1);
    QCOMPARE(memento.redoCount(), 2);
    QCOMPARE(memento.redo().value, 2);
    QCOMPARE(memento.redoCount(), 1);
    QCOMPARE(memento.redo().value, 3);
    QCOMPARE(memento.redoCount(), 0);
}

void CopyMementoTest::testClear()
{
    CopyMemento<Data> memento;
    Data d;

    d.value = 0;
    memento.save(d);
    d.value = 1;
    memento.save(d);
    d.value = 2;
    memento.save(d);
    d.value = 3;
    memento.save(d);
    memento.undo();

    QCOMPARE(memento.undoCount(), 2);
    QCOMPARE(memento.redoCount(), 1);

    memento.clear();

    QCOMPARE(memento.undoCount(), 0);
    QCOMPARE(memento.redoCount(), 0);
}

void CopyMementoTest::testRemoveRedo()
{
    CopyMemento<Data> memento;
    Data d;

    d.value = 0;
    memento.save(d);
    d.value = 1;
    memento.save(d);
    d.value = 2;
    memento.save(d);
    d.value = 3;
    memento.save(d);

    QCOMPARE(memento.undo().value, 2);
    QCOMPARE(memento.undo().value, 1);
    QCOMPARE(memento.redoCount(), 2);

    d.value = 4;
    memento.save(d);

    QCOMPARE(memento.redoCount(), 0);
    QCOMPARE(memento.undo().value, 1);
}

QTEST_APPLESS_MAIN(CopyMementoTest)

#include "tst_copymementotest.moc"
