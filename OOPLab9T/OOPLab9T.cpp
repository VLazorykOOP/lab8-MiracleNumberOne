#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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


// шаблон функції для впорядкування методом швидкого впорядкування
template<typename T>
void quickSort(T* arr, int left, int right) {
    int i = left, j = right;
    T tmp;
    T pivot = arr[(left + right) / 2];

    /* розділення */
    while (i <= j) {
        while (std::strcmp(arr[i], pivot) < 0)
            i++;
        while (std::strcmp(arr[j], pivot) > 0)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* рекурсивний виклик */
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
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

    
    // введення даних з клавіатури
    std::cout << "Enter the number of elements: ";
    int n;
    std::cin >> n;
    char** arr = new char*[n];
    std::cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        arr[i] = new char[100];
        std::cin >> arr[i];
    }

    // виведення несортованого масиву
    std::cout << "Unsorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // виклик функції quickSort
    quickSort(arr, 0, n - 1);

    // виведення впорядкованого масиву
    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // випадкові дані
    srand(time(NULL));
    int size = 10;
    char** arr_random = new char*[size];
    for (int i = 0; i < size; i++) {
        arr_random[i] = new char[100];
        for (int j = 0; j < 10; j++) {
            arr_random[i][j] = (rand() % 26) + 'a';
        }
        arr_random[i][10] = '\0';
    }

    // виведення несортованого масиву
    std::cout << "Unsorted random array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr_random[i] << " ";
    }
    std::cout << std::endl;

    // виклик функції quickSort
    quickSort(arr_random, 0, size - 1);

    // виведення впорядкованого масиву
    std::cout << "Sorted random array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr_random[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}