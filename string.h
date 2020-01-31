#pragma once

#include "object.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class String : public Object {
public:
  String(const char *value) : Object() {
    value_ = value;
    size_ = strlen(value);
    hash_code = 0;
    hash();
  }
  ~String() { delete[] value_; }

  virtual size_t get_size() { return size_; }

  virtual bool equals(Object *object) {
    if (this == object) {
      return true;
    }
    String *s = dynamic_cast<String *>(object);
    if (s == nullptr) {
      return false;
    }
    return !strcmp(s->getValue(), value_);
    // return !strcmp(s->value_, value_);
  }

  String *concat(String *o) {
    char *newValue = new char[size_ + o->get_size() + 1];
    newValue[0] = 0;
    strcat(newValue, value_);
    strcat(newValue, o->getValue());
    String *s = new String((const char *)newValue);
    return s;
  }

  virtual void print_self() { printf("%s", value_); }

  void print_hash() { printf("%zu\n", hash_code); }

  virtual size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }

  virtual void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += 17 * value_[i];
    }
    // printf("hash: %s, code: %d\n", value_, hash_code);
    // hash_code = 57 * (size_t) &(value_);
  }

  virtual const char *getValue() { return value_; }

private:
  const char *value_;
  size_t size_;
  size_t hash_code;
};