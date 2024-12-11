/***************************************************************
  DataTomeUtils.h
  Created by Alexandre Hiroyuki Yamauchi, August 05, 2024.
***************************************************************/

#ifndef DATA_TOME_UTILS_H
#define DATA_TOME_UTILS_H

template <typename TypeOfArray>
int sort_ascend(const void *cmp1, const void *cmp2) {
  TypeOfArray b = *((TypeOfArray *)cmp2);
  TypeOfArray a = *((TypeOfArray *)cmp1);

  return (int)a - b;
}

template <typename TypeOfArray>
void swap(TypeOfArray &a, TypeOfArray &b) {
  TypeOfArray temp = a;
  a = b;
  b = temp;
}

template <typename T1, typename T2>
auto dt_min(const T1 &a, const T2 &b) -> decltype(a < b ? a : b) {
  return (a < b) ? a : b;
}

#endif // DATA_TOME_UTILS_H