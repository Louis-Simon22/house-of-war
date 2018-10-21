#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <memory>

using namespace std;

// TODO _datatype on heap?
template<class _datatype, class _compare>
class binary_tree
{
    private:
        struct internal_node
        {
            weak_ptr<internal_node> parent;
            shared_ptr<internal_node> left;
            shared_ptr<internal_node> right;
            _datatype value;

            internal_node(shared_ptr<internal_node> parent, _datatype value) : value(value) {
                this->parent = weak_ptr<internal_node>(parent);
                this->left = shared_ptr<internal_node>(nullptr);
                this->right = shared_ptr<internal_node>(nullptr);
            }
            internal_node(_datatype value) : value(value) {
                this->parent = weak_ptr<internal_node>();
                this->left = shared_ptr<internal_node>(nullptr);
                this->right = shared_ptr<internal_node>(nullptr);
            }
        };
        shared_ptr<internal_node> root;
        _compare cmp;
        void tryInsert(shared_ptr<internal_node> node, const _datatype value) {
            if (this->cmp(value, node->value)) {
                if (node->left) {
                    this->tryInsert(node->left, value);
                } else {
                    node->left = shared_ptr<internal_node>(new internal_node(node, value));
                }
            } else {
                if (node->right) {
                    this->tryInsert(node->right, value);
                } else {
                    node->right = shared_ptr<internal_node>(new internal_node(node, value));
                }
            }
        }

    public:
        binary_tree(_compare& cmp) : cmp(cmp){
            this->root = shared_ptr<internal_node>(nullptr);
        }

        void add(_datatype value){
            if (this->root)
            {
                this->tryInsert(this->root, value);
            }
            else
            {
                this->root = make_shared<internal_node>(value);
            }
        }

        class node {
            public:
                node* left() const
                {
                    return this->currentNode->left ? new node(this->currentNode->left.get()) : nullptr;
                }
                node* right() const
                {
                    return this->currentNode->right ? new node(this->currentNode->right.get()) : nullptr;
                }
                node* parent() const
                {
                    return this->currentNode->parent ? new node(this->currentNode->parent->lock().get()) : nullptr;
                }
                _datatype value() const
                {
                    return this->currentNode->value;
                }
            private:
                node(internal_node* internalNode) : currentNode(internalNode) {}
                internal_node* currentNode;
        };
};

#endif // BINARY_TREE_H
