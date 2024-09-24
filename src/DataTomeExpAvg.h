/***************************************************************
  DataTomeExpAvg.h
  Created by Alexandre Hiroyuki Yamauchi, August 19, 2024.
***************************************************************/

#ifndef DATA_TOME_EXP_AVG_H
#define DATA_TOME_EXP_AVG_H

#include <limits.h>

// RECOMMENDED: use double type for TypeOfSum
// WARNING: using this class with integer types may result in a loss of
// precision due to cumulative rounding of integer divisions.
template <typename TypeOfSum>
class DataTomeExpAvg {
 protected:
  TypeOfSum _exp_avg;
  unsigned long int _count;

 public:
  DataTomeExpAvg() : _exp_avg(0), _count(0) {}

  DataTomeExpAvg<TypeOfSum> &push(TypeOfSum input) {
    if (_count >= ULONG_MAX) {
      _exp_avg = 0;
      _count = 0;
    }
    _count++;

    TypeOfSum multiplier = 2 / (_count);
    _exp_avg = (input * multiplier) + (_exp_avg * (1 - multiplier));

    return *this;
  }

  TypeOfSum get() { return _exp_avg; }
};

#endif  // DATA_TOME_EXP_AVG_H