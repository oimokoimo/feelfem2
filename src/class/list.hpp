/*
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *
 *  Purpose: Minimal singly-linked list + iterator compatible with feelfem1 APIs.
 *
 *  Notes:
 *   - Clean-room reimplementation: does NOT include/derive from Budd (1992) code.
 *   - Keeps legacy API surface (add/addlast/deletelastlink/adduniq/duplicate/etc.)
 *     to minimize changes in parser/backend.
 */

#pragma once

#include <cassert>
#include "iterator.hpp"

template <class T> class link;
template <class T> class listIterator;
template <class T> class ptrList;

template <class T>
class list
{
public:
  list() noexcept : ptrToFirstLink(nullptr) {}
  list(const list<T>& source);
  virtual ~list() { deleteAllValues(); }

  // operations
  void         add(T value);
  void         addnonvirtual(T value);     // legacy: keep
  void         addlast(T value);
  void         deletelastlink();           // delete link only (not the value itself)
  void         adduniq(T value);           // add if not includes
  virtual void deleteAllValues();

  list*        duplicate() const;

  T            firstElement() const;
  T            lastElement() const;
  virtual int  includes(T value) const;
  virtual int  getPosition(T value) const;

  int          isEmpty() const noexcept { return this->ptrToFirstLink == nullptr; }
  virtual void removeFirst();

  T            getNthElement(int n) const; // n starts from 1
  int          getNumberOfElements();

protected:
  link<T>* ptrToFirstLink;

  friend class listIterator<T>;
  friend class ptrList<T>;
};

template <class T>
class link
{
public:
  link<T>* insert(T val);

private:
  link(T linkValue, link* nextPtr) : value(linkValue), ptrToNextLink(nextPtr) {}
  link(const link&) = delete;
  link& operator=(const link&) = delete;

  link* duplicate() const;

  T     value;
  link* ptrToNextLink;

  friend class list<T>;
  friend class ptrList<T>;
  friend class listIterator<T>;
};

template <class T>
class listIterator : public iterator<T>
{
public:
  explicit listIterator(list<T>& aList);
  listIterator(const listIterator& x);

  int  init() override;
  T    operator()() override;
  int  operator!() override;
  int  operator++() override;
  void operator=(T value) override;

  void removeCurrent();
  void addBefore(T newValue);
  void addAfter(T newValue);

protected:
  link<T>* currentLink;
  link<T>* previousLink;
  list<T>& theList;
};

template <class T>
class doubleEndedList : public list<T>
{
public:
  doubleEndedList() noexcept : list<T>(), ptrToLastLink(nullptr) {}
  doubleEndedList(const doubleEndedList& x);

  void add(T value) override;
  void deleteAllValues() override;
  void removeFirst() override;

  void addToEnd(T value);

protected:
  link<T>* ptrToLastLink;
};

// =========================== list<T> implementation ===========================

template <class T>
list<T>::list(const list<T>& source) : ptrToFirstLink(nullptr)
{
  if (!source.isEmpty()) {
    this->ptrToFirstLink = source.ptrToFirstLink->duplicate();
  }
}

template <class T>
void list<T>::add(T val)
{
  this->ptrToFirstLink = new link<T>(val, this->ptrToFirstLink);
  assert(this->ptrToFirstLink != nullptr);
}

template <class T>
void list<T>::addnonvirtual(T val)
{
  // kept for legacy call sites
  this->add(val);
}

template <class T>
void list<T>::addlast(T val)
{
  if (this->ptrToFirstLink == nullptr) {
    this->ptrToFirstLink = new link<T>(val, nullptr);
    assert(this->ptrToFirstLink != nullptr);
    return;
  }

  link<T>* p = this->ptrToFirstLink;
  while (p->ptrToNextLink != nullptr) {
    p = p->ptrToNextLink;
  }
  p->ptrToNextLink = new link<T>(val, nullptr);
  assert(p->ptrToNextLink != nullptr);
}

template <class T>
void list<T>::deletelastlink()
{
  if (this->ptrToFirstLink == nullptr) return;

  // only one element
  if (this->ptrToFirstLink->ptrToNextLink == nullptr) {
    delete this->ptrToFirstLink;
    this->ptrToFirstLink = nullptr;
    return;
  }

  link<T>* prev = this->ptrToFirstLink;
  link<T>* cur  = this->ptrToFirstLink->ptrToNextLink;

  while (cur->ptrToNextLink != nullptr) {
    prev = cur;
    cur  = cur->ptrToNextLink;
  }

  // cur is last
  prev->ptrToNextLink = nullptr;
  delete cur;
}

template <class T>
void list<T>::deleteAllValues()
{
  link<T>* p = this->ptrToFirstLink;
  while (p != nullptr) {
    link<T>* next = p->ptrToNextLink;
    p->ptrToNextLink = nullptr;
    delete p;
    p = next;
  }
  this->ptrToFirstLink = nullptr;
}

template <class T>
list<T>* list<T>::duplicate() const
{
  list<T>* newlist = new list<T>();
  assert(newlist != nullptr);
  if (this->ptrToFirstLink != nullptr) {
    newlist->ptrToFirstLink = this->ptrToFirstLink->duplicate();
  }
  return newlist;
}

template <class T>
T list<T>::firstElement() const
{
  assert(this->ptrToFirstLink != nullptr);
  return this->ptrToFirstLink->value;
}

template <class T>
T list<T>::lastElement() const
{
  assert(this->ptrToFirstLink != nullptr);
  link<T>* p = this->ptrToFirstLink;
  while (p->ptrToNextLink != nullptr) {
    p = p->ptrToNextLink;
  }
  return p->value;
}

