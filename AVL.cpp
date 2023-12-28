#include "AVL.h"
#include <iostream>

node *AVL::RR_rotate(node *p) // parent
{
    node *temp;
    temp = p->getRight();
    p->setRight(temp->getLeft());
    temp->setLeft(p);

    return temp;
}

node *AVL::LL_rotate(node *p)
{
    node *temp;
    temp = p->getLeft();
    p->setLeft(temp->getRight());
    temp->setRight(p);

    return temp;
}

node *AVL::LR_rotate(node *p) {
    node *temp;
    temp = p->getLeft();
    p->setLeft(RR_rotate(temp));

    return LL_rotate(p);
}

node *AVL::RL_rotate(node *p) {
    node *temp;
    temp = p->getLeft();
    p->setRight(LL_rotate(temp));

    return RR_rotate(p);
}

int AVL::getHeight(node* obj) {
    int h=0;
    if (obj != nullptr)
    {
        int l_height = getHeight(obj->getLeft());
        int r_height = getHeight(obj->getRight());
        return r_height>l_height?r_height:l_height;
    }

    return h;
}


int AVL::difference(node *obj)
{
    int l_height = getHeight(obj->getLeft());
    int r_height = getHeight(obj->getRight());

    return l_height - r_height;
}

node* AVL::self_balance(node *obj)
{
    if (difference(obj) >1 )
    {
        if (difference(obj->getLeft()) > 0)
            obj = LL_rotate(obj);
        else
            obj = LR_rotate(obj);
    }
    else if (difference(obj) < -1)
    {
        if (difference(obj->getRight()) > 0)
            obj = RL_rotate(obj);
        else
            obj = RR_rotate(obj);
    }
    return obj;
}

bool AVL::insert(node *r, const std::string &data)
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
            self_balance(r);
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
            self_balance(r);
            return true;
        }
        return insert (r->getLeft(),data);
    }
}

bool AVL::insert(const std::string &data)
{
    if (root == nullptr)
    {
        root = new node(data);
        return true;
    }
    return insert(root,data);
}

bool AVL::remove(node *child)
{
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
            self_balance(root);
        }
        else
        {
            delete (parent->getRight());
            parent->setRight(nullptr);
            self_balance(root);

        }
    }
    else if (child->getLeft() == nullptr || child->getRight() == nullptr ) //one child
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
        child->setCounter(mm->getCounter());

        remove(mm);
    }

    self_balance(root);
    return true;
}

node *AVL::min(node *start)
{
    if (start ==nullptr)
        return nullptr;

    node *p = start;

    while (p->getRight()!=nullptr)
        p=p->getRight();
    return p;
}

bool AVL::min(std::string &m)
{
    node *r = min (root);
    if (r==nullptr)
        return false;
    m = r->getValue();
    return true;
}

node *AVL::max(node *start)
{
    if (start ==nullptr)
        return nullptr;

    node *p = start;

    while (p->getRight()!=nullptr)
        p=p->getRight();
    return p;
}

bool AVL::max(std::string &m) {
    node  *r = max (root);
    if (r==nullptr)
        return false;
    m= r->getValue();
    return true;
}

node *AVL::search(const std::string &key) {
    node *p;
    p = root;
    while (p != nullptr && key != p->getValue()) {
        if (key > p->getValue())
            p = p->getRight();
        else
            p = p->getLeft();
    }
    return p;
}

bool AVL::search(const std::string& key, int &ret)
{
    node *p = search (key);
    if (p == nullptr)
        return false;
    ret = p->getCounter();
    return true;
}

void AVL::inorder(node *p)
{
    if (p==nullptr)
        return;

    inorder (p->getLeft());
    std::cout<<p->getValue()<<" "<<p->getCounter()<<std::endl;
    inorder (p->getRight());
}

void AVL::printInOrder() { inorder (root); }


bool AVL::remove(const std::string &key)
{
    node *child;

    child = search(key);
    if (child!=nullptr)
        return remove (child);
    return false;
}

AVL::AVL()
{
    root = nullptr;
}


void AVL::printPreorder()
{
    PreOrder(root);
}

void AVL::printPostorder()
{
    PostOrder(root);
}

void AVL::PostOrder(node *p)
{
    if (p==nullptr)
        return;

    PostOrder (p->getLeft());
    PostOrder (p->getRight());
    std::cout<<p->getValue()<<std::endl;
}

void AVL::PreOrder(node *p)
{
    if (p==nullptr)
        return;

    std::cout<<p->getValue()<<std::endl;
    PostOrder (p->getLeft());
    PostOrder (p->getRight());
}

void AVL::destroyTree(node *r)
{
    if (r!= nullptr)
    {
        destroyTree(r->getLeft());
        destroyTree(r->getRight());
        delete(r);
    }
}

AVL::~AVL() { destroyTree(root); }





