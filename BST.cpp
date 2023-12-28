#include "BST.h"
#include <iostream>

BST::BST() { root = nullptr; }

BST::~BST() { destroyTree(root); }

void BST::destroyTree(node *r)
{
    if (r!= nullptr)
    {
        destroyTree(r->getLeft());
        destroyTree(r->getRight());
        delete(r);
    }
}

bool BST::insert(node *r, const std::string &data)
{
    if (data == r->getValue())
    {
        r->setCounter(r->getCounter()+1);
        return false;
    }
    if (data > r->getValue())
    {
        if (r->getRight()==nullptr)
        {
            r->setRight(new node(data));
            r->getRight()->setParent(r);
            return true;
        }
        return insert (r->getRight(),data);
    }
    else
    {
        if (r->getLeft()==nullptr)
        {
            r->setLeft(new node(data));
            r->getLeft()->setParent(r);
            return true;
        }
        return insert (r->getLeft(),data);
    }
}

bool BST::insert(const std::string &data)
{
    if (root == nullptr)
    {
        root = new node(data);
        return true;
    }
    return insert(root,data);
}

node *BST::search(const std::string& key)
{
    node *p;
    p = root;
    while (p != nullptr && key != p->getValue())
    {
        if (key>p->getValue())
            p = p->getRight();
        else
            p = p->getLeft();
    }
    return p;
}

bool BST::search(const std::string& key, int &ret)
{
    node *p = search (key);
    if (p == nullptr)
        return false;
    ret = p->getCounter();
    return true;
}

void BST::printInOrder() { inOrder (root); }
void BST::printPostOrder() { PostOrder (root); }
void BST::printPreOrder() { PreOrder (root); }

void BST::PreOrder(node *p)
{
    if (p==nullptr)
        return;

    std::cout<<p->getValue()<<std::endl;
    PostOrder (p->getLeft());
    PostOrder (p->getRight());

}

void BST::PostOrder(node *p)
{
    if (p==nullptr)
        return;

    PostOrder (p->getLeft());
    PostOrder (p->getRight());
    std::cout<<p->getValue()<<std::endl;
}

void BST::inOrder(node *p)
{
    if (p==nullptr)
        return;

    inOrder (p->getLeft());
    std::cout<<p->getValue()<<" "<<p->getCounter()<<std::endl;
    inOrder (p->getRight());
}

bool BST::min(std::string &m)
{
    node *r = min (root);
    if (r==nullptr)
        return false;
    m = r->getValue();
    return true;
}

node *BST::min(node *start) {
    if (start ==nullptr)
        return nullptr;

    node *p = start;

    while (p->getLeft()!=nullptr)
        p=p->getLeft();
    return p;
}

bool BST::max(std::string &m)
{
    node  *r = max (root);
    if (r==nullptr)
        return false;
    m= r->getValue();
    return true;
}

node *BST::max(node *start)
{
    if (start ==nullptr)
        return nullptr;

    node *p = start;

    while (p->getRight()!=nullptr)
        p=p->getRight();
    return p;
}

bool BST::remove(const std::string& key)
{
    node *child;

    child = search(key);
    if (child!=nullptr)
        return remove (child);
    return false;
}

bool BST::remove(node *child) {
    node *parent;

    if (child == nullptr)
        return false;

    parent = child->getParent();

    if (child->getLeft() == nullptr && child->getRight()==nullptr) //no children
    {
        if (parent==nullptr) // deleting root
        {
            delete(child);
            root=nullptr;
        }
        else if (parent->getLeft() == child)
        {
            delete (parent->getLeft());
            parent->setLeft(nullptr);
        }
        else
        {
            delete (parent->getRight());
            parent->setRight(nullptr);
        }
    }
    else if (child->getLeft() == nullptr ||child->getRight() == nullptr ) //one child
    {
        if (parent==nullptr) // deleting root
        {
            if (child->getLeft() == nullptr)
                root = child->getRight();
            else
                root = child->getLeft();
            delete (child);
        }
        else if (parent->getLeft()==child)
        {
            if (child->getLeft() == nullptr)
                parent->setLeft(child->getRight());
            else
                parent->setLeft(child->getLeft());
            delete (child);
        }
        else
        {
            if (child->getLeft() == nullptr)
                parent->setRight(child->getRight());
            else
                parent->setRight(child->getLeft());
            delete (child);

        }
    }
    else // two children
    {
        node *mm  = min(child->getRight());
        child->setValue(mm->getValue());

        remove(mm);
    }

    return true;
}

int BST::height() { return height(root); }

int BST::height(node *r) {
    if (r ==nullptr)
        return 0;

    int left,right;

    left = 1+height(r->getLeft());
    right = 1+height(r->getRight());

    return left>right?left:right;
}





















