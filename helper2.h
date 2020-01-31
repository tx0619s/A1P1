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

char *string_filter(char *raw_string) {
  size_t size = strlen(raw_string);
  size_t buf_index = 0;
  char buf[size];
  char prev = 0;
  bool q_1 = false;
  bool q_2 = false;
  char *temp;
  for (size_t i = 0; i < size; i++) {
    char c = raw_string[i];
    if (c == ' ') {
      if (!(q_1 && !q_2)) {
        if (i < size - 1 && raw_string[i + 1] != ' ') {
          if (raw_string[i + 1] == '>') {
            buf[buf_index++] = '>';
            buf[buf_index] = 0;
            temp = strdup(buf);
            return temp;
          }
          if (prev == '<') {
            continue;
          }
          temp = (char *)"<>";
          return temp;
        }
        continue;
      }
    }
    if (c == '"') {
      if (q_1) {
        q_2 = true;
        buf[buf_index++] = c;
        prev = c;
      } else {
        q_1 = true;
        buf[buf_index++] = c;
        prev = c;
      }
      continue;
    }
    buf[buf_index++] = c;
    prev = c;
  }
  if (q_1 && !q_2) {
    temp = (char *)"<>";
    return temp;
  }
  buf[buf_index] = 0;
  temp = strdup(buf);
  return temp;
}

size_t string_equal(const char *c1, const char *c2) { return !strcmp(c1, c2); }

size_t dismiss_space(char prev, char c) {
  return (prev == '>' && c == ' ') || (prev == 0 && c == ' ');
}

size_t loop_read(FILE *opened_f, Integer *len, Hashmap *data_map,
                 bool ignore_start_line) {
  size_t i = 0;
  size_t ic = 0;
  char c = 0;
  char prev = 0;
  char buffer[255];
  size_t buffer_index = 0;
  StrList *strl = new StrList();
  size_t max_length = 0;
  size_t max_row = 0;
  size_t row = 0;
  bool p1 = true;
  bool p2 = true;
  // Read file from start to len. Store fields without empty
  // space into a string list, then put into map.
  bool end_of_f = false;
  // all data_map
  // split single line
  // printf("%d\n", len->val_);
  while (i < len->val_ && !end_of_f) {
    buffer_index = 0;
    memset(buffer, 0, sizeof(buffer));
    while ((p1 || p2) && i < len->val_) {
      ic = fgetc(opened_f);
      c = (char)ic;
      if (c == '<') {
        p1 = false;
      }
      if (c == '>') {
        p2 = false;
      }
      if (dismiss_space(prev, c)) {
        i++;
        continue;
      }
      if (c == '\n') {
        prev = 0;
        i++;
        break;
      }
      if (feof(opened_f)) {
        end_of_f = true;
        break;
      }
      buffer[buffer_index] = c;
      buffer_index++;
      prev = c;
      i++;
    }
    // push String to list
    // reset p1 p2
    p1 = true;
    p2 = true;
    char *temp = strdup(buffer);
    if (!string_equal(temp, "")) {
      char *new_temp = string_filter(temp);
      strl->push_back(new String(new_temp));
    }
    // change line
    if (c == '\n' || end_of_f || i == len->val_) {
      if (!ignore_start_line) {
        if (strl->size() > max_length) {
          max_row = row;
          max_length = strl->size();
        }
        data_map->put(new Integer(row), strl);
        strl = new StrList();
        row++;
      } else {
        ignore_start_line = 0;
        i = 0;
        strl->clear();
      }
    }
  }
  return max_row;
}