#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
#include <random>
#include <chrono>
#include "Unsorted.h"
#include "Sorted.h"
#include "BST.h"
#include "AVL.h"
#include "hashtable.h"


#define Q_WORD_COUNT 1000

using namespace std;



int main()
{
    string Q[Q_WORD_COUNT];
    string word;
    unsigned long long word_counter=0,word_counter1=0;
    double unsorted_sum=0, sorted_sum=0, BST_sum=0, AVL_sum=0, hash_sum=0;
    Unsorted U;
    Sorted S;
    BST BST;
    AVL AVL;
    hashtable H;
    int Q_counter1[1050],temp,temp1=0,l;

    ifstream ifs;
    ifs.open("input.txt"); //άνοιγμα αρχείου για ανάγνωση, ίσως χρειαστεί το path για το αρχείο
    ofstream ofs;
    if (!ifs.is_open())
        cerr<<"File read error\n"; //error σε περίπτωση που αποτύχει να ανοίξει το αρχείο
    else
    {
        while(ifs>>word) //επιστρέφει true ή false ανάλογα αν μπόρεσε να διαβάσει μια λέξη
            if(word!=" " && word!="\n")
                word_counter++; //μέτρηση αριθμού λέξεων στο αρχείο
    }

    for(int i=0;i<Q_WORD_COUNT;i++) //εύρεση τυχαίων αριθμών για την επιλογή των λέξεων του Q
    {
        l=0;
        random_device random_device;
        mt19937 random_engine(random_device()); //Η random engine χρειάζεται τουλάχιστον 9.2 ή νεότερη έκδοση του gcc
        uniform_int_distribution<int> distribution_1_100(1, word_counter);

        auto const randomNumber = distribution_1_100(random_engine);
        for(int j=0;j<=i;j++)
        {
            if(randomNumber==Q_counter1[j])
            {
                i--;
                l=1;
            }
        }
        if(l==1)
            continue;
        Q_counter1[i]=randomNumber; //εισαγωγή τυχαίου αριθμού στον πίνακα Q_counter1
    }

    for(int i=0;i<Q_WORD_COUNT;i++) //sort του πίνακα Q_counter1
    {
        for(int j=i+1;j<Q_WORD_COUNT;j++)
        {
            if(Q_counter1[i]>Q_counter1[j])
            {
                temp  =Q_counter1[i];
                Q_counter1[i]=Q_counter1[j];
                Q_counter1[j]=temp;
            }
        }
    }

    ifs.close();
    ifs.open("input.txt"); //ίσως χρειαστεί το path για το αρχείο
    if (!ifs.is_open())
        cerr<<"File read error\n"; //error σε περίπτωση που αποτύχει να ανοίξει το αρχείο
    else
    {
        while(ifs>>word)
        {
            for(int i=0, len=word.size();i<len;i++)
            {
                if(ispunct(word[i])) //αφαιρεί τα σημεία στίξης
                {
                    word.erase(i--, 1);
                    len=word.size(); //resize για το νέο μέγεθος του string χωρίς τα σημεία στίξης
                }
            }
            transform(word.begin(), word.end(), word.begin(),[](unsigned char c){ return tolower(c); }); //μετατρέπει τις λέξεις σε lowercase

            if(Q_counter1[temp1]==word_counter1)
            {
                Q[temp1]=word;
                temp1++;
            }



      /*      //χρονομέτρηση δημιουργίας αταξινόμητου πίνακα (unsorted)
            std::chrono::high_resolution_clock::time_point t1_unsorted_construction = std::chrono::high_resolution_clock::now();
            U.insert(word); //εισαγωγή λέξεων
            std::chrono::high_resolution_clock::time_point t2_unsorted_construction = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span_unsorted_construction = std::chrono::duration_cast<std::chrono::duration<double>>(t2_unsorted_construction - t1_unsorted_construction);
            unsorted_sum+=time_span_unsorted_construction.count();
*/

            //χρονομέτρηση δημιουργίας ταξινομημένου πίνακα (sorted)
            std::chrono::high_resolution_clock::time_point t1_sorted_construction = std::chrono::high_resolution_clock::now();
            S.insert(word); //εισαγωγή λέξεων
            std::chrono::high_resolution_clock::time_point t2_sorted_construction = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span_sorted_construction = std::chrono::duration_cast<std::chrono::duration<double>>(t2_sorted_construction - t1_sorted_construction);
            sorted_sum+=time_span_sorted_construction.count();

            //χρονομέτρηση δημιουργίας απλού δυαδικού δένδρου αναζήτησης (BST)
            std::chrono::high_resolution_clock::time_point t1_BST_construction = std::chrono::high_resolution_clock::now();
            BST.insert(word); //εισαγωγή λέξεων
            std::chrono::high_resolution_clock::time_point t2_BST_construction = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span_BST_construction = std::chrono::duration_cast<std::chrono::duration<double>>(t2_BST_construction - t1_BST_construction);
            BST_sum+=time_span_BST_construction.count();

            //χρονομέτρηση δημιουργίας δυαδικού δένδρού αναζήτησης τύπου AVL (AVL)
            std::chrono::high_resolution_clock::time_point t1_AVL_construction = std::chrono::high_resolution_clock::now();
            AVL.insert(word); //εισαγωγή λέξεων
            std::chrono::high_resolution_clock::time_point t2_AVL_construction = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span_AVL_construction = std::chrono::duration_cast<std::chrono::duration<double>>(t2_AVL_construction - t1_AVL_construction);
            AVL_sum+=time_span_AVL_construction.count();

            //χρονομέτρηση δημιουργίας πίνακα κατακερματισμού με ανοικτή διεύθυνση (hashtable)
            std::chrono::high_resolution_clock::time_point t1_hash_construction = std::chrono::high_resolution_clock::now();
            H.insert(word); //εισαγωγή λέξεων
            std::chrono::high_resolution_clock::time_point t2_hash_construction = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_span_hash_construction = std::chrono::duration_cast<std::chrono::duration<double>>(t2_hash_construction - t1_hash_construction);
            hash_sum+=time_span_hash_construction.count();

            word_counter1++;
        }
        cout<<"\n";
        ifs.close();
    }

//δημιουργία unsorted_output.txt αρχείου

/*    ofs.open("unsorted_output.txt"); //διαγραφή στοιχείων του unsorted_output.txt σε περίπτωση που έχει ήδη στοιχεία μέσα από προηγούμενη εκτέλεση του προγράμματος
    ofs.close();
    std::chrono::high_resolution_clock::time_point t1_unsorted = std::chrono::high_resolution_clock::now(); //αρχή μέτρησης χρόνου αναζήτησης
    for(auto & i : Q) //print των λέξεων του Q στο unsorted_output.txt
    {
        int k;
        ofs.open("unsorted_output.txt",ios::app); //άνοιγμα αρχείου για προσθήκη λέξεων και αριθμού εμφανίσεων
        if (ofs.is_open())
        {
            if (U.search(i,k))
            {
                ofs<<i<<": Appeared "<<k<<" times inside the text\n";
            }
            else
                ofs<<" Word not in the table\n"; //θεωρητικά δεν θα συμβεί ποτέ

            ofs.close();
        }
        else
            cerr<<"File error\n";
    }
    std::chrono::high_resolution_clock::time_point t2_unsorted = std::chrono::high_resolution_clock::now(); //τέλος μέτρησης χρόνου αναζήτησης
    std::chrono::duration<double> time_span_unsorted = std::chrono::duration_cast<std::chrono::duration<double>>(t2_unsorted - t1_unsorted);
    ofs.open("unsorted_output.txt",ios::app);
    if (ofs.is_open())
    {
        ofs<<"--------------------------------------------\n"<<"It took "<<time_span_unsorted.count()<<" seconds to complete the whole search\n"<<"--------------------------------------------\n"<<"The construction of unsorted took "<<unsorted_sum<<" seconds to complete\n"; //προσθήκη χρόνου αναζήτησης και δημιουργίας της δομής
    }
    else
        cerr<<"File error\n";
    ofs.close();
*/
//δημιουργία sorted_output.txt αρχείου

    ofs.open("sorted_output.txt"); //διαγραφή στοιχείων του sorted_output.txt σε περίπτωση που έχει ήδη στοιχεία μέσα από προηγούμενη εκτέλεση του προγράμματος
    ofs.close();
    std::chrono::high_resolution_clock::time_point t1_sorted = std::chrono::high_resolution_clock::now(); //αρχή μέτρησης χρόνου αναζήτησης
    for(auto & i : Q) //print των λέξεων του Q στο sorted_output.txt
    {
        int k;
        ofs.open("sorted_output.txt",ios::app); //άνοιγμα αρχείου για προσθήκη λέξεων και αριθμού εμφανίσεων
        if (ofs.is_open())
        {
            k = S.search(0,S.get_elements(),i);
            ofs<<i<<": Appeared "<<S[k].second<<" times inside the text\n";

            ofs.close();
        }
        else
            cerr<<"File error\n";
    }
    std::chrono::high_resolution_clock::time_point t2_sorted = std::chrono::high_resolution_clock::now(); //τέλος μέτρησης χρόνου αναζήτησης
    std::chrono::duration<double> time_span_sorted = std::chrono::duration_cast<std::chrono::duration<double>>(t2_sorted - t1_sorted);
    ofs.open("sorted_output.txt",ios::app);
    if (ofs.is_open())
    {
        ofs<<"--------------------------------------------\n"<<"It took "<<time_span_sorted.count()<<" seconds to complete the whole search\n"<<"--------------------------------------------\n"<<"The construction of sorted took "<<sorted_sum<<" seconds to complete\n"; //προσθήκη χρόνου αναζήτησης και δημιουργίας της δομής
    }
    else
        cerr<<"File error\n";
    ofs.close();

//δημιουργία BST_output.txt αρχείου

    ofs.open("BST_output.txt"); //διαγραφή στοιχείων του BST_output.txt σε περίπτωση που έχει ήδη στοιχεία μέσα από προηγούμενη εκτέλεση του προγράμματος
    ofs.close();
    std::chrono::high_resolution_clock::time_point t1_BST = std::chrono::high_resolution_clock::now(); //αρχή μέτρησης χρόνου αναζήτησης
    for(auto & i : Q) //print των λέξεων του Q στο BST_output.txt
    {
        int k;
        ofs.open("BST_output.txt",ios::app); //άνοιγμα αρχείου για προσθήκη λέξεων και αριθμού εμφανίσεων
        if (ofs.is_open())
        {
            if (BST.search(i,k))
            {
                ofs<<i<<": Appeared "<<k<<" times inside the text\n";
            }
            else
                ofs<<" Word not in the table\n"; //θεωρητικά δεν θα συμβεί ποτέ

            ofs.close();
        }
        else
            cerr<<"File error\n";
    }
    std::chrono::high_resolution_clock::time_point t2_BST = std::chrono::high_resolution_clock::now(); //τέλος μέτρησης χρόνου αναζήτησης
    std::chrono::duration<double> time_span_BST = std::chrono::duration_cast<std::chrono::duration<double>>(t2_BST - t1_BST);
    ofs.open("BST_output.txt",ios::app);
    if (ofs.is_open())
    {
        ofs<<"--------------------------------------------\n"<<"It took "<<time_span_BST.count()<<" seconds to complete the whole search\n"<<"--------------------------------------------\n"<<"The construction of BST took "<<BST_sum<<" seconds to complete\n"; //προσθήκη χρόνου αναζήτησης και δημιουργίας της δομής
    }
    else
        cerr<<"File error\n";
    ofs.close();


//δημιουργία AVL_output.txt αρχείου

    ofs.open("AVL_output.txt"); //διαγραφή στοιχείων του AVL_output.txt σε περίπτωση που έχει ήδη στοιχεία μέσα από προηγούμενη εκτέλεση του προγράμματος
    ofs.close();
    std::chrono::high_resolution_clock::time_point t1_AVL = std::chrono::high_resolution_clock::now(); //αρχή μέτρησης χρόνου αναζήτησης
    for(auto & i : Q) //print των λέξεων του Q στο AVL_output.txt
    {
        int k;
        ofs.open("AVL_output.txt",ios::app); //άνοιγμα αρχείου για προσθήκη λέξεων και αριθμού εμφανίσεων
        if (ofs.is_open())
        {
            if (AVL.search(i,k))
            {
                ofs<<i<<": Appeared "<<k<<" times inside the text\n";
            }
            else
                ofs<<" Word not in the table\n"; //θεωρητικά δεν θα συμβεί ποτέ

            ofs.close();
        }
        else
            cerr<<"File error\n";
    }
    std::chrono::high_resolution_clock::time_point t2_AVL = std::chrono::high_resolution_clock::now(); //τέλος μέτρησης χρόνου αναζήτησης
    std::chrono::duration<double> time_span_AVL = std::chrono::duration_cast<std::chrono::duration<double>>(t2_AVL - t1_AVL);
    ofs.open("AVL_output.txt",ios::app);
    if (ofs.is_open())
    {
        ofs<<"--------------------------------------------\n"<<"It took "<<time_span_AVL.count()<<" seconds to complete the whole search\n"<<"--------------------------------------------\n"<<"The construction of AVL took "<<AVL_sum<<" seconds to complete\n"; //προσθήκη χρόνου αναζήτησης και δημιουργίας της δομής
    }
    else
        cerr<<"File error\n";
    ofs.close();


//δημιουργία hashtable_output.txt αρχείου

    ofs.open("hashtable_output.txt"); //διαγραφή στοιχείων του hashtable_output.txt σε περίπτωση που έχει ήδη στοιχεία μέσα από προηγούμενη εκτέλεση του προγράμματος
    ofs.close();
    std::chrono::high_resolution_clock::time_point t1_hash = std::chrono::high_resolution_clock::now(); //αρχή μέτρησης χρόνου αναζήτησης
    for(auto & i : Q) //print των λέξεων του Q στο hashtable_output.txt
    {
        int k;
        ofs.open("hashtable_output.txt",ios::app);
        if (ofs.is_open())
        {
            if (H.search(i,k))
            {
                ofs<<i<<": Appeared "<<k<<" times inside the text\n";
            }
            else
                ofs<<" Word not in the table\n"; //θεωρητικά δεν θα συμβεί ποτέ

            ofs.close();
        }
        else
            cerr<<"File error\n";
    }
    std::chrono::high_resolution_clock::time_point t2_hash = std::chrono::high_resolution_clock::now(); //τέλος μέτρησης χρόνου αναζήτησης
    std::chrono::duration<double> time_span_hash = std::chrono::duration_cast<std::chrono::duration<double>>(t2_hash - t1_hash);
    ofs.open("hashtable_output.txt",ios::app);
    if (ofs.is_open())
    {
        ofs<<"--------------------------------------------\n"<<"It took "<<time_span_hash.count()<<" seconds to complete the whole search\n"<<"--------------------------------------------\n"<<"The construction of hashtable took "<<hash_sum<<" seconds to complete\n"; //προσθήκη χρόνου αναζήτησης και δημιουργίας της δομής
    }
    else
        cerr<<"File error\n";
    ofs.close();

}