template <class T>
T list<T>::getNthElement(int n) const
{
  assert(n >= 1);
  assert(this->ptrToFirstLink != nullptr);

  link<T>* p = this->ptrToFirstLink;
  for (int i = 1; i < n; ++i) {
    p = p->ptrToNextLink;
    assert(p != nullptr);
  }
  return p->value;
}

template <class T>
void list<T>::adduniq(T val)
{
  if (this->includes(val)) return;
  this->add(val);
}

template <class T>
int list<T>::includes(T v) const
{
  for (link<T>* p = this->ptrToFirstLink; p != nullptr; p = p->ptrToNextLink) {
    if (v == p->value) return 1;
  }
  return 0;
}

template <class T>
int list<T>::getPosition(T v) const
{
  int no = 1;
  for (link<T>* p = this->ptrToFirstLink; p != nullptr; p = p->ptrToNextLink) {
    if (v == p->value) return no;
    ++no;
  }
  return 0;
}

template <class T>
void list<T>::removeFirst()
{
  assert(this->ptrToFirstLink != nullptr);
  link<T>* p = this->ptrToFirstLink;
  this->ptrToFirstLink = p->ptrToNextLink;
  p->ptrToNextLink = nullptr;
  delete p;
}

template <class T>
int list<T>::getNumberOfElements()
{
  int counter = 0;
  for (link<T>* p = this->ptrToFirstLink; p != nullptr; p = p->ptrToNextLink) {
    ++counter;
  }
  return counter;
}

// =========================== link<T> implementation ===========================

template <class T>
link<T>* link<T>::insert(T val)
{
  this->ptrToNextLink = new link<T>(val, this->ptrToNextLink);
  assert(this->ptrToNextLink != nullptr);
  return this->ptrToNextLink;
}

template <class T>
link<T>* link<T>::duplicate() const
{
  link<T>* newlink = new link<T>(this->value, nullptr);
  assert(newlink != nullptr);

  if (this->ptrToNextLink != nullptr) {
    newlink->ptrToNextLink = this->ptrToNextLink->duplicate();
  }
  return newlink;
}

// ======================== listIterator<T> implementation ======================

template <class T>
listIterator<T>::listIterator(list<T>& aList)
  : currentLink(nullptr), previousLink(nullptr), theList(aList)
{
  init();
}

template <class T>
listIterator<T>::listIterator(const listIterator& x)
  : currentLink(nullptr), previousLink(nullptr), theList(x.theList)
{
  init();
}

template <class T>
int listIterator<T>::init()
{
  previousLink = nullptr;
  currentLink  = theList.ptrToFirstLink;
  return currentLink != nullptr;
}

template <class T>
T listIterator<T>::operator()()
{
  assert(currentLink != nullptr);
  return currentLink->value;
}

template <class T>
int listIterator<T>::operator!()
{
  if (currentLink == nullptr && previousLink != nullptr) {
    currentLink = previousLink->ptrToNextLink;
  }
  return currentLink != nullptr;
}

template <class T>
int listIterator<T>::operator++()
{
  if (currentLink == nullptr) {
    if (previousLink == nullptr) currentLink = theList.ptrToFirstLink;
    else                        currentLink = previousLink->ptrToNextLink;
  } else {
    previousLink = currentLink;
    currentLink  = currentLink->ptrToNextLink;
  }
  return currentLink != nullptr;
}

template <class T>
void listIterator<T>::operator=(T val)
{
  assert(currentLink != nullptr);
  currentLink->value = val;
}

template <class T>
void listIterator<T>::removeCurrent()
{
  assert(currentLink != nullptr);

  if (previousLink == nullptr) {
    theList.ptrToFirstLink = currentLink->ptrToNextLink;
  } else {
    previousLink->ptrToNextLink = currentLink->ptrToNextLink;
  }

  currentLink->ptrToNextLink = nullptr;
  delete currentLink;
  currentLink = nullptr;
}

template <class T>
void listIterator<T>::addBefore(T val)
{
  if (previousLink != nullptr) {
    previousLink = previousLink->insert(val);
  } else {
    theList.addnonvirtual(val);
    previousLink = theList.ptrToFirstLink;
    currentLink  = previousLink->ptrToNextLink;
  }
}

template <class T>
void listIterator<T>::addAfter(T val)
{
  if (currentLink != nullptr) {
    currentLink->insert(val);
  } else if (previousLink != nullptr) {
    currentLink = previousLink->insert(val);
  } else {
    theList.add(val);
  }
}

// ======================= doubleEndedList<T> implementation ====================

template <class T>
doubleEndedList<T>::doubleEndedList(const doubleEndedList& x)
  : list<T>(x), ptrToLastLink(nullptr)
{
  // re-locate last link pointer
  if (!this->isEmpty()) {
    link<T>* p = this->ptrToFirstLink;
    while (p->ptrToNextLink != nullptr) p = p->ptrToNextLink;
    ptrToLastLink = p;
  }
}

template <class T>
void doubleEndedList<T>::add(T val)
{
  if (this->isEmpty()) {
    list<T>::add(val);
    ptrToLastLink = this->ptrToFirstLink;
  } else {
    list<T>::add(val);
  }
}

template <class T>
void doubleEndedList<T>::addToEnd(T val)
{
  if (ptrToLastLink != nullptr) {
    ptrToLastLink = ptrToLastLink->insert(val);
  } else {
    this->add(val); // empty list case
  }
}

template <class T>
void doubleEndedList<T>::deleteAllValues()
{
  list<T>::deleteAllValues();
  ptrToLastLink = nullptr;
}

template <class T>
void doubleEndedList<T>::removeFirst()
{
  list<T>::removeFirst();
  if (this->isEmpty()) {
    ptrToLastLink = nullptr;
  }
}

