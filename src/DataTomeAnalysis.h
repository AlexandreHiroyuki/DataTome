/***************************************************************
  DataTomeAnalysis.h
  Data filtering and data analysis structure manager.
  Created by Alexandre Hiroyuki Yamauchi, December 22, 2023.
***************************************************************/

#ifndef DATA_TOME_ANALYSIS_H
#define DATA_TOME_ANALYSIS_H

#include <DataTomeMvAvg.h>

#include <algorithm>
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

  TypeOfArray min() {
    TypeOfArray min = (*this)[0];
    for (size_t i = 1; i < this->point_count(); i++) {
      if ((*this)[i] < min) min = (*this)[i];
    }

    return min;
  }

  TypeOfArray max() {
    TypeOfArray max = (*this)[0];
    for (size_t i = 1; i < this->point_count(); i++) {
      if ((*this)[i] > max) max = (*this)[i];
    }

    return max;
  }

  TypeOfArray median() {
    TypeOfArray median = 0;
    size_t current_size = this->point_count();

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    memcpy(temp, this->_array, current_size * sizeof(TypeOfArray));

    std::sort(temp, temp + current_size);

    if (current_size % 2 == 0) {
      median = (temp[current_size / 2 - 1] + temp[current_size / 2]) / 2;
    } else {
      median = temp[current_size / 2];
    }

    free(temp);

    return median;
  }

  TypeOfArray lowest_mode() {
    size_t current_size = this->point_count();

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    memcpy(temp, this->_array, current_size * sizeof(TypeOfArray));

    std::sort(temp, temp + current_size);

    size_t max_count = 0;
    TypeOfArray mode = temp[0];

    size_t count = 0;
    TypeOfArray current_number = temp[0];

    for (size_t i = 0; i < current_size; i++) {
      if (temp[i] == current_number) {
        count++;
      } else {
        current_number = temp[i];
        count = 1;
      }

      if (count > max_count) {
        max_count = count;
        mode = current_number;
      }
    }

    free(temp);

    return mode;
  }

  TypeOfArray highest_mode() {
    size_t current_size = this->point_count();

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    memcpy(temp, this->_array, current_size * sizeof(TypeOfArray));

    std::sort(temp, temp + current_size);

    size_t max_count = 0;
    TypeOfArray mode = temp[0];

    size_t count = 0;
    TypeOfArray current_number = temp[0];

    for (size_t i = 0; i < current_size; i++) {
      if (temp[i] == current_number) {
        count++;
      } else {
        current_number = temp[i];
        count = 1;
      }

      if (count >= max_count) {
        max_count = count;
        mode = current_number;
      }
    }

    free(temp);

    return mode;
  }

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

  TypeOfArray partial_min(size_t partial_id) {
    TypeOfArray min = (*this)[0];
    for (size_t i = 1; i < this->partial_point_count(partial_id); i++) {
      if ((*this)[i] < min) min = (*this)[i];
    }

    return min;
  }

  TypeOfArray partial_max(size_t partial_id) {
    TypeOfArray max = (*this)[0];
    for (size_t i = 1; i < this->partial_point_count(partial_id); i++) {
      if ((*this)[i] > max) max = (*this)[i];
    }

    return max;
  }

  TypeOfArray partial_median(size_t partial_id) {
    TypeOfArray median = 0;
    size_t current_size = this->partial_point_count(partial_id);

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    for (size_t i = 0; i < current_size; i++) {
      temp[i] = (*this)[i];
    }

    std::sort(temp, temp + current_size);

    if (current_size % 2 == 0) {
      median = (temp[current_size / 2 - 1] + temp[current_size / 2]) / 2;
    } else {
      median = temp[current_size / 2];
    }

    free(temp);

    return median;
  }

  TypeOfArray partial_lowest_mode(size_t partial_id) {
    size_t current_size = this->partial_point_count(partial_id);

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    for (size_t i = 0; i < current_size; i++) {
      temp[i] = (*this)[i];
    }

    std::sort(temp, temp + current_size);

    size_t max_count = 0;
    TypeOfArray mode = temp[0];

    size_t count = 0;
    TypeOfArray current_number = temp[0];

    for (size_t i = 0; i < current_size; i++) {
      if (temp[i] == current_number) {
        count++;
      } else {
        current_number = temp[i];
        count = 1;
      }

      if (count > max_count) {
        max_count = count;
        mode = current_number;
      }
    }

    free(temp);

    return mode;
  }

  TypeOfArray partial_highest_mode(size_t partial_id) {
    size_t current_size = this->partial_point_count(partial_id);

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    for (size_t i = 0; i < current_size; i++) {
      temp[i] = (*this)[i];
    }

    std::sort(temp, temp + current_size);

    size_t max_count = 0;
    TypeOfArray mode = temp[0];

    size_t count = 0;
    TypeOfArray current_number = temp[0];

    for (size_t i = 0; i < current_size; i++) {
      if (temp[i] == current_number) {
        count++;
      } else {
        current_number = temp[i];
        count = 1;
      }

      if (count >= max_count) {
        max_count = count;
        mode = current_number;
      }
    }

    free(temp);

    return mode;
  }

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