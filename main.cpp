#include <iostream>
#include "tree.hpp"

using namespace std;

string inputData;

void creteListNodes(TreeNode *&root) {
    int i;
    getline(cin, inputData);
    TreeNode *pointer;

    root = NULL;

    for (i = 0; i < inputData.length(); i++) {
        pointer = root;

        while (pointer && pointer->value != inputData[i]) {
            pointer = pointer->next;
        }

        if (pointer) {
            pointer->count += 1;
        } else {
            pointer = new TreeNode;
            pointer->next = root;
            pointer->left = NULL;
            pointer->right = NULL;
            pointer->value = inputData[i];
            pointer->count = 0;

            root = pointer;
        }
    }

    //sortowanie
    int c;
    char v;
    bool end;

    do {
        end = true;
        pointer = root;

        while (pointer->next) {
            if (pointer->count > pointer->next->count) {
                c = pointer->count;
                v = pointer->value;

                pointer->count = pointer->next->count;
                pointer->value = pointer->next->value;

                pointer->next->value = v;
                pointer->next->count = c;

                end = false;
            }
            pointer = pointer->next;
        }
    } while (!end);


    cout << "Utworzona lista: " << endl;
    pointer = root;
    while (pointer) {
        cout << pointer->value << ":" << pointer->count << " | ";
        pointer = pointer->next;
    }

    cout << endl;
}

void createTree(TreeNode *&root) {
    TreeNode *pointer;
    TreeNode *helperRoot;
    TreeNode *node1;
    TreeNode *node2;

    while (true) {

        node1 = root;
        node2 = node1->next;

        if (!node2) break;

        root = node2->next; //lista bez dwoch pierwszych wezlow

        pointer = new TreeNode;
        pointer->left = node1;
        pointer->right = node2;
        pointer->count = node1->count + node2->count;

        if (!root || (pointer->count <= root->count)) {
            pointer->next = root;
            root = pointer;
            continue;
        }

        helperRoot = root;


        while (helperRoot->next && pointer->count > helperRoot->count) {
            helperRoot = helperRoot->next;
        }

        pointer->next = helperRoot->next;
        root->next = pointer;
    }
}

bool code(char c, TreeNode *&root, string bit) {

    if (!root->left) {
        if (c != root->value) return false;
        else {
            cout << bit;
        }
    } else {
        return code(c, root->left, bit + "0") || code(c, root->right, bit + "1");
    }
}

void huffman(TreeNode *root) {
    unsigned int i;
    for (i = 0; i < inputData.length(); i++) {
        code(inputData[i], root, "");
    }
}

void encodeHuffman(TreeNode *root) {
    TreeNode *pointer;
    string bits;
    cout << "Podaj ciąg bitów do rozpakowania" << endl;
    cin >> bits;
    unsigned int i;
    for (i = 0; i < bits.length(); i++) {
        pointer = root;
        while (pointer->left || pointer->right) {
            if (bits[i] == '0') pointer = pointer->left;
            if (bits[i] == '1') pointer = pointer->right;
        }
        cout << pointer->value << " ";
    }

    cout << endl;
}

int main() {
    TreeNode *root;
    cout << "Podaj ciag znakow do kompresacji" << endl;
    creteListNodes(root);
    createTree(root);
    cout << "Skompresowany tekst:" << endl;
    huffman(root);
    cout << endl;
    encodeHuffman(root);
    return 0;
}