#pragma once
#include "object.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
// this is a general hashmap. I create it for practice and
// might be useful for future assignment.

class Hashmap_pair : public Object {
public:
  Object *key_;
  Object *val_;
  Hashmap_pair(Object *key, Object *val) : Object() {
    key_ = key;
    val_ = val;
  }
  ~Hashmap_pair() {
    delete key_;
    delete val_;
  }
};

class Hashmap : public Object {
private:
  Hashmap_pair **data;
  size_t size_;
  size_t capacity_;

public:
  Hashmap() {
    data = new Hashmap_pair *[4];
    capacity_ = 4;
    initialize(data);
    size_ = 0;
  }

  ~Hashmap() { delete[] data; }

  void initialize(Hashmap_pair **new_data) {
    for (size_t i = 0; i < capacity_; i++) {
      new_data[i] = nullptr;
    }
  }

  size_t hash_index(Object *key) {
    if (key) {
      return key->hash() & (capacity_ - 1);
    }
    return -1;
  }

  /** helper method to increase the index i in hash_put method*/
  size_t index_grow(size_t i) {
    if (i == capacity_ - 1) {
      return 0;
    }
    return i + 1;
  }

  /** check whether the loop needs end in hash_put method*/
  bool index_check(size_t i, size_t index, size_t count) {
    if (i == index && count != 0) {
      return false;
    }
    return true;
  }

  /** put key and val into temp_map*/
  void hash_put(Hashmap_pair **temp_elems, Object *key, Object *val) {
    size_t index = hash_index(key);
    for (size_t i = index, count = 0; index_check(i, index, count);
         i = index_grow(i), count++) {
      if (!temp_elems[i]) {
        temp_elems[i] = new Hashmap_pair(key, val);
        size_++;
        return;
      } else if (temp_elems[i]->key_->equals(key)) {
        temp_elems[i]->val_ = val;
        return;
      }
    }
  }

  /** expand the node array size*/
  void expand() {
    capacity_ *= 2;
    size_t prev_len_ = size_;
    size_ = 0;
    Hashmap_pair **new_elems = new Hashmap_pair *[capacity_];
    initialize(new_elems);
    for (size_t i = 0, count = 0; count < prev_len_ && i < capacity_ / 2; i++) {
      if (data[i]) {
        hash_put(new_elems, data[i]->key_, data[i]->val_);
        count++;
      }
    }
    delete[] data;
    data = new_elems;
  }

  /** Gets the value of the key*/
  Object *get(Object *key) {
    size_t index = hash_index(key);
    for (size_t i = index, count = 0; index_check(i, index, count);
         i = index_grow(i), count++) {
      Hashmap_pair *cur = data[i];
      if (cur) {
        if (cur->key_->equals(key)) {
          return cur->val_;
        }
      }
    }
    return nullptr;
  }

  void put(Object *key, Object *val) {
    if (size_ == capacity_) {
      expand();
    }
    hash_put(data, key, val);
  }

  // Removed the given key from the map
  void remove(Object *key) {
    size_t index = hash_index(key);
    for (size_t i = index, count = 0; index_check(i, index, count);
         i = index_grow(i), count++) {
      if (data[i]) {
        if (data[i]->key_->equals(key)) {
          data[i] = nullptr;
          size_--;
        }
      }
    }
  }

  size_t size() { return size_; }

  Object **key_array() {
    Object **keys;
    keys = new Object *[size_];
    size_t key_size = 0;
    for (size_t i = 0; i < capacity_; i++) {
      if (data[i]) {
        keys[key_size] = data[i]->key_;
        key_size++;
      }
    }
    return keys;
  }

  virtual void print_self() {
    Object **keys = key_array();
    for (size_t i = 0; i < size_; i++) {
      printf("key: ");
      keys[i]->print_self();
      printf(" val: ");
      get(keys[i])->print_self();
      printf("\n");
    }
  }
};