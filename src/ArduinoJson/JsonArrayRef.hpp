// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "./JsonArray.hpp"

namespace ArduinoJson {

class JsonArrayRef {
 public:
  JsonArrayRef(JsonArray& arr) : _array(&arr) {}

  template <typename T>
  bool add(const T& value) {
    return _array->add(value);
  }

  JsonArray::iterator begin() {
    return _array->begin();
  }

  JsonArray::const_iterator begin() const {
    return _array->begin();
  }

  JsonArray::iterator end() {
    return _array->end();
  }

  JsonArray::const_iterator end() const {
    return _array->end();
  }

  template <typename T, size_t N>
  bool copyFrom(T (&array)[N]) {
    return _array->copyFrom(array, N);
  }

  template <typename T>
  bool copyFrom(T* array, size_t len) {
    return _array->copyFrom(array, len);
  }

  template <typename T, size_t N1, size_t N2>
  bool copyFrom(T (&array)[N1][N2]) {
    return _array->copyFrom(array);
  }

  template <typename T, size_t N>
  size_t copyTo(T (&array)[N]) const {
    return _array->copyTo(array, N);
  }

  template <typename T>
  size_t copyTo(T* array, size_t len) const {
    return _array->copyTo(array, len);
  }

  // Exports a 2D array
  template <typename T, size_t N1, size_t N2>
  void copyTo(T (&array)[N1][N2]) const {
    return _array->copyTo(array);
  }

  JsonArrayRef createNestedArray() {
    return _array->createNestedArray();
  }

  JsonObject& createNestedObject() {
    return _array->createNestedObject();
  }

  const Internals::JsonArraySubscript operator[](size_t index) const {
    return _array->operator[](index);
  }

  bool operator==(const JsonArrayRef& rhs) const {
    return _array == rhs._array;
  }

  size_t size() const {
    return _array->size();
  }

  bool success() const {
    return _array->success();
  }

  template <typename Visitor>
  void visit(Visitor& visitor) const {
    return _array->visit(visitor);
  }

 private:
  JsonArray* _array;
};
}  // namespace ArduinoJson
