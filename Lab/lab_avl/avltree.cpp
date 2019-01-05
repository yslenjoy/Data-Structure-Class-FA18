/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    Node* tmp = y->left;
    y->left = t;
    t->right = tmp;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    y->height = 1 + max(heightOrNeg1(y->right), heightOrNeg1(y->left));
    t = y;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    Node* tmp = y->right;
    y->right = t;
    t->left = tmp;
    t->height = 1 + max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    y->height = 1 + max(heightOrNeg1(y->right), heightOrNeg1(y->left));
    t = y;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    if (subtree->right == NULL && subtree->left == NULL) {
        return;
    }
    Node* l = subtree->left;
    Node* r = subtree->right;
    int b = heightOrNeg1(r) - heightOrNeg1(l);

    if (b >= 2) {
        int bb = heightOrNeg1(r->right) - heightOrNeg1(r->left);
        if (bb == -1) { // RL
            rotateRightLeft(subtree);
        }
        if (bb == 1) { // L
            rotateLeft(subtree);
        }
    }
    if (b <= -2) {
        int bb = heightOrNeg1(l->right) - heightOrNeg1(l->left);
        if (bb == 1) {
            rotateLeftRight(subtree);
        }
        if (bb == -1) {
            rotateRight(subtree);
        }
    }
    // height update is not actually needed in reblance function, but if height is never updated in inset() or remove(), height needs to be updated in rebalance() function
    // it's good practice to update height in insert() or remove() since the height NEEDS to be updated
    // subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
    }
    else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    subtree->height = 1 + max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)); // height update
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            // Find IOP
            Node* cur = subtree->left;
            while (cur->right != NULL) {
                cur = cur->right;
            }
            swap(subtree, cur);
            remove(subtree->left, key); // recursive call
            // The second way: has some errors
            //remove(subtree, key);subtree: 9, key = 10, remove function will go right rather than go left, therefore, this won't work
            
            // Another way: but this way might has some bugs: when IOP has left child
            // Node* cur2 = subtree->left;
            // if (cur2 == cur) {
            //     cur2 = NULL;
            // }else {
            //     while (cur2->right != cur) {
            //         cur2 = cur2->right;
            //     }
            //     cur2->right = NULL;
            // }

        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != NULL) {
                Node* tmp = subtree;
                subtree = subtree->left;
                delete tmp;
                tmp = NULL;
            }
            if (subtree->right != NULL) {
                Node* tmp = subtree;
                subtree = subtree->right;
                delete tmp;
                tmp = NULL;
            }
        }
        // your code here
    }
    rebalance(subtree); // make sure every node visited is balanced
    // in this way, the rebalance helper function is useful
}
