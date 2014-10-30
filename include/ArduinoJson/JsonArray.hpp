// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "ForwardDeclarations.hpp"
#include "JsonArrayIterator.hpp"
#include "JsonArrayConstIterator.hpp"
#include "JsonPrintable.hpp"
#include "JsonObject.hpp"

namespace ArduinoJson {

class JsonArray : public JsonPrintable {
  friend class JsonBuffer;

 public:
  typedef JsonValue value_type;
  typedef JsonArrayIterator iterator;
  typedef JsonArrayConstIterator const_iterator;

  int size() const;

  bool success() { return _buffer != NULL; }

  value_type &operator[](int index) const { return at(index); }
  value_type &at(int index) const;

  template <typename T>
  void add(T value) {
    add().set(value);
  }

  value_type &add();
  void add(double value, int decimals) { add().set(value, decimals); }
  void add(JsonArray &nestedArray) { add().set(nestedArray); }
  void add(JsonObject &nestedObject) { add().set(nestedObject); }

  JsonArray &createNestedArray();
  JsonObject &createNestedObject();

  iterator begin() { return iterator(_firstNode); }
  iterator end() { return iterator(0); }

  const_iterator begin() const { return const_iterator(_firstNode); }
  const_iterator end() const { return const_iterator(0); }

  static JsonArray &invalid() { return _invalid; }

  virtual void writeTo(Internals::JsonWriter &writer) const;

 private:
  // constructor is private: instance must be created via a JsonBuffer
  JsonArray(JsonBuffer *buffer) : _buffer(buffer), _firstNode(NULL) {}

  // copy is forbidden, use a reference instead
  JsonArray(const JsonArray &);
  JsonArray &operator=(const JsonArray &);

  Internals::JsonArrayNode *createNode();
  inline void addNode(Internals::JsonArrayNode *node);

  JsonBuffer *_buffer;
  Internals::JsonArrayNode *_firstNode;
  static JsonArray _invalid;
};

inline bool operator==(const JsonArray &left, const JsonArray &right) {
  // two JsonArray are equal if they are the same instance
  // (we don't compare the content)
  return &left == &right;
}
}
