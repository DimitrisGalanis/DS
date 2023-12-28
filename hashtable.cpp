#include <string>
#include "hashtable.h"




hashtable::hashtable() //constructor
{
    size=1024;
    elements=0;
    deleted = this; //pointer σε ολόκληρο το hashtable για τα διαγραμμένα αντικείμενα

    A= new myPair *[size];
    for(int i=0;i<size;i++)
        A[i]=nullptr;
}


hashtable::~hashtable() //destructor
{
    delete[] A;
    A=nullptr;
    elements=0;
    size=0;
}


unsigned int hashtable::hash(const string &d) //αλγόριθμος djb2 για hashing
{
    unsigned long int hash = 5381;
    int c;
    for(auto x: d)
    {
        c=x;
        hash=((hash<<5)+hash)+c;
    }
    return (hash%size);
}


unsigned int hashtable::hash2(unsigned int d) //δεύτερη συνάρτηση hashing
{
    return (d+1)%size;
}


bool hashtable::insert (const string &key) //εισαγωγή στοιχείου στον πίνακα
{
    if (search(key)!=nullptr) //+1 εμφάνιση της λέξης αν υπάρχει ήδη στον πίνακα
    {
        myPair *p = search(key);
        p->data++;
        return true;
    }
    if (elements>=size/2) //διπλασιασμός πίνακα
    {
        myPair **temp;
        size*=2;
        temp = new myPair*[size];
        for(int i=0;i<size;i++)
            temp[i]=nullptr;
        for (int i=0;i<size/2;i++)
        {
            if (A[i]!=nullptr && A[i]!=deleted)
            {
                unsigned int p = hash(A[i]->key);
                while (temp[p]!=nullptr)
                    p = hash2(p);
                temp[p]=A[i];
                A[i]=nullptr;
            }
        }
        delete[]A;
        A=temp;
    }
    //εισαγωγή της λέξης αν δεν υπάρχει ήδη
    unsigned int p = hash(key);
    while (A[p]!=nullptr && A[p]!=deleted)
        p = hash2(p);
    A[p]=new  myPair (1,key);
    elements++;
    return true;
}


myPair *& hashtable::search(const string &key)//συνάρτηση για αναζήτηση αντικειμένου
{
    unsigned int p = hash(key);
    while (A[p]==deleted || (A[p]!=nullptr && A[p]->key!=key))
        p = hash2(p);
    return A[p];
}


bool hashtable::search(const string &key, int &data)//public συνάρτηση για αναζήτηση αντικειμένου (καλεί την private)
{
    myPair *p = search(key);

    if (p==nullptr)
        return false;

    data = p->data;

    return true;
}


bool hashtable::remove(const string &key) //συνάρτηση για διαγραφή αντικειμένου
{
    myPair * &p = search(key);
    if (p==nullptr)
        return false;

    elements--;
    delete p;
    p = (myPair *) deleted;
    return true;
}






