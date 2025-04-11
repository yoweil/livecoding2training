# SortedVector - STL-совместимый упорядоченный контейнер

### Описание
Разработайте шаблонный класс `SortedVector<T>` - STL-совместимый контейнер, который хранит элементы в отсортированном порядке. Контейнер должен автоматически поддерживать элементы в отсортированном состоянии при вставке и обеспечивать эффективный поиск элементов.

### Требования

#### Базовые требования (для всех)
1. Шаблонный класс `SortedVector<T, Compare = std::less<T>, Allocator = std::allocator<T>>`
2. STL-совместимые типы:
   - `value_type`, `reference`, `const_reference`, `iterator`, `const_iterator`, `size_type`, `difference_type`
3. Основные конструкторы:
   - Конструктор по умолчанию
   - Конструктор с компаратором
   - Конструктор копирования и перемещения
4. Итераторы:
   - `begin()`/`end()`, `cbegin()`/`cend()`
   - Итераторы должны поддерживать категорию random access
5. Доступ к элементам:
   - `front()`, `back()`
   - `operator[]` и `at()`
6. Модификаторы:
   - `insert(const T& value)` - вставка с поддержанием сортировки
   - `erase(iterator pos)` - удаление элемента
   - `clear()` - очистка контейнера
7. Размер и ёмкость:
   - `empty()`, `size()`, `capacity()`, `reserve()`

1. Эффективный поиск:
   - `bool contains(const T& value) const` - проверка наличия значения
   - `iterator find(const T& value)` - поиск элемента (за O(log n))
   - `std::pair<iterator, iterator> equal_range(const T& value)` - поиск диапазона равных элементов
2. Batch-операции:
   - `void insert(InputIt first, InputIt last)` - вставка диапазона элементов
   - `void insert(std::initializer_list<T> ilist)` - вставка списка инициализации
3. Метод `shrink_to_fit()` для оптимизации использования памяти
4. Совместимость с алгоритмами поиска в отсортированном диапазоне