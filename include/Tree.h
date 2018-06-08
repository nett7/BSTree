#pragma once

#include <unistd.h>
#include <iostream>
#include <string>
#include <initializer_list>

namespace BSTree {

    struct Node {
        int data;
        Node *left;
        Node *right;

        Node(int val) : left(nullptr), right(nullptr) {
            data = val;
        }
    };

    void print_(int depth, Node *node);

    class Tree {

    private:

        Node *root;

        void clean(Node *&node);

        void direct_print(std::ostream &out, Node *node) const;

        void symmetric_print(std::ostream &out, Node *node) const;

        void reverse_print(std::ostream &out, Node *node) const;

        Node *find_parent(int &val);

    public:

        enum class order {
            direct, symmetric, reverse
        };

        void print_how(order order_ = order::direct, std::ostream &out = std::cout) const;

        Tree(std::initializer_list<int> list_);

        Tree() : root(nullptr) {};

        Tree(const Tree &tree);

        void print() {
            print_(0, root);
        }

        void swap(Tree &tree);

        Tree &operator=(Tree &tree);

        void insert(int val);

        bool save(const std::string &path);

        void load(const std::string &path);

        ~Tree() {
            clean(root);
        }

        void remove(int val);

        bool exist(int val);

        friend std::ostream &operator<<(std::ostream &stream, const Tree &);

    };
}


