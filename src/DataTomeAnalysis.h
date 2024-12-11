/***************************************************************
  DataTomeAnalysis.h
  Data filtering and data analysis structure manager.
  Created by Alexandre Hiroyuki Yamauchi, December 22, 2023.
***************************************************************/

#ifndef DATA_TOME_ANALYSIS_H
#define DATA_TOME_ANALYSIS_H

#include <DataTomeMvAvg.h>
#include <DataTomeUtils.h>
#include <math.h>
#include <stdlib.h>

template <typename TypeOfArray, typename TypeOfSum = TypeOfArray>
class DataTomeAnalysis : public DataTomeMvAvg<TypeOfArray, TypeOfSum> {
 public:
  DataTomeAnalysis(size_t size) : DataTomeMvAvg<TypeOfArray, TypeOfSum>(size) {}

  TypeOfArray minimum() {
    TypeOfArray result = (*this)[0];
    for (size_t i = 1; i < this->point_count(); i++) {
      if ((*this)[i] < result) result = (*this)[i];
    }

    return result;
  }

  TypeOfArray maximum() {
    TypeOfArray result = (*this)[0];
    for (size_t i = 1; i < this->point_count(); i++) {
      if ((*this)[i] > result) result = (*this)[i];
    }

    return result;
  }

  double median() {
    double calculated_median;
    size_t current_size = this->point_count(),
           m = current_size / 2;
    TypeOfArray *temp_array = (TypeOfArray *)malloc(sizeof(TypeOfArray) * current_size);

    memcpy(temp_array, this->_array, sizeof(TypeOfArray) * current_size);

    if (current_size % 2 == 0)
    {
      size_t m1 = quickSelect(0, current_size - 1, m - 1, temp_array),
             m2 = quickSelect(0, current_size - 1, m, temp_array);
      calculated_median = (m1 + m2) / 2.0;
    }
    else
    {
      calculated_median = quickSelect(0, current_size - 1, m, temp_array);
    }
    free(temp_array);
    return calculated_median;
  }

  TypeOfArray lowest_mode() {
    size_t current_size = this->point_count();

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    memcpy(temp, this->_array, current_size * sizeof(TypeOfArray));

    qsort(temp, current_size, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);

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

    qsort(temp, current_size, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);

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
      TypeOfArray data_point = (*this)[i] - average;
      var += (data_point) * (data_point);
    }

    return var;
  }

  TypeOfArray std() { return sqrt(var() / this->point_count()); }

  /** Partial Methods **/

  TypeOfArray partial_minimum(size_t partial_id) {
    TypeOfArray result = (*this)[0];
    for (size_t i = 1; i < this->partial_point_count(partial_id); i++) {
      if ((*this)[i] < result) result = (*this)[i];
    }

    return result;
  }

  TypeOfArray partial_maximum(size_t partial_id) {
    TypeOfArray result = (*this)[0];
    for (size_t i = 1; i < this->partial_point_count(partial_id); i++) {
      if ((*this)[i] > result) result = (*this)[i];
    }

    return result;
  }

  TypeOfArray partial_median(size_t partial_id) {
    TypeOfArray median = 0;
    size_t current_size = this->partial_point_count(partial_id);

    TypeOfArray *temp =
        (typeof(temp))malloc(current_size * sizeof(typeof(temp)));

    for (size_t i = 0; i < current_size; i++) {
      temp[i] = (*this)[i];
    }

    qsort(temp, current_size, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);

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

    qsort(temp, current_size, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);

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

    qsort(temp, current_size, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);

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
      TypeOfArray data_point = (*this)[i] - average;
      var += (data_point) * (data_point);
    }

    return var;
  }

  TypeOfArray partial_std(size_t partial_id) {
    return sqrt(partial_var(partial_id) /
                this->partial_point_count(partial_id));
  }

  private:
    TypeOfArray medianOfMedians(int l, int r, TypeOfArray nums[]) {
      int k = 5;
      size_t size = r - l + 1,
             medians_size = (size + k - 1) / k;
      TypeOfArray medians[medians_size];
      for (int i = l, m_count = 0; i <= r; i += k, m_count++)
      {
        int left = i, right = min(i + k, r + 1),
            mid = left + (right - left) / 2;
        qsort(nums + left, right - left, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);
        medians[m_count] = (nums[mid]);
      }
      qsort(medians, medians_size, sizeof(TypeOfArray), sort_ascend<TypeOfArray>);
      return medians[medians_size / 2];
    };

    TypeOfArray quickSelect(int l, int r, int m, TypeOfArray nums[]) {
      int pivot = medianOfMedians(l, r, nums),
          index = r,
          p = l;
      for (int i = l; i <= r; i++)
      {
        if (nums[i] == pivot)
        {
          index = i;
          swap(nums[index], nums[r]);
          break;
        }
      }
      for (int i = l; i < r; i++)
      {
        if (nums[i] < nums[r])
        {
          swap(nums[i], nums[p]);
          p += 1;
        }
      }
      swap(nums[p], nums[r]);
      if (p > m)
      {
        return quickSelect(l, p - 1, m, nums);
      }
      else if (p < m)
      {
        return quickSelect(p + 1, r, m, nums);
      }
      return nums[p];
    };
};

#endif  // DATA_TOME_ANALYSIS_H