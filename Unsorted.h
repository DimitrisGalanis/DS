#ifndef PROJECT_2021_DATA_STRUCT_UNSORTED_H
#define PROJECT_2021_DATA_STRUCT_UNSORTED_H

#include <string>
#include <utility>

class Unsorted
{
private:
    size_t size ;  // Μέγεθος πίνακα
    size_t elements; // Πόσα στοιχεία έχει μέσα
    std::pair<std::string,int> *Array;

    void Re_Allocate(size_t new_size);
public:
    Unsorted();
    ~Unsorted();
    const std::pair<std::string,int>& operator[](size_t index) const;
    std::pair<std::string,int>& operator[](size_t index);
    size_t get_elements() const;


    bool search(const std::string&,int &);
    bool remove(const std::string&);
    void insert(const std::string &value);

};

#endif //PROJECT_2021_DATA_STRUCT_UNSORTED_H
