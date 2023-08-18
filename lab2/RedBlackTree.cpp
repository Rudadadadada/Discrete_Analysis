#include <iostream>
#include <vector>
#include <fstream>


enum Color {
    BLACK,
    RED
};

struct RBTNode {
    std::string key;
    unsigned long long value{};
    RBTNode *parent{};
    RBTNode *left{};
    RBTNode *right{};
    Color color{};
};


class RBTree {
private:
    RBTNode *root;
    RBTNode *nilNode;

    RBTNode *searchNodeHelper(RBTNode *node, const std::string &key) {
        if (node == nilNode || key == node->key)
            return node;
        if (key < node->key)
            return searchNodeHelper(node->left, key);
        return searchNodeHelper(node->right, key);
    }

    void fixedDelete(RBTNode *node) {
        RBTNode *temp;
        while (node != root && node->color == Color::BLACK) {
            if (node == node->parent->left) {
                temp = node->parent->right;
                if (temp->color == Color::RED) {
                    temp->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    leftRotate(node->parent);
                    temp = node->parent->right;
                }
                if (temp == nullptr) {
                    node = node->parent;
                    node->color = Color::BLACK;
                    return;
                }
                if ((temp->left == nullptr || temp->left->color == Color::BLACK) &&
                    (temp->right == nullptr || temp->right->color == Color::BLACK)) {
                    temp->color = Color::RED;
                    node = node->parent;
                } else {
                    if (temp->right == nullptr || temp->right->color == Color::BLACK) {
                        temp->left->color = BLACK;
                        temp->color = Color::RED;
                        rightRotate(temp);
                        temp = node->parent->right;
                    }
                    temp->color = node->parent->color;
                    if (node->parent != nullptr)
                        node->parent->color = Color::BLACK;
                    if (temp->right != nullptr)
                        temp->right->color = Color::BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            } else {
                temp = node->parent->left;
                if (temp->color == Color::RED) {
                    temp->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    rightRotate(node->parent);
                    temp = node->parent->left;
                }
                if (temp == nullptr)
                    return;
                if (temp->right == nullptr || temp->right->color == Color::BLACK) {
                    temp->color = Color::RED;
                    node = node->parent;
                } else {
                    if (temp->left->color == Color::BLACK) {
                        temp->right->color = Color::BLACK;
                        temp->color = Color::RED;
                        leftRotate(temp);
                        temp = node->parent->left;
                    }
                    temp->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    temp->left->color = Color::BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = Color::BLACK;
    }


    void transplant(RBTNode *destNode, RBTNode *sourceNode) {
        if (destNode->parent == nullptr) {
            root = sourceNode;
        } else if (destNode == destNode->parent->left) {
            destNode->parent->left = sourceNode;
        } else {
            destNode->parent->right = sourceNode;
        }
        sourceNode->parent = destNode->parent;
    }

    void deleteNodeHelper(RBTNode *node, const std::string &key) {
        RBTNode *temp = nilNode;
        RBTNode *temp1, *temp2;
        while (node != nilNode) {
            if (node->key == key)
                temp = node;
            if (node->key <= key)
                node = node->right;
            else
                node = node->left;
        }

        if (temp == nilNode) {
            std::cout << "NoSuchWord" << std::endl;
            return;
        }
        std::cout << "OK" << std::endl;

        temp2 = temp;
        Color origColor = temp2->color;
        if (temp->left == nilNode) {
            temp1 = temp->right;
            transplant(temp, temp->right);
        } else if (temp->right == nilNode) {
            temp1 = temp->left;
            transplant(temp, temp->left);
        } else {
            temp2 = searchMinimum(temp->right);
            origColor = temp2->color;
            temp1 = temp2->right;
            if (temp2->parent == temp) {
                temp1->parent = temp2;
            } else {
                transplant(temp2, temp2->right);
                temp2->right = temp->right;
                temp2->right->parent = temp2;
            }
            transplant(temp, temp2);
            temp2->left = temp->left;
            temp2->left->parent = temp2;
            temp2->color = temp->color;
        }
        delete temp;
        if (origColor == Color::BLACK)
            fixedDelete(temp1);
    }

    void fixedInsert(RBTNode *node) {
        RBTNode *temp;
        while (node->parent->color == Color::RED) {
            if (node->parent == node->parent->parent->right) {
                temp = node->parent->parent->left;
                if (temp->color == Color::RED) {
                    temp->color = Color::BLACK;
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    leftRotate(node->parent->parent);
                }
            } else {
                temp = node->parent->parent->right;
                if (temp->color == Color::RED) {
                    temp->color = Color::BLACK;
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rightRotate(node->parent->parent);
                }
            }
            if (node == root) {
                break;
            }
        }
        root->color = Color::BLACK;
    }

    void saveNode(RBTNode *temp, std::ofstream &output) {
        char separator = ' ';
        if (temp == nilNode || temp == nullptr)
            return;
        for (auto keyValue: temp->key)
            output.write(reinterpret_cast<char *>(&keyValue), sizeof(char));
        output.write(&separator, sizeof(char));
        output.write(reinterpret_cast<char *>(&temp->value), sizeof(unsigned long long));
        output.flush();
        saveNode(temp->left, output);
        saveNode(temp->right, output);
    }

    void recursiveDeleter(RBTNode *temp) {
        if (temp == nullptr || temp == nilNode)
            return;
        recursiveDeleter(temp->left);
        recursiveDeleter(temp->right);
        delete temp;
    };

    RBTNode *searchMinimum(RBTNode *node) {
        while (node->left != nilNode)
            node = node->left;
        return node;
    }

    void leftRotate(RBTNode *node) {
        RBTNode *temp = node->right;
        if (temp == nilNode)
            return;
        node->right = temp->left;
        if (temp->left != nilNode)
            temp->left->parent = node;
        temp->parent = node->parent;
        if (node->parent == nullptr)
            this->root = temp;
        else if (node == node->parent->left)
            node->parent->left = temp;
        else
            node->parent->right = temp;
        temp->left = node;
        node->parent = temp;
    }

    void rightRotate(RBTNode *node) {
        RBTNode *temp = node->left;
        if (temp == nilNode)
            return;
        node->left = temp->right;
        if (temp->right != nilNode && temp->right != nullptr)
            temp->right->parent = node;
        temp->parent = node->parent;
        if (node->parent == nullptr)
            this->root = temp;
        else if (node == node->parent->right)
            node->parent->right = temp;
        else
            node->parent->left = temp;
        temp->right = node;
        node->parent = temp;
    }

public:
    RBTree() {
        nilNode = new RBTNode;
        nilNode->color = Color::BLACK;
        nilNode->left = nullptr;
        nilNode->right = nullptr;
        root = nilNode;
    }

    RBTNode *searchTree(const std::string &key) {
        return searchNodeHelper(this->root, key);
    }

    void insertNode(const std::string &key, const unsigned long long value) {
        auto *node = new RBTNode;
        node->parent = nullptr;
        node->key = key;
        node->value = value;
        node->left = nilNode;
        node->right = nilNode;
        node->color = Color::RED;
        RBTNode *temp = this->root;
        RBTNode *temp1 = nullptr;

        while (temp != nilNode) {
            temp1 = temp;
            if (node->key < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }

        node->parent = temp1;
        if (temp1 == nullptr)
            root = node;
        else if (node->key < temp1->key)
            temp1->left = node;
        else
            temp1->right = node;

        if (node->parent == nullptr) {
            node->color = Color::BLACK;
            return;
        }

        if (node->parent->parent == nullptr)
            return;
        fixedInsert(node);
    }

    void deleteNode(const std::string &key) {
        deleteNodeHelper(this->root, key);
    }

    bool loadTree(std::ifstream &input) {
        std::string key;
        char temp;

        if (input.read(reinterpret_cast<char *>(&temp), sizeof(char)) && temp != '@')
            return false;

        while (true) {
            key.clear();
            while (input.read(reinterpret_cast<char *>(&temp), sizeof(char)) && temp != ' ') {
                if (temp == '^')
                    return true;
                key += temp;
            }
            if (!input)
                return false;
            unsigned long long value;
            input.read(reinterpret_cast<char *>(&value), sizeof(unsigned long long));
            insertNode(key, value);
        }
    }

    void saveTree(std::ofstream &output) {
        char start = '@';
        char end = '^';
        output.write(reinterpret_cast<char *>(&start), sizeof(char));
        saveNode(root, output);
        output.write(reinterpret_cast<char *>(&end), sizeof(char));
    }

    void removeTree() {
        recursiveDeleter(root);
    };
};


void to_lower(std::string &sequence) {
    for (char &c: sequence)
        c = tolower(c);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::string> commands;
    std::string temp;

    RBTree dict{};

    while (std::cin >> temp) {
        to_lower(temp);
        commands.clear();
        commands.push_back(temp);

        if (commands[0] == "+") {
            std::cin >> temp;
            to_lower(temp);
            commands.push_back(temp);

            std::cin >> temp;
            to_lower(temp);
            commands.push_back(temp);

            if (!dict.searchTree(commands[1])->key.empty())
                std::cout << "Exist" << std::endl;
            else {
                dict.insertNode(commands[1], std::stoull(commands[2]));
                std::cout << "OK" << std::endl;
            }
        } else if (commands[0] == "-") {
            std::cin >> temp;
            to_lower(temp);
            commands.push_back(temp);

            dict.deleteNode(commands[1]);
        } else if (commands[0] == "!") {
            std::cin >> temp;
            to_lower(temp);
            commands.push_back(temp);

            std::cin >> temp;
            to_lower(temp);
            commands.push_back(temp);
            if (commands[1] == "save") {
                std::ofstream output(commands[2], std::ios::trunc | std::ios::binary);
                dict.saveTree(output);
                std::cout << "OK" << std::endl;
                output.close();
            } else if (commands[1] == "load") {
                std::ifstream input(commands[2], std::ios::binary);
                auto *newDict = new RBTree;
                newDict->loadTree(input);
                dict.removeTree();
                dict = *newDict;
                std::cout << "OK" << std::endl;
                input.close();
            } else {
                auto res = dict.searchTree(commands[0]);
                if (!res->key.empty())
                    std::cout << "OK: " << res->value << std::endl;
                else
                    std::cout << "NoSuchWord" << std::endl;
            }
        } else {
            auto res = dict.searchTree(commands[0]);
            if (!res->key.empty())
                std::cout << "OK: " << res->value << std::endl;
            else
                std::cout << "NoSuchWord" << std::endl;
        }
    }
}