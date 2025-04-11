#include <gtest/gtest.h>
#include <algorithm>
#include <numeric>
#include <vector>
#include <utility>
#include <string>
#include <functional>
#include <type_traits>
#include "../lib/sorted_vector.hpp"

// Тестовая фикстура для тестов SortedVector<int>
class SortedVectorIntTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Предустановка для каждого теста
    }

    void TearDown() override {
        // Очистка после каждого теста
    }
};

// Тестирование типов и свойств контейнера
TEST(SortedVectorTraitsTest, HasRequiredTypes) {
    // Проверяем наличие необходимых типов
    using Container = SortedVector<int>;
    using T = typename Container::value_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;
    using iterator = typename Container::iterator;
    using const_iterator = typename Container::const_iterator;
    using size_type = typename Container::size_type;
    using difference_type = typename Container::difference_type;
    
    // Тест проверяет только компилируемость, если типы не определены, код не скомпилируется
    SUCCEED() << "All required types are defined";
}

TEST(SortedVectorTraitsTest, IteratorSupportsRandomAccess) {
    // Проверяем, что итератор поддерживает random access
    using Container = SortedVector<int>;
    using iterator = typename Container::iterator;
    
    static_assert(
        std::is_base_of_v<std::random_access_iterator_tag, 
                          typename std::iterator_traits<iterator>::iterator_category>,
        "Iterator must be random access"
    );
    
    SUCCEED() << "Iterator supports random access";
}

// Тесты базовых операций
TEST_F(SortedVectorIntTest, DefaultConstructor) {
    SortedVector<int> empty;
    EXPECT_TRUE(empty.empty()) << "Default constructor should create empty container";
    EXPECT_EQ(empty.size(), 0) << "Size of empty container should be 0";
}

TEST_F(SortedVectorIntTest, InsertAndSort) {
    SortedVector<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(8);
    c.insert(1);
    
    EXPECT_EQ(c.size(), 4) << "Size after insertion should be 4";
    EXPECT_FALSE(c.empty()) << "Container should not be empty after insertion";
    EXPECT_TRUE(std::is_sorted(c.begin(), c.end())) << "Elements should be kept sorted";
    
    std::vector<int> expected{1, 3, 5, 8};
    EXPECT_TRUE(std::equal(c.begin(), c.end(), expected.begin())) 
        << "Elements should be in correct sorted order";
}

TEST_F(SortedVectorIntTest, ElementAccess) {
    SortedVector<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(8);
    c.insert(1);
    
    EXPECT_EQ(c.front(), 1) << "front() should return smallest element";
    EXPECT_EQ(c.back(), 8) << "back() should return largest element";
    EXPECT_EQ(c[1], 3) << "operator[] should work correctly";
    EXPECT_EQ(c.at(2), 5) << "at() should work correctly";
    
    EXPECT_THROW(c.at(10), std::out_of_range) << "at() should throw for out-of-range access";
}

TEST_F(SortedVectorIntTest, EraseAndClear) {
    SortedVector<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(8);
    c.insert(1);
    
    auto it = c.begin() + 1; // указывает на 3
    c.erase(it);
    EXPECT_EQ(c.size(), 3) << "Size should be reduced after erase";
    
    std::vector<int> expected_after_erase{1, 5, 8};
    EXPECT_TRUE(std::equal(c.begin(), c.end(), expected_after_erase.begin()))
        << "Element should be correctly erased";
    
    c.clear();
    EXPECT_TRUE(c.empty()) << "Container should be empty after clear()";
    EXPECT_EQ(c.size(), 0) << "Size should be 0 after clear()";
}

// Тесты операций поиска
TEST_F(SortedVectorIntTest, Contains) {
    SortedVector<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(8);
    c.insert(1);
    
    EXPECT_TRUE(c.contains(3)) << "contains() should find existing element";
    EXPECT_FALSE(c.contains(7)) << "contains() should correctly report non-existing element";
}

TEST_F(SortedVectorIntTest, Find) {
    SortedVector<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(8);
    c.insert(1);
    c.insert(3); // дубликат
    
    auto it = c.find(3);
    EXPECT_NE(it, c.end()) << "find() should locate existing element";
    EXPECT_EQ(*it, 3) << "find() should return iterator to correct element";
    
    auto it_not_found = c.find(7);
    EXPECT_EQ(it_not_found, c.end()) << "find() should return end() for non-existing element";
}

TEST_F(SortedVectorIntTest, EqualRange) {
    SortedVector<int> c;
    c.insert(5);
    c.insert(3);
    c.insert(8);
    c.insert(1);
    c.insert(3); // дубликат
    
    auto [first, last] = c.equal_range(3);
    auto count = std::distance(first, last);
    EXPECT_EQ(count, 2) << "equal_range() should find correct number of elements";
    EXPECT_EQ(*first, 3) << "equal_range() first iterator should point to correct element";
    
    auto [first_not_found, last_not_found] = c.equal_range(7);
    EXPECT_EQ(first_not_found, last_not_found) 
        << "equal_range() should return empty range for non-existing element";
}

// Тесты batch-операций
TEST_F(SortedVectorIntTest, InsertInitializerList) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1});
    
    EXPECT_EQ(c.size(), 4) << "insert(initializer_list) should add correct number of elements";
    EXPECT_TRUE(std::is_sorted(c.begin(), c.end())) 
        << "Elements should remain sorted after batch insert";
}

