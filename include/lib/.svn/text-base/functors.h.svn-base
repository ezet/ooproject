#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>

// As the compiler throws errors about missing externals when separating
// templated types into header and src files, the functors are being defined
// as well as declared here.
// Another solution is to excplicitly specialize each template instantiation that 
// will be used, but this causes more bloat than defining them in the header file,
// especially for short functors. See functors.cpp for an example of the 
// alternate solution.

///
/// Name comparison functor
///
template <class T>
struct NameEquals : public std::binary_function<T, std::string, bool> {
  bool operator() (const T& obj, const std::string& name) const {
    return obj.name() == name;
  }
};


///
/// Prints all contents of a sequence container
///
template<typename InputIterator>
void Print(std::ostream& ostr, InputIterator itbegin, InputIterator itend,
           const std::string& delimiter = "") {
    std::copy(itbegin, itend,std::ostream_iterator
              <typename InputIterator::value_type>(ostr, delimiter.c_str()));
}

