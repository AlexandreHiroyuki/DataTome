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

  if(a > b)
    return 1;
  else if(a < b)
    return -1;
  return 0;
}

template <typename TypeOfArray> void swap(TypeOfArray &a, TypeOfArray &b) {
  TypeOfArray temp = a;
  a                = b;
  b                = temp;
}

template <typename TypeOfArray>
const TypeOfArray &dt_min(const TypeOfArray &a, const TypeOfArray &b) {
  return (a < b) ? a : b;
}

#endif // DATA_TOME_UTILS_H