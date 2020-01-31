#pragma once
#include "cast_helper.h"
#include "hashmap.h"
#include "helper2.h"
#include "integer.h"
#include "list.h"
#include "object.h"
#include "string.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

String *f = new String("-f");
String *from = new String("-from");
String *len = new String("-len");
String *print_col_type = new String("-print_col_type");
String *print_col_idx = new String("-print_col_idx");
String *is_missing_idx = new String("-is_missing_idx");

size_t array_contains(String **array, size_t size, String *val) {
  for (size_t i = 0; i < size; i++) {
    if (array[i] && array[i]->equals(val)) {
      // printf("%s\n", array[i]->getValue());
      return true;
    }
  }
  return false;
}

size_t multi_input_check(String *key) {
  if (key->equals(print_col_idx) || key->equals(is_missing_idx)) {
    return true;
  }
  return false;
}

void set_keys(Hashmap *hashmap) {
  hashmap->put(f, nullptr);
  hashmap->put(from, nullptr);
  hashmap->put(len, nullptr);
  hashmap->put(print_col_type, nullptr);
  hashmap->put(print_col_idx, nullptr);
  hashmap->put(is_missing_idx, nullptr);
}

void read_command(Hashmap *hashmap, size_t argv, char **argc) {
  set_keys(hashmap);
  size_t size = hashmap->size();
  String **keys = cast_object_arr(hashmap->key_array(), size);

  for (size_t i = 1; i < argv; i++) {
    String *key = new String(argc[i]);
    if (array_contains(keys, size, key)) {
      if (multi_input_check(key)) {
        StrList *strList = new StrList();
        strList->push_back(new String(argc[i + 1]));
        strList->push_back(new String(argc[i + 2]));
        i = i + 2;
        hashmap->put(key, strList);
      } else {
        hashmap->put(key, new String(argc[i + 1]));
        i++;
      }
    }
  }
}

size_t read_file(Hashmap *command_map, Hashmap *data_map) {
  String *file_path = cast_string(command_map->get(new String("-f")));
  String *from_s = cast_string(command_map->get(new String("-from")));
  String *len_s = cast_string(command_map->get(new String("-len")));
  Integer *from;
  Integer *len;
  if (from_s) {
    from = new Integer(atoi(from_s->getValue()));
  } else {
    from = new Integer(0);
  }
  bool ignore_start_line = 0;
  if (!from->equals(new Integer(0))) {
    ignore_start_line = 1;
  }
  if (len_s) {
    len = new Integer(atoi(len_s->getValue()));
  } else {
    len = new Integer(500);
  }

  FILE *opened_f;
  opened_f = fopen(file_path->getValue(), "r");
  assert(opened_f != 0);
  fseek(opened_f, from->val_, SEEK_SET);
  size_t max_row = loop_read(opened_f, len, data_map, ignore_start_line);
  fclose(opened_f);
  return max_row;
}