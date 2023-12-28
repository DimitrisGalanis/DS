#ifndef AVL_AVL_H
#define AVL_AVL_H

#include "node.h"


class AVL
{
private:
    node *root;
    // Printing
    void inorder (node *);
    void PostOrder (node *);
    void PreOrder (node *);

    //min-max
    node *min(node *);
    node *max(node *);
    node *search (const std::string&);

    //Rotations
    node* RR_rotate(node *);
    node* LL_rotate(node *);
    node* LR_rotate(node *);
    node* RL_rotate(node *);

    //Helpers
    int getHeight(node *);
    int difference(node *);
    node* self_balance(node *);
    bool insert(node*,const std::string&);
    bool remove (node *);



    void destroyTree(node *);
public:
    AVL();
    ~AVL();
    bool insert (const std::string &);
    bool remove (const std::string&);

    bool min (std::string &);
    bool max (std::string &);
    bool search (const std::string& ,int &);

    void printInOrder();
    void printPreorder();
    void printPostorder();
};


#endif //AVL_AVL_H
