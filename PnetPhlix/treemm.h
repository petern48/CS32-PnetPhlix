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
        if (m_root == nullptr) {
            m_root = new TreeNode; // Constructs node with left and right values nullptr
            m_root->m_keyVal = key;
            m_root->values.push_back(value);
        }
        
        Node* cur = m_root;
        while (true) {
            


        }
    }

    Iterator find(const KeyType& key) const
    {
        return Iterator();  // Replace this line with correct code.
    }
    
private:
    struct TreeNode {
        TreeNode() { left = nullptr; right = nullptr; }
        KeyType keyVal;
        std::list<ValueType> values;
        Node* left;
        Node* right;
      };
    Node* m_root;
};

#endif // TREEMULTIMAP_INCLUDED
