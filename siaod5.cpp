#include <iostream>
using namespace std;

// Структура для узла дерева
struct Node {
    string key;
    Node* left;
    Node* right;
    Node(string k) : key(k), left(NULL), right(NULL) {}
};

// Вставка элемента в дерево
Node* insert(Node* root, string key) {
    if (root == NULL) {
        return new Node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root;
}

// Обратный обход дерева
void postorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->key << " ";
}

// Симметричный обход дерева
void inorderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    cout << root->key << " ";
    inorderTraversal(root->right);
}

// Найти длину пути от корня до заданного значения
int findPathLength(Node* root, string key) {
    if (root == NULL) {
        return 0; // Не нашли элемент
    }

    if (key < root->key) {
        return 1 + findPathLength(root->left, key);
    } else if (key > root->key) {
        return 1 + findPathLength(root->right, key);
    }

    return 1; // Нашли элемент
}

// Найти высоту дерева
int findTreeHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = findTreeHeight(root->left);
    int rightHeight = findTreeHeight(root->right);

    return 1 + max(leftHeight, rightHeight);
}

// Удаление дерева (освобождение памяти)
void deleteTree(Node* root) {
    if (root == NULL) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void printTree(Node* root, string prefix, bool isLeft) {
    if (root == NULL) {
        return;
    }

    cout << prefix;
    cout << (isLeft ? "├── " : "└── ");
    cout << root->key << endl;

    if (root->left || root->right) {
        if (root->left) {
            printTree(root->left, prefix + (isLeft ? "│   " : "    "), true);
        }
        if (root->right) {
            printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);
        }
    }
}

// Основная функция
int main() {
    system("chcp 65001");
    Node* root = NULL;
    int n;

    cout << "Введите количество элементов в дереве: ";
    cin >> n;

    cout << "Введите элементы дерева:" << endl;
    for (int i = 0; i < n; i++) {
        string key;
        cin >> key;
        root = insert(root, key);
    }

    int choice;
    do {
        cout << "Меню:" << endl;
        cout << "1. Вставить элемент" << endl;
        cout << "2. Обратный обход" << endl;
        cout << "3. Симметричный обход" << endl;
        cout << "4. Найти длину пути до элемента" << endl;
        cout << "5. Найти высоту дерева" << endl;
        cout << "6. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Введите элемент для вставки: ";
                string key;
                cin >> key;
                root = insert(root, key);
                break;
            }
            case 2: {
                cout << "Обратный обход: ";
                postorderTraversal(root);
                cout << endl;
                break;
            }
            case 3:{
                cout << "Симметричный обход: ";
                inorderTraversal(root);
                cout << endl;
                break;
            }

            case 4:{
                string key;
                cout << "Введите элемент для поиска пути: ";
                cin >> key;
                int length = findPathLength(root, key);
                cout << "Длина пути: " << length - 1 << endl;
                break;
            }

            case 5:{
                int height = findTreeHeight(root);
                cout << "Высота дерева: " << height << endl;
                break;
            }

            case 6:{
                deleteTree(root);
                cout << "Дерево удалено. Выход." << endl;
                break;
            }
            case 7:{
                cout << "Структура дерева:" << endl;
                printTree(root, "", true);

                break;
            }

            default:{
                cout << "Некорректный выбор. Повторите попытку." << endl;
            }
        }
    } while (choice != 6);

    return 0;
}
