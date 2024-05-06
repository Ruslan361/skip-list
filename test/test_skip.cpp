#include <gtest.h>
#include "skip.h"

// Тестирование вставки элементов
TEST(SkipListTest, InsertTest) {
    SkipList<int> skipList;
    skipList.insert(5);
    skipList.insert(10);
    skipList.insert(3);

    EXPECT_TRUE(skipList.search(5));
    EXPECT_TRUE(skipList.search(10));
    EXPECT_TRUE(skipList.search(3));
    EXPECT_FALSE(skipList.search(7)); // Этого элемента нет в списке
}

// Тестирование удаления элементов
TEST(SkipListTest, EraseTest) {
    SkipList<int> skipList;
    skipList.insert(5);
    skipList.insert(10);
    skipList.insert(3);
    skipList.erase(10);

    EXPECT_TRUE(skipList.search(5));
    EXPECT_FALSE(skipList.search(10)); // Удаленный элемент
    EXPECT_TRUE(skipList.search(3));
    EXPECT_FALSE(skipList.search(7)); // Этого элемента нет в списке
}

// Тестирование проверки пустоты списка
TEST(SkipListTest, EmptyTest) {
    SkipList<int> skipList;

    EXPECT_TRUE(skipList.empty());

    skipList.insert(5);

    EXPECT_FALSE(skipList.empty());
}

// Тестирование размера списка
TEST(SkipListTest, SizeTest) {
    SkipList<int> skipList;

    EXPECT_EQ(skipList.size(), 0);

    skipList.insert(5);
    skipList.insert(10);
    skipList.insert(3);

    EXPECT_EQ(skipList.size(), 3);
}
// Тесты для метода insert
TEST(SkipListTest, Insert) {
    SkipList<int> skipList;

    skipList.insert(5);
    ASSERT_TRUE(skipList.search(5));

    skipList.insert(10);
    ASSERT_TRUE(skipList.search(10));
}

// Тесты для метода search
TEST(SkipListTest, Search) {
    SkipList<int> skipList;

    skipList.insert(5);
    skipList.insert(10);

    ASSERT_TRUE(skipList.search(5));
    ASSERT_TRUE(skipList.search(10));
    ASSERT_FALSE(skipList.search(3));
}

// Тесты для метода erase
TEST(SkipListTest, Erase) {
    SkipList<int> skipList;

    skipList.insert(5);
    skipList.insert(10);

    skipList.erase(5);
    ASSERT_FALSE(skipList.search(5));
    ASSERT_TRUE(skipList.search(10));

    skipList.erase(10);
    ASSERT_FALSE(skipList.search(10));
}

// Тесты для метода size
TEST(SkipListTest, Size) {
    SkipList<int> skipList;

    ASSERT_EQ(skipList.size(), 0);

    skipList.insert(5);
    ASSERT_EQ(skipList.size(), 1);

    skipList.insert(10);
    ASSERT_EQ(skipList.size(), 2);

    skipList.erase(5);
    ASSERT_EQ(skipList.size(), 1);
}

// Тесты для метода empty
TEST(SkipListTest, Empty) {
    SkipList<int> skipList;

    ASSERT_TRUE(skipList.empty());

    skipList.insert(5);
    ASSERT_FALSE(skipList.empty());

    skipList.erase(5);
    ASSERT_TRUE(skipList.empty());
}