TEST_F(SortedVectorIntTest, InsertRange) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1});
    
    std::vector<int> v{9, 2, 7, 4};
    c.insert(v.begin(), v.end());
    
    EXPECT_EQ(c.size(), 8) << "insert(range) should add correct number of elements";
    EXPECT_TRUE(std::is_sorted(c.begin(), c.end())) 
        << "Elements should remain sorted after range insert";
    
    std::vector<int> expected{1, 2, 3, 4, 5, 7, 8, 9};
    EXPECT_TRUE(std::equal(c.begin(), c.end(), expected.begin())) 
        << "Container should have correct elements after batch operations";
}

// Тесты STL-совместимости
TEST_F(SortedVectorIntTest, STLDistance) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    size_t count = std::distance(c.begin(), c.end());
    EXPECT_EQ(count, c.size()) << "std::distance should work correctly with iterators";
}

TEST_F(SortedVectorIntTest, STLCopy) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    std::vector<int> v(c.size());
    std::copy(c.begin(), c.end(), v.begin());
    EXPECT_TRUE(std::equal(c.begin(), c.end(), v.begin())) 
        << "std::copy should work correctly";
}

TEST_F(SortedVectorIntTest, STLAccumulate) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    int sum = std::accumulate(c.begin(), c.end(), 0);
    EXPECT_EQ(sum, 28) << "std::accumulate should work correctly";
}

TEST_F(SortedVectorIntTest, STLFindIf) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    auto it = std::find_if(c.begin(), c.end(), [](int x) { return x > 5; });
    EXPECT_NE(it, c.end()) << "std::find_if should find element";
    EXPECT_EQ(*it, 8) << "std::find_if should return correct element";
}

TEST_F(SortedVectorIntTest, STLCountIf) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    int even_count = std::count_if(c.begin(), c.end(), [](int x) { return x % 2 == 0; });
    EXPECT_EQ(even_count, 2) << "std::count_if should work correctly";
}

TEST_F(SortedVectorIntTest, STLBinarySearch) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    bool found = std::binary_search(c.begin(), c.end(), 8);
    EXPECT_TRUE(found) << "std::binary_search should work for existing element";
    
    bool not_found = std::binary_search(c.begin(), c.end(), 7);
    EXPECT_FALSE(not_found) << "std::binary_search should work for non-existing element";
}

TEST_F(SortedVectorIntTest, STLTransform) {
    SortedVector<int> c;
    c.insert({5, 3, 8, 1, 9, 2});
    
    std::vector<int> squares(c.size());
    std::transform(c.begin(), c.end(), squares.begin(), [](int x) { return x * x; });
    EXPECT_EQ(squares[0], 1) << "std::transform should work correctly";
    EXPECT_EQ(squares[5], 81) << "std::transform should calculate squares correctly";
}

// Тесты capacity операций
TEST_F(SortedVectorIntTest, Reserve) {
    SortedVector<int> c;
    
    size_t initial_capacity = c.capacity();
    c.reserve(100);
    
    EXPECT_GE(c.capacity(), 100) << "reserve() should increase capacity";
    EXPECT_TRUE(c.empty()) << "Container should remain empty after reserve";
}

TEST_F(SortedVectorIntTest, ShrinkToFit) {
    SortedVector<int> c;
    c.reserve(100);
    
    for (int i = 0; i < 50; ++i) {
        c.insert(i);
    }
    
    EXPECT_EQ(c.size(), 50) << "Container should have correct size after insertions";
    EXPECT_GE(c.capacity(), 50) << "Capacity should be sufficient for elements";
    
    size_t before_shrink = c.capacity();
    c.shrink_to_fit();
    
    EXPECT_LE(c.capacity(), before_shrink) << "shrink_to_fit() should reduce or maintain capacity";
    EXPECT_GE(c.capacity(), c.size()) << "Capacity should remain sufficient after shrink_to_fit";
}

// Тест с пользовательским компаратором
TEST(SortedVectorCustomTest, CustomComparator) {
    SortedVector<int, std::greater<int>> desc;
    desc.insert({5, 3, 8, 1, 9, 2});
    
    std::vector<int> expected{9, 8, 5, 3, 2, 1};
    EXPECT_TRUE(std::equal(desc.begin(), desc.end(), expected.begin())) 
        << "Custom comparator should sort elements correctly";
    
    EXPECT_TRUE(desc.contains(5)) << "contains() should work with custom comparator";
    
    auto it = desc.find(3);
    EXPECT_NE(it, desc.end()) << "find() should work with custom comparator";
    EXPECT_EQ(*it, 3) << "find() should return correct element with custom comparator";
}

// Тест со строками
TEST(SortedVectorStringTest, StringType) {
    SortedVector<std::string> strings;
    strings.insert("roma");
    strings.insert("gosha");
    strings.insert("yura");
    
    std::vector<std::string> expected{"gosha", "roma", "yura"};  // Должно быть отсортировано лексикографически
    EXPECT_TRUE(std::equal(strings.begin(), strings.end(), expected.begin())) 
        << "Container should work with string type and sort strings correctly";
}

// Тест с парами
TEST(SortedVectorPairTest, PairType) {
    SortedVector<std::pair<int, std::string>> pairs;
    pairs.insert({3, "three"});
    pairs.insert({1, "one"});
    pairs.insert({2, "two"});
    
    EXPECT_EQ(pairs.front().first, 1) << "Container should work with pair type";
    EXPECT_EQ(pairs.back().first, 3) << "Container should maintain correct order with complex types";
}

// Main функция для запуска всех тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}