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


template<typename T>
class Array {
private:
    T* data; // вказівник на масив даних
    int size; // розмір масиву

public:
    // Конструктори
    Array() {
        data = nullptr;
        size = 0;
    }

    explicit Array(int s) {
        data = new T[s];
        size = s;
    }

    Array(const Array& other) {
        data = new T[other.size];
        size = other.size;
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Оператор []
    T& operator[](int index) {
        return data[index];
    }

    // Оператор =
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            data = new T[other.size];
            size = other.size;
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Оператор +
    Array operator+(const Array& other) const {
        Array result(size + other.size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i];
        }
        for (int i = 0; i < other.size; ++i) {
            result.data[size + i] = other.data[i];
        }
        return result;
    }

    // Оператор +=
    Array& operator+=(const Array& other) {
        Array temp = *this + other;
        *this = temp;
        return *this;
    }

    // Оператор -
    Array operator-(const Array& other) const {
        Array result(size);
        for (int i = 0; i < size; ++i) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    // Оператор -=
    Array& operator-=(const Array& other) {
        Array temp = *this - other;
        *this = temp;
        return *this;
    }
};


class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int data) {
        Node* newNode = new Node(data);

        if (root == nullptr) {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true) {
            if (data < current->data) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    return;
                }
                current = current->left;
            }
            else {
                if (current->right == nullptr) {
                    current->right = newNode;
                    return;
                }
                current = current->right;
            }
        }
    }

    // Ітератор для обходу дерева в прямому порядку
    class Iterator {
    private:
        Node* current;
    public:
        Iterator(Node* root) {
            current = root;
            while (current->left != nullptr) {
                current = current->left;
            }
        }

        bool hasNext() {
            return current != nullptr;
        }

        int next() {
            int data = current->data;

            if (current->right != nullptr) {
                current = current->right;
                while (current->left != nullptr) {
                    current = current->left;
                }
            }
            else {
                Node* temp = current;
                current = current->left;

                while (current != nullptr && current->right == temp) {
                    temp = current;
                    current = current->left;
                }
            }

            return data;
        }
    };

    Iterator iterator() {
        return Iterator(root);
    }
};


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


    int x;
    std::cout << "Enter the size of the array: ";
    std::cin >> x;

    Array<int> arrr(x);

    for (int i = 0; i < x; ++i) {
        int q;
        std::cout << "Enter element " << i << ": ";
        std::cin >> q;
        arrr[i] = q;
    }


    BinaryTree tree;

    // Введення даних з клавіатури
    int n, x;
    std::cout << "Введіть кількість елементів: ";
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cout << "Введіть елемент: ";
        std::cin >> x;
        tree.insert(x);
    }

    // Обхід дерева в прямому порядку за допомогою ітератора
    std::cout << "Обхід дерева в прямому порядку: ";
    BinaryTree::Iterator it = tree.iterator();
    while (it.hasNext()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    // Обхід дерева в прямому порядку за допомогою ітератора
    std::cout << "Обхід дерева в прямому порядку: ";
    it = tree.iterator();
    while (it.hasNext()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    // Введення даних за допомогою датчика випадкових чисел
    srand(time(nullptr));
    for (int i = 0; i < 10; i++) {
        tree.insert(rand() % 100);
    }

    // Обхід дерева в прямому порядку за допомогою ітератора
    std::cout << "Обхід дерева в прямому порядку: ";
    it = tree.iterator();
    while (it.hasNext()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    return 0;
}