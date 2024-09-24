/***************************************************************
  DataTomeCumulative.h
  Created by Alexandre Hiroyuki Yamauchi, September 23, 2024.
***************************************************************/

#ifndef DATA_TOME_CUMULATIVE_H
#define DATA_TOME_CUMULATIVE_H

#include <limits.h>

// RECOMMENDED: use double type for TypeOfSum
// WARNING: using this class with integer types may result in a loss of
// precision due to cumulative rounding of integer divisions.
template <typename TypeOfSum>
class DataTomeCumulative {
 protected:
  TypeOfSum _cumulative_average;
  unsigned long int _count;

 public:
  DataTomeCumulative() : _cumulative_average(0), _count(0) {}

  DataTomeCumulative<TypeOfSum> &push(TypeOfSum input) {
    if (_count >= ULONG_MAX) {
      _cumulative_average = 0;
      _count = 0;
    }
    _count++;

    _cumulative_average += (input - _cumulative_average) / (_count);

    return *this;
  }

  TypeOfSum get() { return _cumulative_average; }
};

#endif  // DATA_TOME_CUMULATIVE_H