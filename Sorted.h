#ifndef PROJECT_2021_DATA_STRUCT_SORTED_H
#define PROJECT_2021_DATA_STRUCT_SORTED_H

#include <string>
#include <utility>

class Sorted
{
private:
    size_t elements; // Πόσα στοιχεία έχει μέσα
    std::pair<std::string,int> *Array;
    int find_index(const std::string&,bool &flag_insert);

    void Re_Allocate(size_t new_size);

public:
    Sorted();
    ~Sorted();
    size_t size ;  // Μέγεθος πίνακα
    const std::pair<std::string,int>& operator[](size_t index) const;
    std::pair<std::string,int>& operator[](size_t index);
    unsigned long long get_elements() const;


    int search(int low , int high ,const std::string&) const;
    // bool search(const std::string& value , int &position) 2nd way
    bool remove(const std::string&);
    void insert(const std::string &value);
};


#endif //PROJECT_2021_DATA_STRUCT_SORTED_H
