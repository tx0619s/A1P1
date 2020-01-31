#pragma once
#include "cast_helper.h"
#include "hashmap.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 is String, 2 is Float, 3 is Int, 4 is Bool, 0 is missing value
char *identify_datatype(const char *c) {
  char *result = new char[2];
  result[1] = 0;
  bool dot = false;
  bool none_one_or_zero = false;
  bool one_or_zero = false;
  // puts(c);
  for (size_t i = 0; i < strlen(c); i++) {
    if (c[i] == '<' || c[i] == '>' || c[i] == ' ') {
      continue;
    }
    if (c[i] == '"') {
      result[0] = '1';

      return result;
    }
    if (!isdigit(c[i]) && c[i] != '+' && c[i] != '-' && c[i] != '.') {
      result[0] = '1';
      return result;
    }
    if (c[i] == '.') {
      dot = true;
    }
    if (isdigit(c[i]) && c[i] != '0' && c[i] != '1') {
      none_one_or_zero = true;
    }
    if (c[i] == '0' || c[i] == '1') {
      one_or_zero = true;
    }
  }
  if ((none_one_or_zero || one_or_zero) && dot) {
    result[0] = '2';
    return result;
  }
  if (none_one_or_zero) {
    result[0] = '3';
    return result;
  } else {
    result[0] = '4';
    return result;
  }
}

StrList *get_column_header(size_t max_row, Hashmap *data_map) {
  StrList *column_list = new StrList();
  StrList *row = cast_list(data_map->get(new Integer(max_row)));
  for (size_t i = 0; i < row->size(); i++) {
    const char *curr = row->get(i)->getValue();
    char *type = identify_datatype(curr);
    // type[1] = 0;
    column_list->push_back(new String(type));
  }
  return column_list;
}
