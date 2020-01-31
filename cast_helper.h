#pragma once
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"

String *cast_string(Object *object) { return dynamic_cast<String *>(object); }

StrList *cast_list(Object *object) { return dynamic_cast<StrList *>(object); }

Integer *cast_integer(Object *object) {
  return dynamic_cast<Integer *>(object);
}

String **cast_object_arr(Object **array, size_t size) {
  String **output = new String *[size];
  // printf("size in cast_arr: %d\n", size);
  for (size_t i = 0; i < size; i++) {
    output[i] = cast_string(array[i]);
  }
  return output;
}

Integer **cast_object_arr_Integer(Object **array, size_t size) {
  Integer **output = new Integer *[size];
  // printf("size in cast_arr: %d\n", size);
  for (size_t i = 0; i < size; i++) {
    output[i] = cast_integer(array[i]);
  }
  return output;
}
