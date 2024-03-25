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
 public:
  DataTomeAnalysis(size_t size) : DataTomeMvAvg<TypeOfArray, TypeOfSum>(size) {}

  /** Aliases **/

  TypeOfArray mean() { return this->get(); }
  size_t count() { return this->point_count(); }

  /** Proper Methods **/

  TypeOfArray var() {
    TypeOfArray average = this->get();

    TypeOfArray var = 0;
    for (size_t i = 0; i < this->point_count(); i++) {
      var += ((*this)[i] - average) * ((*this)[i] - average);
    }

    return var;
  }

  TypeOfArray std() { return sqrt(var() / this->point_count()); }

  /** Partial Methods **/

  /** Aliases **/

  TypeOfArray partial_mean(size_t partial_id) {
    return this->partial_get(partial_id);
  }
  size_t partial_count(size_t partial_id) {
    return this->partial_size(partial_id);
  }

  /** Proper Methods **/

  TypeOfArray partial_var(size_t partial_id) {
    TypeOfArray average = this->partial_get(partial_id);

    TypeOfArray var = 0;
    for (size_t i = 0; i < this->partial_point_count(partial_id); i++) {
      var += ((*this)[i] - average) * ((*this)[i] - average);
    }

    return var;
  }

  TypeOfArray partial_std(size_t partial_id) {
    return sqrt(partial_var(partial_id) /
                this->partial_point_count(partial_id));
  }
};

#endif  // DATA_TOME_ANALYSIS_H