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
            // Replace this line with correct code.
            m_curr = m_root;
            m_prev = nullptr;
        }
        // Added new constructor
        Iterator(TreeMultimap<KeyType,ValueType>,& )

        ValueType& get_value() const
        {
            throw 1;  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            return false;  // Replace this line with correct code.
        }

        void advance()
        {
            // Replace this line with correct code.
        }

    private:
        Node* m_curr;
        Node* m_prev;

        // In order traversal

    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
            m_root = new TreeNode(key, value); // Constructs node with left and right values nullptr
        
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
            else if (key < curr->keyVal) {
                // Iterate to left TreeNode
                if (curr->left != nullptr)
                    curr = curr->left;
                // Create new TreeNode
                else {
                    curr = new TreeNode(key, value);
                    return;
                }
            }
            // key > curr->keyVal
            else {
                if (curr->right != nullptr)
                    curr = curr->right;
                else {
                    curr = new TreeNode(key, value);
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        return Iterator();  // Replace this line with correct code.
    }
    
private:
    struct TreeNode {
        TreeNode(KeyType key, ValueType value) {
            keyVal = key;
            values.push_back(value);
            left = nullptr;
            right = nullptr;
        }
        KeyType keyVal;
        std::list<ValueType> values;
        TreeNode* left;
        TreeNode* right;
      };
    TreeNode* m_root;
};

#endif // TREEMULTIMAP_INCLUDED
