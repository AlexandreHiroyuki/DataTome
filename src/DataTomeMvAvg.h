/***************************************************************
  DataTomeMvAvg.h - Moving average structure manager.
  Created by Alexandre Hiroyuki Yamauchi, September 2, 2019.
***************************************************************/
#ifndef DATA_TOME_MV_AVG_H
#define DATA_TOME_MV_AVG_H

#include <cstdlib>
#include <cstring>  // memset

template <typename TypeOfArray, typename TypeOfSum = TypeOfArray>
class DataTomeMvAvg {
 protected:
  size_t _array_size;
  size_t _current_index;
  size_t _average_counter;

  TypeOfArray *_array;
  TypeOfSum _average_sum;

  size_t _partial_sums_counter;
  TypeOfSum *_partial_sums;
  size_t *_partial_sum_sizes;

  void _next_index() {
    _current_index++;
    if (_current_index >= _array_size) _current_index = 0;
  }

 public:
  /** Constructor **/
  DataTomeMvAvg(size_t size)
      : _array_size(size),
        _current_index(0),
        _average_counter(0),
        _array((TypeOfArray *)calloc(size, sizeof(TypeOfArray))),
        _average_sum(0),
        _partial_sums_counter(0),
        _partial_sums((TypeOfSum *)calloc(1, sizeof(TypeOfSum))),
        _partial_sum_sizes((size_t *)calloc(1, sizeof(size_t))) {}

  /** Destructor **/
  ~DataTomeMvAvg() {
    free(_array);
    free(_partial_sums);
    free(_partial_sum_sizes);
  }

  /** Get Result and Access elements **/

  DataTomeMvAvg<TypeOfArray, TypeOfSum> &push(TypeOfArray input) {
    TypeOfArray last_value = _array[_current_index];
    _average_sum -= last_value;
    _average_sum += input;
    _array[_current_index] = input;

    for (size_t i = 0; i < _partial_sums_counter; i++) {
      _partial_sums[i] += input;
      _partial_sums[i] -= (*this)[_partial_sum_sizes[i] - 1];
    }

    if (_average_counter < _array_size) {
      _average_counter++;
    }

    _next_index();

    return *this;
  }

  TypeOfArray get() {
    return (_average_sum / ((_average_counter == 0) ? 1 : _average_counter));
  }
  TypeOfArray get(size_t n_points) {
    // @alias get_by_brute
    return get_by_brute(n_points);
  }

  TypeOfArray get_by_brute(size_t n_points) {
    if (n_points > _average_counter) n_points = _average_counter;

    int sum = 0;
    for (size_t i = 0; i < n_points; i++) {
      sum += (*this)[i];
    }

    return sum / n_points;
  }

  TypeOfArray front() {
    int last_index = _current_index;

    if (last_index - 1 < 0) {
      last_index = _array_size - 1;
    } else {
      last_index -= 1;
    }

    return _array[last_index];
  }

  TypeOfArray back() {
    if (_average_counter < _array_size) {
      return _array[0];
    }
    return _array[_current_index];
  }

  TypeOfArray operator[](size_t index) {
    int final_index = (_current_index - 1) - index;

    int check_index = _array_size + final_index;

    if (final_index < 0) {
      return _array[check_index];
    }

    return _array[final_index];
  }

  TypeOfArray at_index(size_t index) { return _array[index]; }

  size_t size_of_array() { return _array_size; }

  size_t size() { return size_of_array(); }

  size_t size_of_memory() { return _array_size * sizeof(TypeOfArray); }

  size_t point_count() { return _average_counter; }

  /** Modify array **/

  DataTomeMvAvg<TypeOfArray, TypeOfSum> &grow(size_t new_size) {
    if (new_size <= _array_size) return *this;

    _current_index = new_size - 1;

    _array = static_cast<TypeOfArray *>(
        realloc(_array, new_size * sizeof(TypeOfArray)));

    for (size_t i = _array_size; i < new_size; i++) _array[i] = 0;

    _array_size = new_size;
    return *this;
  }
  DataTomeMvAvg<TypeOfArray, TypeOfSum> &resize(size_t new_size) {
    // @alias grow
    return grow(new_size);
  }

  DataTomeMvAvg<TypeOfArray, TypeOfSum> &clear() {
    memset(_array, 0, sizeof(TypeOfArray) * _array_size);

    _current_index = 0;

    _average_sum = 0;

    _average_counter = 0;

    return *this;
  }

  /** Partial Average methods **/

  size_t partial_create(size_t sum_size) {
    if (sum_size > _array_size) {
      sum_size = _array_size;
    }

    size_t _counter_initial_size = 1;
    _partial_sums_counter++;

    if (_partial_sums_counter > _counter_initial_size) {
      _partial_sums = static_cast<TypeOfSum *>(
          realloc(_partial_sums, _partial_sums_counter * sizeof(TypeOfSum)));
      _partial_sum_sizes = static_cast<size_t *>(
          realloc(_partial_sum_sizes, _partial_sums_counter * sizeof(size_t)));
    }

    _partial_sums[_partial_sums_counter - 1] = 0;

    for (size_t i = 0; i < sum_size; i++) {
      _partial_sums[_partial_sums_counter - 1] += (*this)[i];
    }

    _partial_sum_sizes[_partial_sums_counter - 1] = sum_size;

    return _partial_sums_counter - 1;
  }

  TypeOfArray partial_get(size_t id) {
    if (id > _partial_sums_counter) return 0;

    if (_average_counter >= _partial_sum_sizes[id])
      return _partial_sums[id] / _partial_sum_sizes[id];
    else
      return _partial_sums[id] /
             ((_average_counter == 0) ? 1 : _average_counter);
  }

  size_t partial_size_of_array(size_t id) {
    if (id > _partial_sums_counter) return 0;

    return _partial_sum_sizes[id];
  }

  size_t partial_size(size_t id) { return partial_size_of_array(id); }

  size_t partial_point_count(size_t id) {
    if (id > _partial_sums_counter) return 0;

    if (_average_counter >= _partial_sum_sizes[id])
      return _partial_sum_sizes[id];
    else
      return _average_counter;
  }

  size_t partials_memory() {
    return sizeof(_partial_sums_counter) + sizeof(_partial_sums) +
           sizeof(_partial_sum_sizes);
  }
};

#endif
