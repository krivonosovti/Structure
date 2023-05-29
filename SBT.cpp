#include <iostream>

typedef int key_t;
typedef int element_t;

struct bst
{
    key_t key;
    element_t data;
    bst* left, * right;
};

bst* bst_insert(bst* root, key_t k, element_t e)
{
    if (!root)
    {
        bst* node = (bst*)malloc(sizeof(bst));
        if (!node)
            return NULL;
        node->left = node->right = NULL;
        node->key = k;
        node->data = e;

        return node;
    }
    // block repeated par of key
    if (root->key == k && root->data == e)
        return NULL;
    if (root->key <= k)  //  insert into the right subtree
    {
        bst* node = bst_insert(root->right, k, e);
        if (!node) // err by system 
            return NULL;

        if (root->right == NULL)
            root->right = node;
        // пробегаем до конца 
    }
    else
    {
        bst* node = bst_insert(root->left, k, e);
        if (!node)
            return NULL;
        if (root->left == NULL)
            root->left = node;
    }
    return root;

}

bst* bst_insert_iter(bst* root, key_t k, element_t e)
{
    bst* cur = root, * par;

    bst* node = (bst*)malloc(sizeof(bst));
    if (!node) return NULL;
    node->left = node->right = NULL;
    node->key = k;
    node->data = e;

    if (root == NULL) return node;
    /* par указывает на родительский по отношению к cuк элемент  */
    do
    {
        par = cur;
        cur = k >= cur->key ? cur->right : cur->left;
    } while (cur);
    if (par->key == k && par->data == e) { free(node); return NULL; }
    /* включаем узел в дерево в качестве левого иои правого поддерева */
    if (k >= par->key)
        par->right = node;
    else
        par->left = node;
    return root;
}

bst* bst_search(bst* root, key_t k)
{
    bst* cur = root;
    while (cur)
    {
        if (k < cur->key) cur = cur->left;
        else if (k > cur->key) cur = cur->right;
        else return cur;
    }

    return NULL;
}

bst* bst_search_pair(bst* root, key_t k, element_t e)
{
    while ((root = bst_search(root, k)) && root->data != e)
        root = root->right;
    return root;
}

bst* bst_max(bst* root)
{
    bst* cur = root;
    if (!root) return NULL;
    while (cur->right) cur = cur->right;
    return cur;
}
bst* bst_min(bst* root)
{
    bst* cur = root;
    if (!root) return NULL;
    while (cur->left) cur = cur->left;
}

bst* bst_successor(bst* root, bst* node)
{
    bst* succ = NULL;
    //поиск наименьшего элемента в правом поддереве
    if (node->right) return bst_min(node->right);
    /*  близшайшей левый порядок*/
    while (root)
    {
        if (node->key < root->key)
        {
            succ = root;
            root = root->left;
        }
        else if (node == root)
            return succ;
        else
            root = root->right;
    }
    return succ;
}

bst* bst_predecessor(bst* root, bst* node)
{
    bst* succ = NULL;
    if (node->left) return bst_max(node->left);
    while (root)
    {
        if (node->key > root->key)
        {
            succ = root;
            root = root->right;
        }
        else if (node == root)
            return succ;
        else
            root = root->left;
    }
    return succ;
}

int bst_remove(bst** root, bst* node)
{
    if (!root)
        return 1;
    if (node == *root)//нашли удаляемый элемент 
    {
        if (node->left && node->right)
            return bst_remove(&(*root)->right, bst_min(node->right));
        else
        {
            bst* t = *root;
            *root = (*root)->left ? (*root)->left : (*root)->right;
            free(t);
            return 0;
        }
    }
    else if (node->key >= (*root)->key)
        return bst_remove(&(*root)->right, node);
    else
        return bst_remove(&(*root)->left, node);
}

void bst_free(bst* tree)
{
    if (tree)
    {
        bst_free(tree->left);
        bst_free(tree->right);
        free(tree);
    }
}

int main()
{
    bst* tree = NULL;

    std::cout << "Hello World!\n";
}
