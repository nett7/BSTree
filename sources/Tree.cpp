//
// Created by netta on 25.05.18.
//

#include "Tree.h"

#include <sstream>
#include <fstream>
#include <iostream>

using std::cout;
using std::ostream;
using std::endl;
using std::logic_error;
using std::string;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::stringstream;

void BSTree:: print_(int depth, BSTree::Node *node) {

    if (node == nullptr) {
        if (depth == 0)
            cout << "Дерево пусто" << endl;
        return;
    } else {
        BSTree::print_(depth + 1, node->right);
        for (int i = 0; i < depth; i++) {
            cout << "   ";
            if (i == depth - 1) cout << "--";
        }
        cout << node->data << endl;
        BSTree::print_(depth + 1, node->left);


    }
};


void BSTree::Tree::clean(Node *&node) {
    {
        if (node != nullptr) {
            clean(node->left);
            clean(node->right);
            delete node;
            node = nullptr;
        }
    }

}

void BSTree::Tree::direct_print(ostream &out, Node *node) const {

    if (node == nullptr)
        return ;
    out << node->data << ' ';
    direct_print(out, node->left);
    direct_print(out, node->right);

}

void BSTree::Tree::symmetric_print(ostream &out, Node *node) const {
    if (node == nullptr)
        return;
    symmetric_print(out, node->left);
    out << node->data << ' ';
    symmetric_print(out, node->right);

}

void BSTree::Tree::reverse_print(ostream &out, Node *node) const {

    if (node == nullptr)
        return;
    reverse_print(out, node->left);
    reverse_print(out, node->right);
    out << node->data << ' ';

}

BSTree::Node *BSTree::Tree::find_parent(int &val) {

    if (root == nullptr)
        return root;
    Node *node = root;
    while (node != nullptr) {
        if (val < node->data)
            if (node->left != nullptr && node->left->data == val)
                return node;
            else {
                node = node->left;
            }
        else if (node->right != nullptr && node->right->data == val)
            return node;
        else {
            node = node->right;
        }
    }
    return node;
}

void BSTree::Tree::print_how( Tree::order order1,ostream &out) const {
    if (root == nullptr) {
        cout << "Дерево пусто\n";
        return ;
    }
    switch (order1) {
        case order::direct :
            break;
        case order::symmetric :
            symmetric_print(out, root);
            break;
        case order::reverse :
            reverse_print(out, root);

    }

}

BSTree::Tree::Tree(std::initializer_list<int> list_) {
    root = nullptr;
    for (auto &item : list_)
        this->insert(item);
}


bool BSTree::Tree::insert(int val) {
    if (root == nullptr) {
        root = new Node(val);
        return true;
    } else {
        Node *temp = root;
        Node *node = new Node(val);
        while (true) {
            if (val < temp->data) {
                if (temp->left != nullptr)
                    temp = temp->left;
                else {
                    temp->left = node;
                    return true;
                }
            } else if (val == temp->data) {
                throw logic_error("Узел уже существует в дереве");

            } else {
                if (temp->right != nullptr)
                    temp = temp->right;
                else {
                    temp->right = node;
                    return true;
                }
            }
        }
    }
}

bool BSTree::Tree::save(const string &path) {
    if (!(access(path.c_str(), 0)))//проверяет существование файла
    {
        string answer;
        cout << " Файл уже существует. Перезаписать файл? (Да|Нет)" << endl;
        cin >> answer;
        if (answer == "Да") {
            ofstream fout(path.c_str());
            direct_print(fout, root);
            return true;
        } else
            return false;
    } else//файл не существует
    {
        ofstream fout(path.c_str());
        direct_print(fout, root);
        return true;
    }
}

bool BSTree::Tree::load(const string &path) {
    if ((access(path.c_str(), 0))) {
        throw logic_error("Файл с заданным путем не существует");
    }
    ifstream fin(path.c_str());
    int value;
    fin >> value;
    this->clean(root);
    while (fin) {
        this->insert(value);
        fin >> value;
    }
    fin.close();
    cout << "Дерево было успешно загружено\n";
    return true;
}

bool BSTree::Tree::remove(int val) {
    Node *parent = find_parent(val);

    if (parent == nullptr && root->data != val) {
        cout << "Узел не был найден в дереве\n";
        return true;
    } else {

        Node *node_to_delete;
        if (root->data == val)
            node_to_delete = root;
        else {
            if (val > parent->data)
                node_to_delete = parent->right;
            else {
                node_to_delete = parent->left;
            }
        }
        if (node_to_delete->left == nullptr) {
            if (val > parent->data)
                parent->right = node_to_delete->right;
            else {
                parent->left = node_to_delete->right;
            }
            delete node_to_delete;
            cout << "Узел был успешно удален из дерева\n";
            return true;
        } else if (node_to_delete->right == nullptr) {
            if (val > parent->data)
                parent->right = node_to_delete->left;
            else {
                parent->left = node_to_delete->left;
            }
            delete node_to_delete;
            cout << "Узел был успешно удален из дерева\n";
            return true;
        }
        // Здесь у удаляемого узла имеются два потомка
        // ищем ближайший по значению к удаляемому, при этом меньший его
        // это prodecessor, меняем со значением node_to_delete и удаляем

        Node *pp = node_to_delete->left;
        if (pp->right != nullptr) {//проверка на наличие правого потомка
            while (pp->right->right != nullptr)
                pp = pp->right;

            node_to_delete->data = pp->data;
            Node *prodecessor = nullptr;
            if (pp->right != nullptr)
                prodecessor = pp->right;
            else { prodecessor = pp; }
            if (pp == node_to_delete)// случай, когда родитель prodecessor является подлежащим удалению элементом
                pp->left = prodecessor->left;
            else if (prodecessor->left !=
                     nullptr)// когда у prodecessor есть левый потомок, которого не должны потерять
            {
                pp->right = prodecessor->left;
            } else {
                //левого потомка нет, просто обнуляем значение
                pp->right = nullptr;
            }

            delete prodecessor;//освобождаем память
        } else {
            node_to_delete->data = pp->data;
            node_to_delete->left = pp->left;
            delete pp;
        }

        cout << "Узел был успешно удален из дерева\n";
        return true;
    }

}

bool BSTree::Tree::exist(int val) {
    if (find_parent(val) != nullptr) {
        cout << "Узел найден\n";
        return true;
    } else cout << "Узел не найден\n";
    return false;
}

void BSTree::Tree::swap(BSTree::Tree &tree) {
    std::swap(root, tree.root);
}

BSTree::Tree & BSTree::Tree::operator=(BSTree::Tree &tree) {
    this->clean(root);
    Tree tmp{ tree };
    this->swap(tmp);
    return *this;
}

ostream & operator<<(ostream &stream, const BSTree::Tree &tree) {
    tree.print_how(BSTree::Tree::order::direct, stream);
    return stream;

}

BSTree::Tree::Tree(const BSTree::Tree &tree) {
// это не хочет работать, и мешает работе всей программы
    /*    string str;
    stringstream out(str);
    out << tree;
    int value;
    while (out >> value) {
        this->insert(value);
    }*/
}





