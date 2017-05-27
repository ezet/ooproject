#pragma once
#include "service\storage\file\BaseFileService.h"
#include "lib\TCollection.h"
#include <fstream>

class SystemFileService : public BaseFileService {
public:
  SystemFileService();

  explicit SystemFileService(std::fstream& file);

  SystemFileService(const std::string fname,
    const std::ios::openmode=std::ios::out|std::ios::in);

  virtual ~SystemFileService();

  ///
  /// Loads system state from file
  ///
  template <class T>
  SystemFileService& LoadState(TCollection<T>* collection) {
    T model;
    while (file() >> model) {
      if (model.Validate()) {
        collection->Add(model);
      } else {
        ErrorHandler::DisplayError("Error: An unexpected error occurred while "
          "loading from file.");
      }
    }
    return *this;
  }

  ///
  /// Saves system state to file
  ///
  template <class T>
  SystemFileService& SaveState(const TCollection<T>* collection) {
    TCollection<T>::CollectionPair iters = collection->GetCollection();
    for (; iters.first != iters.second; ++iters.first)
      file() << *iters.first << '\n';
    return *this;
  }


private:
};