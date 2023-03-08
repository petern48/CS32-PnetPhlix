#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <list>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
public:
    class Iterator
    {
    public:
        Iterator()
        {
            m_node = nullptr; // Invalid iterator
        }
        // New Constructor
        Iterator(TreeMultimap<KeyType, ValueType>& t) {
            m_node = t.m_root;
        }

        Iterator(TreeNode *node) {
            m_node = node;
        }

        ValueType& get_value() const
        {
            if (isvalid())
                return m_node->values; // TODO returning a list
            throw 1;  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            if (m_node != nullptr)
                return true;
            return false;
        }

        // In order traversal
        void advance()
        {
            // Recall: iterators starts at the node furthest to the left
            

            // Advance to right child then iterate all the way to the left
            if (m_node->right != nullptr) {
                m_node = m_node->right;
                while (m_node->left != nullptr)
                    m_node = m_node->left;
            }
            // No right child
            else {
                // Note: If parent is root node, m_node will be set to nullptr

                // If this node is the left child
                if (m_node->parent->left == m_node)
                    m_node = m_node->parent;

                // If node is the right child of parent
                else {
                    // While current node is the right child
                    while (m_node->parent != nullptr && m_node->parent->right == m_node)
                        m_node = m_node->parent;
                    // Go up (to the right) one more time once we're the left child
                    m_node = m_node->parent;
                }
            }
        }

    private:
        TreeNode* m_node;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        deleteAll(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
            m_root = new TreeNode(key, value, nullptr); // Parent ptr is null
        
        TreeNode* curr = m_root;
        while (true) {
            // If found a TreeNode with the key already
            if (key == curr->keyVal) {
                std::list<ValueType>::iterator it = curr->values.begin();
                while (it != curr->values.end()) {
                    // Key already maps to the value
                    if (value == *it)
                        return;
                    // If value should go right before this
                    else if (value < *it) {
                        // Add value right before here
                        curr->values.insert(it, value); // UNSURE
                    }

                    // Value should go after this
                    else if (value > *it) {
                        // Add value to end of list
                        if (it == curr->values.end())
                            curr->values.push_back(*it);
                        // Iterate to next element
                        else
                            it++;
                    }
                }
            }
            // TreeNode for key doesn't exist yet
            else if (key < curr->keyVal) {
                // Create new TreeNode as left child
                if (curr->left == nullptr) {
                    curr->left = new TreeNode(key, value, curr);
                    return;
                }
                // Iterate to left TreeNode
                else
                    curr = curr->left;
            }
            // key > curr->keyVal
            else {
                if (curr->right == nulltr) {
                    curr->right = new TreeNode(key, value, curr);
                    return;
                }
                else
                    curr = curr->right;
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        TreeNode* n = binarySearch(m_root, key);
        return Iterator(n);
    }
    
private:
    struct TreeNode {
        TreeNode(KeyType key, ValueType value, TreeNode* parent) {
            keyVal = key;
            values.push_back(value);
            left = nullptr;
            right = nullptr;
            parent = parent;
        }
        KeyType keyVal;
        std::list<ValueType> values;
        TreeNode *left, *right, *parent;
    };
    TreeNode* m_root;

    void deleteAll(TreeNode* curr) {
        // In order Traversal
        if (curr == nullptr)
            return;
        deleteAll(curr->left);
        if (curr != nullptr)
            delete curr;
        deleteAll(curr->right);
    }

    TreeNode* binarySearch(TreeNode* curr, const KeyType& key) {
        if (curr == nullptr)
            return nullptr;
        else if (curr->keyVal == key)
            return curr;
        else if (curr->keyVal < key)
            return search(curr->left);
        else // curr->keyVal > key
            return search(curr->right);
    }
};

#endif // TREEMULTIMAP_INCLUDED
