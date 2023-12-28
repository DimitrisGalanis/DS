#ifndef hashtable_h
#define hashtable_h
#include "myPair.h"


using namespace std;


class hashtable
{
    int size; //μέγεθος πίνακα κατακερματισμού
    int elements; //αριθμός στοιχείων που έχω εισάγει στον πίνακα
    myPair **A; //δυναμικός πίνακας αντικειμένων myPair
    void *deleted; //δείκτης για διαγραμμένα αντικείμενα
    unsigned int hash(const string &); //πρώτη συνάρτηση για δημιουργία κλειδιού
    unsigned int hash2(unsigned int ); //δεύτερη συνάρτηση για δημιουργία κλειδιού
    myPair *& search(const string &); //συνάρτηση για αναζήτηση αντικειμένου

public:
    hashtable(); //constructor
    ~hashtable(); //destructor
    bool insert(const string &); //εισαγωγή στοιχείου στον πίνακα
    bool search(const string &, int &data); //public συνάρτηση για αναζήτηση αντικειμένου
    bool remove(const string &); //συνάρτηση για διαγραφή αντικειμένου
};



#endif