#include <gtest/gtest.h>
#include "LinkedList.h"

class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        list = new LinkedList<int>();
    }
    
    void TearDown() override {
        delete list;
    }
    
    LinkedList<int>* list;
};

TEST_F(LinkedListTest, EmptyList) {
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}

TEST_F(LinkedListTest, PushFront) {
    list->pushFront(10);
    EXPECT_FALSE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 1);
    EXPECT_EQ(list->getFirst(), 10);
    EXPECT_EQ(list->getLast(), 10);
    
    list->pushFront(20);
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->getFirst(), 20);
    EXPECT_EQ(list->getLast(), 10);
}

TEST_F(LinkedListTest, PushBack) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    EXPECT_EQ(list->getSize(), 3);
    EXPECT_EQ(list->getFirst(), 10);
    EXPECT_EQ(list->getLast(), 30);
}

TEST_F(LinkedListTest, PopFront) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    int value = list->popFront();
    EXPECT_EQ(value, 10);
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->getFirst(), 20);
}

TEST_F(LinkedListTest, PopBack) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    int value = list->popBack();
    EXPECT_EQ(value, 30);
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->getLast(), 20);
}

TEST_F(LinkedListTest, InsertAt) {
    list->pushBack(10);
    list->pushBack(30);
    list->pushBack(40);
    
    list->insertAt(1, 20);
    EXPECT_EQ(list->getSize(), 4);
    EXPECT_EQ(list->getAt(1), 20);
    EXPECT_EQ(list->getAt(2), 30);
}

TEST_F(LinkedListTest, RemoveAt) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    int value = list->removeAt(1);
    EXPECT_EQ(value, 20);
    EXPECT_EQ(list->getSize(), 2);
    EXPECT_EQ(list->getAt(0), 10);
    EXPECT_EQ(list->getAt(1), 30);
}

TEST_F(LinkedListTest, Reverse) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    list->reverse();
    EXPECT_EQ(list->getAt(0), 30);
    EXPECT_EQ(list->getAt(1), 20);
    EXPECT_EQ(list->getAt(2), 10);
}

TEST_F(LinkedListTest, Find) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    EXPECT_EQ(list->find(20), 1);
    EXPECT_EQ(list->find(40), -1);
}

TEST_F(LinkedListTest, Clear) {
    list->pushBack(10);
    list->pushBack(20);
    list->pushBack(30);
    
    list->clear();
    EXPECT_TRUE(list->isEmpty());
    EXPECT_EQ(list->getSize(), 0);
}
