#include <vector>
#include <iostream>

template <typename T>
std::ostream & operator << (
                std::ostream & os,
                const std::vector<T> & vec)
{
    for(auto elem : vec)
    {
        os<<elem<< ", ";
    }
    return os;
}