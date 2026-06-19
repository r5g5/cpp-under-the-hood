//
// Created by Rahul Gupta on 19/06/26.
//
#include <iostream>
#include <iterator>

namespace rdx
{
    /// Queries size of the object or type.
    /// sizeof cannot be used with function types, incomplete types, or bit-field lvalues(until C++11) gl values(since C++11).
    /// When applied to a reference type, the result is the size of the referenced type.
    /// When applied to a class type, the result is the number of bytes occupied by a complete object of
    /// that class, including any additional padding required to place such object in an array.
    /// The number of bytes occupied by a potentially-overlapping subobject may be less than the size of that object.
    /// \refer https://en.cppreference.com/cpp/language/sizeof


    template <typename Type>
    static std::size_t getSizeOf(const Type* arg)
    {
        return reinterpret_cast<const char*>(arg + 1) - reinterpret_cast<const char*>(arg);
    }

}