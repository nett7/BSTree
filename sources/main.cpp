#include <iostream>
#include "Tree.h"

using namespace BSTree;
using namespace std;

int main() {

    size_t operation;
    char met;
    int value;
    string answer;
    string path;
    Tree tree;
    setlocale(LC_ALL, "Russian");
    cout<<"Работа с деревом\n\n";

    while (true) {
        cout << "Выберите одну из операций:\n"
             << "1. Вывести дерево на экран\n"
             << "2. Вывести список узлов дерева \n"
             << "3. Добавить узел в дерево\n"
             << "4. Удалить узел из дерева\n"
             << "5. Сохранить дерево в файл\n"
             << "6. Загрузить дерево из файла\n"
             << "7. Проверить наличие узла\n"
             << "8. Завершить работу программы\n";

        cin >> operation;
        switch (operation) {
            case 1 :
                tree.print();
                break;
            case 2:{
                cout << "Выберете метод обхода\n";
                cout << "a. Прямой обход\n"
                     << "b. Поперечный обход\n"
                     << "c. Обратный обход\n";
                bool key = false;
                while (!key) {
                    cin >> met;
                    switch (met) {
                        case 'a':
                            tree.print_how(Tree::order::direct);
                            key = true;
                            break;
                        case 'b' :
                            tree.print_how(BSTree::Tree::order::reverse);
                            key = true;
                            break;
                        case 'c' :
                            tree.print_how(BSTree::Tree::order::symmetric);
                            key = true;
                            break;
                             default:
                                 cout << "Вы ввели неправильный метод, попробуйте еще\n";
                                 break;
                    }
                }
            }
                break;
            case 3: cout<<"Введите значение для нового узла:\n";
            cin>>value;
                try {

                tree.insert(value);
                }
                catch (logic_error err){
                   cout<< err.what()<<endl;
                }
                break;
            case 4: cout<<"Введите значение узла для удаления:\n";
                cin>>value;
                tree.remove(value);
                break;
            case 5: cout<<"Введите путь к файлу:\n";
            cin>>path;
            tree.save(path);
                break;
            case 6: cout<<"Введите путь к файлу:\n";
                cin>>path;
                try {
                tree.load(path);
                }
                catch (logic_error err){
                    cout<<err.what()<<endl;
                }
                break;

            case 7: cout<<"Введите значение для поиска:\n";
            cin>>value;
                tree.exist(value);
                break;

            case 8:
                cout << "Вы уверены, что хотите выйти из программы ? (Да|Нет)\n";
                while (true) {
                    cin >> answer;
                    if ((answer == "Да") || (answer == "Нет"))
                        break;
                    else {
                        cout << "Неправильный ввод ответа, попробуйте еще\n";
                    }
                }
                break;

                }
        if (answer == "Да")
            break;
        }


    return 0;
}