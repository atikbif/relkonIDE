// тестирование итератора на базе QT TEST

#include <QStringList>
#include <QtTest>

#include "namesortiterator.h"

class NameSortIteratorTest : public QObject
{
    Q_OBJECT

public:
    NameSortIteratorTest();

private Q_SLOTS:
    void testCase1();
};

NameSortIteratorTest::NameSortIteratorTest()
{
}

void NameSortIteratorTest::testCase1()
{
    IDStorage* storage = new IDStorage();
    CompositeVar v1;
    v1.setName("startPoint");
    storage->addVar(&v1);
    QStringList varNames;
    varNames << "varD" << "varA" << "varb" << "varC" << "varB";

    foreach (QString vName, varNames) {
       CompositeVar* v = new CompositeVar();
       v->setName(vName);
       v1.addChild(*v);
       storage->addVar(v);
    }

    QStringList sortList;
    NameSortIterator it(*storage);
    it.goToID(v1.getID());
    it.down();
    it.first();
    QVERIFY2(it.getItemCount()==varNames.count(),"Incorrect count of elements");
    for(int i=0;i<it.getItemCount();i++) {
        QString id = it.currentID();
        CompositeVar var;
        storage->getVarByID(id,var);
        sortList << var.getName();
        it.next();
    }

    QVERIFY2(sortList.count()==varNames.count(),"Incorrect count of elements");

    QVERIFY2(sortList.at(0)=="varA", "sort error - element 1");
    QVERIFY2(sortList.at(1)=="varB", "sort error - element 2");
    QVERIFY2(sortList.at(2)=="varC", "sort error - element 3");
    QVERIFY2(sortList.at(3)=="varD", "sort error - element 4");
    QVERIFY2(sortList.at(4)=="varb", "sort error - element 5");
}

QTEST_APPLESS_MAIN(NameSortIteratorTest)

#include "tst_namesortiteratortest.moc"
