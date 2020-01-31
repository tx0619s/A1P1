#pragma once
#include "string.h"
#include <assert.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class StrList : public Object {
protected:
  String **list;
  size_t size_;
  size_t capacity_;
  size_t hash_code;

public:
  StrList() : Object() {
    size_ = 0;
    capacity_ = 4;
    list = new String *[capacity_];
    initialize(0);
    hash_code = 0;
    hash();
    // list = (String**) malloc(capacity_ * sizeof(String*));
    // hash_code = (size_t) this;
  }

  ~StrList() { delete[] list; }

  void initialize(size_t from) {
    for (size_t i = from; i < capacity_; i++) {
      list[i] = nullptr;
    }
  }

  void expand() {
    capacity_ *= 2;
    String **temp = new String *[capacity_];
    for (size_t i = 0; i < size_; i++) {
      temp[i] = list[i];
    }
    delete[] list;
    list = temp;
    initialize(size_);
  }

  void push_back(String *e) {
    if (size_ == capacity_) {
      expand();
    }
    list[size_] = e;
    size_++;
  } // Appends e to end

  void add(size_t i, String *e) {
    // will there be a space??
    assert(i <= size_);
    if (size_ == capacity_) {
      expand();
    }
    if (!list[i]) {
      list[i] = e;
      return;
    }
    String **temp = new String *[capacity_];
    for (size_t j = 0; j < i; j++) {
      temp[j] = list[j];
    }
    temp[i] = e;
    for (size_t j = i; j < size_; j++) {
      temp[j + 1] = list[j];
    }
    size_++;
    delete[] list;
    list = temp;
  } // Inserts e at i

  void add_all(size_t i, StrList *c) {
    assert(i <= size_ && i >= 0);
    while (c->size() + size_ > capacity_) {
      expand();
    }
    String **temp = new String *[capacity_];
    for (size_t j = 0; j < i; j++) {
      temp[j] = list[j];
    }
    for (size_t j = i; j < c->size() + i; j++) {
      temp[j] = c->get(j - i);
    }
    for (size_t j = i + c->size(); j < size_ + c->size(); j++) {
      temp[j] = list[j - c->size()];
    }
    size_ += c->size();
    delete[] list;
    list = temp;
  } // Inserts all of elements in c into this list at i

  void clear() {
    delete[] list;
    list = new String *[capacity_];
    initialize(0);
    size_ = 0;
  } // Removes all of elements from this list

  bool contains(Object *o) {
    String *s = dynamic_cast<String *>(o);
    if (!s) {
      return false;
    }
    for (size_t i = 0; i < size_; i++) {
      if (list[i]->equals(s)) {
        return true;
      }
    }
    return false;
  }

  bool equals(Object *o) {
    if (o->hash() == hash_code) {
      // return true;
    }
    StrList *l = dynamic_cast<StrList *>(o);
    if (!l) {
      return false;
    }
    if (size_ != l->size()) {
      return false;
    }

    if (size_ == l->size()) {
      size_t count = 0;
      for (size_t i = 0; i < size_; i++) {
        if (contains(l->get(i))) {
          count++;
        }
      }
      if (count == size_) {
        return true;
      }
    }

    return false;
  } // Compares o with this list for equality.

  String *get(size_t index) {
    assert(index < size_ && index >= 0);
    return list[index];
  } // Returns the element at index

  size_t hash() {
    if (hash_code == 0) {
      hash_me();
    }
    return hash_code;
  } // Returns the hash code value for this list.

  virtual void hash_me() {
    hash_code = 0;
    for (size_t i = 0; i < size_; i++) {
      hash_code += list[i]->hash();
      // list[i]->print_hash();
    }
  }

  size_t index_of(Object *o) {
    String *cast_o = dynamic_cast<String *>(o);
    if (!cast_o) {
      return false;
    }

    for (size_t i = 0; i < size_; i++) {
      if (list[i]->equals(cast_o)) {
        return i;
      }
    }
    return -1;
  } // Returns the index of the first occurrence of o, or >size() if not there

  String *remove(size_t i) {
    assert(i < size_ && i >= 0);
    String **temp = new String *[capacity_];
    String *cur;
    cur = temp[i];
    for (size_t j = 0; j < i; j++) {
      // puts(list[j]->getValue());
      temp[j] = list[j];
    }
    for (size_t j = i + 1; j < size_; j++) {
      // puts(list[j]->getValue());
      temp[j - 1] = list[j];
    }
    delete[] list;
    list = temp;
    size_--;
    return cur;
  } // Removes the element at i

  String *set(size_t i, String *e) {
    assert(i < size_ && i >= 0);
    String *temp = list[i];
    list[i] = e;
    return temp;
  } // Replaces the element at i with e

  size_t size() {
    return size_;
  } // Return the number of elements in the collection

  virtual void print_self() {
    for (size_t i = 0; i < size_; i++) {
      list[i]->print_self();
      printf(" ");
    }
    printf("size: %zu", size_);
  }
};

class SortedStrList : public StrList {
public:
  SortedStrList() : StrList() {}
  ~SortedStrList() { delete[] list; }

  void merge(String **list_, size_t l, size_t m, size_t r) {
    size_t n1, n2, i, j, k;
    n1 = m - l + 1;
    n2 = r - m;
    String **la, **ra;
    la = new String *[n1], ra = new String *[n2];
    for (i = 0; i < n1; i++) {
      la[i] = list_[i + l];
    }
    for (j = 0; j < n2; j++) {
      ra[j] = list_[j + m + 1];
    }
    i = 0;
    j = 0;
    for (k = l; i < n1 && j < n2; k++) {
      size_t a = la[i]->getValue()[0];
      size_t b = ra[j]->getValue()[0];
      // set lower and higher the same
      if (islower(a))
        a -= 32;
      if (islower(b))
        b -= 32;
      if (a <= b) {
        list_[k] = la[i++];
        // list_[k] = la[i++];
      } else {
        list_[k] = ra[j++];
        j++;
        // list_[k] = ra[j++];
      }
    }

    while (i < n1) {
      list_[k++] = la[i++];
    }
    while (j < n2) {
      list_[k++] = ra[j++];
    }
  }
  // size_t are index
  void merge_sort(size_t l, size_t r) {
    size_t m;
    if (l < r) {
      m = (l + r) / 2;
      // sort left
      merge_sort(l, m);
      // sort right
      merge_sort(m + 1, r);
      // last step
      merge(list, l, m, r);
    }
  }

  void sorted_add(String *t) {
    if (size_ == capacity_) {
      expand();
    }
    String *o = new String(t->getValue());
    // merge_sort(0, size_ - 1);
    size_t pre = 0;
    for (size_t i = 0; i < size_; i++) {
      size_t cur = list[i]->getValue()[0];
      size_t os = o->getValue()[0];
      if (islower(cur))
        cur -= 26;
      if (islower(os))
        os -= 26;
      // ignore the catipal letter
      if (cur <= os) {
        pre++;
        continue;
      } else {
        // there are #pre of string prior
        if (pre) {
          add(i, o);
          return;
        }
        // the first string > o
        add(0, o);
        return;
      }
    }
    // there is no string in the list or all previous is smaller than o
    push_back(o);
  }
};