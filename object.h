#pragma once
#include <iostream>

class Object {
public:
  Object() {
    hash_code = 0;
    hash();
  }

  ~Object() {}

  virtual bool equals(Object *object) { return this == object; }

  virtual size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  }

  virtual void hash_me() { hash_code = (size_t)this; }

  virtual void print_self() {
    printf("empty object");
    // print nothing
  }

  virtual void print_follow_schema(Object *schema, size_t col) {
    printf("empty object");
  }

private:
  size_t hash_code;
};