#include "Sorted.h"

Sorted::Sorted()
{
    size = 1024;
    elements = 0;
    Array = new std::pair<std::string,int> [size];
}

Sorted::~Sorted() { delete[] Array; }

const std::pair<std::string, int> &Sorted::operator[](size_t index) const
{
    return Array[index];
}

std::pair<std::string, int> &Sorted::operator[](size_t index)
{
    return Array[index];
}

unsigned long long Sorted::get_elements() const { return elements; }

int Sorted::search(int low , int high , const std::string &value) const
{
    //Binary search
if ( low>high)
    return -1;
int mid = (low+high)/2;
if(value==Array[mid].first)
    return mid;
else if(value < Array[mid].first)
    return search(low,mid-1,value);
else
    return search(mid+1,high,value);
}

bool Sorted::remove(const std::string &value)
{
    unsigned long long position = search(0,elements-1,value);
    if (position==-1)
    {
        return false;
    }

    unsigned long long i;
    for (i = position; i < elements - 1; i++)
       Array[i] = Array[i + 1];


    elements = elements -1 ;
    return true;
}

void Sorted::Re_Allocate(size_t new_size)
{
    auto *Temp = new std::pair<std::string,int>[new_size];

    if (new_size < elements)  //Ελέγχος για downsize
        elements = new_size;  // Θεωριτικά δεν θα γίνει μικροτερο ποτέ

    for (size_t i=0; i < elements ; ++i)
        Temp[i] = Array[i];      // string copy maybe?

    delete[] Array;
    Array = Temp;
    size = new_size;
}

void Sorted::insert(const std::string &value)
{
    int index=0;
    bool flag=false;

    if (elements >= size) // Αν δεν έχω χώρο Realloc
        Re_Allocate(2*size);

    index = find_index(value,flag);
    if (flag)
        ++Array[index].second;
    else
    {
        for (auto i = elements; i > index; --i)
            Array[i] = Array[i - 1];

        Array[index].first = value;
        Array[index].second = 1;
        elements = elements + 1;
    }


/*    while(index<elements && value>Array[index].first)
        index++;

    if (Array[index].first==value)
    {
        ++Array[index].second;
        flag=true;
    }

    if(!flag)
    {
        for (auto i = elements; i > index; --i)
            Array[i] = Array[i - 1];

        Array[index].first = value;
        Array[index].second = 1;
        elements = elements + 1;
    }
*/
}

int Sorted::find_index(const std::string &value,bool &flag_insert)
{
    flag_insert = false; // αρχικοποιηση στο οτι δεν εχει βρεθεί
    int start=0;
    int end = elements-1;

    while (start <= end) {
        int mid = (start + end) / 2;

        // If value is found
        if (Array[mid].first == value)
        {
            flag_insert = true;    // γυρνάει true
            return mid;
        }
        else if (Array[mid].first < value)
            start = mid + 1;

        else
            end = mid - 1;
    }
    // Return insert position
    return end + 1;


}

