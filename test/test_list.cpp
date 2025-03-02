#include "gtest.h"
#include "list.h"

TEST(list_test, push_back)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.get_first()->value, 1);
}

TEST(list_test, push_front)
{
    List<int> list;

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.get_first()->value, 1);
}

TEST(list_test, pop_front)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.pop_front();

    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_first()->value, 2);
}

TEST(list_test, insert)
{
    List<int> list;

    list.push_back(1);
    list.push_back(3);
    list.insert(2, list.get_first());

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.get_first()->next->value, 2);
}

TEST(list_test, erase)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* node = list.get_first()->next;

    list.erase(node);

    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.get_first()->next->value, 3);
}

TEST(list_test, clear)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();

    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.get_first(), nullptr);
}

TEST(list_test, get_last)
{
    List<int> list;

    EXPECT_EQ(list.get_last(), nullptr);

    list.push_back(1);
    list.push_back(2);

    EXPECT_EQ(list.get_last()->value, 2);
}

TEST(list_test, assign_operator)
{
    List<int> list1;

    list1.push_back(1);
    list1.push_back(2);

    List<int> list2;

    list2.push_back(3);
    list2.push_back(4);

    list2 = list1;

    EXPECT_EQ(list2.get_size(), 2);
    EXPECT_EQ(list2.get_first()->value, 1);
    EXPECT_EQ(list2.get_first()->next->value, 2);
}

TEST(list_test, copy_constructor)
{
    List<int> list1;

    list1.push_back(1);
    list1.push_back(2);

    List<int> list2 = list1;

    EXPECT_EQ(list2.get_size(), 2);
    EXPECT_EQ(list2.get_first()->value, 1);
    EXPECT_EQ(list2.get_first()->next->value, 2);
}

TEST(list_test, pop_front_empty_list)
{
    List<int> list;

    EXPECT_THROW(list.pop_front(), std::logic_error);
}

TEST(list_test, erase_node_not_in_list)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);

    Node<int>* node = new Node<int>(3);

    EXPECT_THROW(list.erase(node), std::logic_error);
}

TEST(list_test, erase_from_empty_list)
{
    List<int> list;

    EXPECT_THROW(list.erase(nullptr), std::logic_error);
}

TEST(list_test, iterator_comparison)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);

    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();

    EXPECT_EQ(it1, it2);

    it1++;

    EXPECT_NE(it1, it2);
}

TEST(list_test, insert_at_nullptr)
{
    List<int> list;

    list.push_back(2);

    list.insert(1, nullptr);

    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.get_first()->value, 1);
}

TEST(list_test, erase_last_element)
{
    List<int> list;

    list.push_back(1);

    list.erase(list.get_first());

    EXPECT_EQ(list.get_size(), 0);
    EXPECT_EQ(list.get_first(), nullptr);
}

TEST(list_test, insert_after_last)
{
    List<int> list;

    list.push_back(1);

    list.insert(2, list.get_last());

    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.get_last()->value, 2);
}

TEST(list_test, multiple_push_pop)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_front(0);

    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.get_first()->value, 0);

    list.pop_front();
    list.pop_front();

    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.get_first()->value, 2);
}

TEST(list_test, self_assignment)
{
    List<int> list;

    list.push_back(1);
    list.push_back(2);

    list = list;

    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.get_first()->value, 1);
    EXPECT_EQ(list.get_first()->next->value, 2);
}