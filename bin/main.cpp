#include "../lib/sorted_vector.hpp"
#include <iostream>
#include <algorithm>
#include <string>

int main() {
    SortedVector<int> numbers;
    
    // Вставка элементов (они автоматически сортируются)
    numbers.insert(5);
    numbers.insert(1);
    numbers.insert(10);
    numbers.insert(3);
    numbers.insert(7);
    
    // Вывод содержимого: 1 3 5 7 10
    std::cout << "Sorted numbers: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Contains 5: " << (numbers.contains(5) ? "Yes" : "No") << std::endl;
    std::cout << "Contains 6: " << (numbers.contains(6) ? "Yes" : "No") << std::endl;
    
    auto it = numbers.find(7);
    if (it != numbers.end()) {
        std::cout << "Found 7 at position: " << (it - numbers.begin()) << std::endl;
    }
    
    // Вставка дубликатов
    numbers.insert(3);
    numbers.insert(3);
    
    // Поиск диапазона всех троек
    auto [first, last] = numbers.equal_range(3);
    std::cout << "Number of 3's: " << (last - first) << std::endl;
    
    // Использование с компаратором для сортировки в обратном порядке
    SortedVector<int, std::greater<int>> reversed;
    reversed.insert({1, 5, 3, 10, 7});
    
    std::cout << "Reversed order: ";
    for (int num : reversed) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    bool is_sorted = std::is_sorted(numbers.begin(), numbers.end());
    std::cout << "Is sorted: " << (is_sorted ? "Yes" : "No") << std::endl;
    
    auto sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "Sum: " << sum << std::endl;
    
    return 0;
}