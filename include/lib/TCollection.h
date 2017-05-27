#pragma once
#include <map>
#include <utility>

///
/// A wrapper class for STL::set, providing a simplified interface
///
template <class T>
class TCollection {
public:
  typedef typename std::set<T>::iterator CollectionIter;
  typedef typename std::pair<CollectionIter, bool> IterBoolPair;
  typedef typename std::pair<CollectionIter, CollectionIter> CollectionPair;

  ///
  /// Adds a element to the collection, returns a pair with an iterator
  /// to the element and a bool value which is true if the element was added
  /// and false otherwise.
  ///
  IterBoolPair Add(const T& elem) {
    return collection_.insert(elem);
  }

  ///
  /// Deletes an element from the collection if found.
  /// Returns 1 if the element was deleted, 0 otherwise.
  ///
  int Delete(const T& elem) {
    return collection_.erase(elem);
  }

  ///
  /// Deletes the element pointed to by iter from the collection.
  /// 
  void Delete(typename std::set<T>::iterator iter) {
    collection_.erase(iter);
  }

  ///
  /// Returns a pair of iterators, where first is an iterator to the
  /// beginning, and second is an iterator to the end of the collection.
  ///
  CollectionPair GetCollection() const {
    return make_pair(collection_.begin(), collection_.end());
  }

  ///
  /// Finds an element in the collection, and returns a pair with an 
  /// iterator and a bool value. pair.second is true if the element
  /// was found.
  ///
  IterBoolPair Find(const T& elem) const {
    IterBoolPair pair;
    pair.first = collection_.find(elem);
    pair.second = pair.first != collection_.end();
    return pair;
  }

  ///
  /// Finds an element by comparing T::name_ attributes.
  /// Returns a pair, first is an iterator and second is a bool value,
  /// where bool is true if the element was found, false otherwise.
  ///
  IterBoolPair FindByName(const std::string name) const {
    IterBoolPair pair;
    pair.first = find_if(collection_.begin(), collection_.end(), bind2nd(NameEquals(), name));
    pair.second = pair.first != collection_.end();
    return pair;
  }

  ///
  /// Returns the number of elements in the collection.
  ///
  int Count() const {
    return collection_.size();
  }

  ///
  /// Returns true if the collection is empty, false otherwise.
  ///
  bool Empty() const {
    return collection_.empty();
  }

  ///
  /// Returns a pair with an iterator to the last element and a bool. 
  /// Bool is false if the collection is empty, otherwise true.
  ///
  IterBoolPair GetLast() const {
    return make_pair(--collection_.end(), !Empty());
  }

  ///
  /// Clears the array, removing all elements
  ///
  void Clear() {
    collection_.clear();
  }

private:
  // insertion operator
  friend std::ostream& operator<<(std::ostream& os, const TCollection<T>& collection);

  // extraction operator
  friend std::istream& operator>>(std::istream& is, TCollection<T>& collection);

  ///
  /// Functor for locating elements by name
  ///
  struct NameEquals : public std::binary_function<T, std::string, bool> {
    bool operator() (const T& obj, const std::string& name) const {
      return !(_stricmp(obj.name().c_str() , name.c_str()));
    }
  };


  // holds the elements
  std::set<T> collection_;
};

// insertion operator
template <class T>
std::ostream& operator<<(std::ostream& os, const TCollection<T>& collection) {
  TCollection<T>::CollectionPair iters = GetCollection();
  for (; iters.first != iters.second; ++iters.first)
    os << *iters.first;
  return os;
}

// extraction operator
template <class T>
std::istream& operator>>(std::istream& is, TCollection<T>& collection) {
  T elem;
  is >> elem;
  return is;
}