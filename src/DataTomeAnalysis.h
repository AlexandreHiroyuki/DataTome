/***************************************************************
  DataTomeAnalysis.h
  Data filtering and data analysis structure manager.
  Created by Alexandre Hiroyuki Yamauchi, December 22, 2023.
***************************************************************/

#ifndef DATA_TOME_ANALYSIS_H
#define DATA_TOME_ANALYSIS_H

#include <DataTomeMvAvg.h>

#include <cmath>
#include <cstdlib>

template <typename TypeOfArray, typename TypeOfSum = TypeOfArray>
class DataTomeAnalysis : public DataTomeMvAvg<TypeOfArray, TypeOfSum> {
 private:
 public:
  DataTomeAnalysis(size_t size) : DataTomeMvAvg<TypeOfArray, TypeOfSum>(size) {}

  TypeOfArray var() {
    TypeOfArray average = this->get();

    TypeOfArray var = 0;
    for (size_t i = 0; i < this->point_count(); i++) {
      var += ((*this)[i] - average) * ((*this)[i] - average);
    }

    return var;
  }

  TypeOfArray std() { return sqrt(var() / this->size()); }

  TypeOfArray partial_var(size_t partial_id) {
    TypeOfArray average = this->partial_get(partial_id);

    TypeOfArray var = 0;
    for (size_t i = 0; i < this->partial_size(partial_id); i++) {
      var += ((*this)[i] - average) * ((*this)[i] - average);
    }

    return var;
  }

  TypeOfArray partial_std(size_t partial_id) {
    return sqrt(partial_var(partial_id) / this->partial_size(partial_id));
  }
};

#endif  // DATA_TOME_ANALYSIS_H