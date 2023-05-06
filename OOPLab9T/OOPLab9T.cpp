#include <iostream>
#include <cstring>

template<typename T>
int sequentialSearch(T arr[], int size, T key) {
    int lastIndex = -1;  // індекс останнього знайденого елемента, за замовчуванням -1

    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {  // якщо елемент знайдено
            lastIndex = i;    // оновити індекс останнього знайденого елемента
        }
    }

    return lastIndex;
}

// Спеціалізація для типу char*
template<>
int sequentialSearch(char* arr[], int size, char* key) {
    int lastIndex = -1;

    for (int i = 0; i < size; i++) {
        if (std::strcmp(arr[i], key) == 0) {  // порівняти два рядки за допомогою std::strcmp()
            lastIndex = i;
        }
    }

    return lastIndex;
}

int main() {
    int intArr[] = {1, 2, 3, 4, 5};
    int intKey = 3;
    std::cout << "Index of last occurrence of " << intKey << " in intArr: "
              << sequentialSearch(intArr, 5, intKey) << std::endl;

    double doubleArr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double doubleKey = 2.2;
    std::cout << "Index of last occurrence of " << doubleKey << " in doubleArr: "
              << sequentialSearch(doubleArr, 5, doubleKey) << std::endl;

    char* strArr[] = {"apple", "banana", "orange", "grape", "apple"};
    char* strKey = "apple";
    std::cout << "Index of last occurrence of \"" << strKey << "\" in strArr: "
              << sequentialSearch(strArr, 5, strKey) << std::endl;

    return 0;
}