#include "Unsorted.h"
#include <cstring>

Unsorted::Unsorted() {
    size = 1024;
    elements = 0;
    Array = new std::pair<std::string,int> [size];
}

Unsorted::~Unsorted() { delete [] Array; }

void Unsorted::Re_Allocate(size_t new_size)
{
    auto *Temp = new std::pair<std::string,int>[new_size];

    if (new_size < elements)  //Ελέγχος για downsize
        elements = new_size;  // Θεωρητικά δεν θα γίνει μικροτερο ποτέ

    for (size_t i=0; i < elements ; ++i)
        Temp[i] = Array[i];

    delete[] Array;
    Array = Temp;
    size = new_size;
}

void Unsorted::insert(const std::string &value)
{
    size_t i=0;
    bool flag=false;

    if (elements >= size) // Αν δεν έχω χώρο Reallocate
        Re_Allocate(2*size);


    while (i<elements && !flag) // search
    {
        if (Array[i].first==value)
        {
            Array[i].second = Array[i].second + 1; // Αυξάνω +1 αφου βρέθηκε
            flag = true;
        }
        i=i+1;
    }

    std::pair<std::string, int> temp;
    temp.first = value;
    temp.second = 1;

    if(!flag)
    {
        Array[elements] = temp;  // προσθέτω το στοιχείο
        elements = elements +1;          // increment τα στοιχεια που έχει ο πίνακας
    }
}

bool Unsorted::search(const std::string& value, int &data)
{
    for (size_t i=0; i<elements; ++i)
    {
        if (value == Array[i].first)
        {
            data=Array[i].second;
            return true;
        }
    }
    return false;
}

bool Unsorted::remove(const std::string &value)
{
    size_t i=0;
    bool flag=false;

    while (i<elements)
    {
        if (Array[i].first == value)
        {
            for (size_t j=i ; j<elements-1 ; ++j )
            {
                Array[j] = Array[j+1];
            }

            --elements;
            flag = true;
            return flag;
        }

        ++i;
    }
    return flag;
}

const std::pair<std::string, int> &Unsorted::operator[](size_t index) const
{

/*    if(index>=elements || index <0)
    {
           //
    }
 */

    return Array[index];
}

std::pair<std::string, int> &Unsorted::operator[](size_t index)
{
/*    if(index>=elements || index <0)
    {
        //
    }
*/
    return Array[index];
}

size_t Unsorted::get_elements() const { return elements; }






