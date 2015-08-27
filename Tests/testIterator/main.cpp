#include <gtest/gtest.h>
#include "namesortiterator.h"
#include <QStringList>

// тест итератора для сортировки переменных в дереве по именам
// на базе google test

class IterTest: public ::testing::Test
{
protected:
    CompositeVar* varHead;
    CompositeVar* varForNamesWithoutNumbers;
    CompositeVar* varForNamesWithNumbers;
    IDStorage* storage;
    QStringList list1,list2;

    IterTest() {

    }
    virtual ~IterTest() {

    }

    virtual void SetUp() {
        varHead = new CompositeVar();
        varHead->setName("head");
        storage = new IDStorage();
        storage->addVar(varHead);

        varForNamesWithoutNumbers = new CompositeVar();
        varForNamesWithoutNumbers->setName("withoutNumbers");
        varHead->addChild(*varForNamesWithoutNumbers);
        storage->addVar(varForNamesWithoutNumbers);

        varForNamesWithNumbers = new CompositeVar();
        varForNamesWithNumbers->setName("withNumbers");
        varHead->addChild(*varForNamesWithNumbers);
        storage->addVar(varForNamesWithNumbers);

        list1 << "VarC" << "VarA" << "Varc" << "VarB" << "VarD";
        list2 << "Var7Last" << "VarB" << "Vara" << "VarA" << "Var12Last" << "Var13";

        foreach (QString name, list1) {
           CompositeVar* var = new CompositeVar();
           var->setName(name);
           varForNamesWithoutNumbers->addChild(*var);
           storage->addVar(var);
        }

        foreach (QString name, list2) {
           CompositeVar* var = new CompositeVar();
           var->setName(name);
           varForNamesWithNumbers->addChild(*var);
           storage->addVar(var);
        }

    }

    virtual void TearDown() {
        delete storage;
    }

};

TEST_F(IterTest, without_numbers) {
    QString id = varForNamesWithoutNumbers->getID();
    NameSortIterator it(*storage);
    it.goToID(id);
    it.down();
    ASSERT_EQ(list1.count(),it.getItemCount());
    QStringList sortList;
    for(int i=0;i<it.getItemCount();i++) {
        CompositeVar var;
        QString id = it.currentID();
        storage->getVarByID(id,var);
        sortList << var.getName();
        it.next();
    }
    ASSERT_EQ(list1.count(),sortList.count());
    ASSERT_STREQ("VarA",sortList.at(0).toStdString().c_str());
    ASSERT_STREQ("VarB",sortList.at(1).toStdString().c_str());
    ASSERT_STREQ("VarC",sortList.at(2).toStdString().c_str());
    ASSERT_STREQ("VarD",sortList.at(3).toStdString().c_str());
    ASSERT_STREQ("Varc",sortList.at(4).toStdString().c_str());
}

TEST_F(IterTest, with_numbers) {
    QString id = varForNamesWithNumbers->getID();
    NameSortIterator it(*storage);
    it.goToID(id);
    it.down();
    ASSERT_EQ(list2.count(),it.getItemCount());
    QStringList sortList;
    for(int i=0;i<it.getItemCount();i++) {
        CompositeVar var;
        QString id = it.currentID();
        storage->getVarByID(id,var);
        sortList << var.getName();
        it.next();
    }
    ASSERT_EQ(list2.count(),sortList.count());
    ASSERT_STREQ("Var13",sortList.at(0).toStdString().c_str());
    ASSERT_STREQ("Var7Last",sortList.at(1).toStdString().c_str());
    ASSERT_STREQ("Var12Last",sortList.at(2).toStdString().c_str());
    ASSERT_STREQ("VarA",sortList.at(3).toStdString().c_str());
    ASSERT_STREQ("Vara",sortList.at(4).toStdString().c_str());
    ASSERT_STREQ("VarB",sortList.at(5).toStdString().c_str());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
