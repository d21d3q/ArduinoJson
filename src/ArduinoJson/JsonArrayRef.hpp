// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "./JsonArray.hpp"
#include "JsonArraySubscript.hpp"

namespace ArduinoJson {

class JsonObjectRef;

class JsonArrayRef {
  friend class JsonVariant;

 public:
  typedef JsonArray::iterator iterator;
  typedef JsonArray::const_iterator const_iterator;

  JsonArrayRef() : _array(0) {}
  JsonArrayRef(JsonArray& arr) : _array(&arr) {}

  // Adds the specified value at the end of the array.
  //
  // bool add(TValue);
  // TValue = bool, long, int, short, float, double, RawJson, JsonVariant,
  //          std::string, String, JsonArray, JsonObject
  template <typename T>
  bool add(const T& value) {
    if (!_array) return false;
    return _array->add_impl<const T&>(value);
  }
  //
  // bool add(TValue);
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename T>
  bool add(T* value) {
    if (!_array) return false;
    return _array->add_impl<T*>(value);
  }

  iterator begin() {
    if (!_array) return iterator();
    return _array->begin();
  }

  const_iterator begin() const {
    if (!_array) return const_iterator();
    return _array->begin();
  }

  iterator end() {
    if (!_array) return iterator();
    return _array->end();
  }

  const_iterator end() const {
    if (!_array) return const_iterator();
    return _array->end();
  }

  template <typename T, size_t N>
  bool copyFrom(T (&array)[N]) {
    if (!_array) return false;
    return _array->copyFrom(array, N);
  }

  template <typename T>
  bool copyFrom(T* array, size_t len) {
    if (!_array) return false;
    return _array->copyFrom(array, len);
  }

  template <typename T, size_t N1, size_t N2>
  bool copyFrom(T (&array)[N1][N2]) {
    if (!_array) return false;
    return _array->copyFrom(array);
  }

  template <typename T, size_t N>
  size_t copyTo(T (&array)[N]) const {
    if (!_array) return 0;
    return _array->copyTo(array, N);
  }

  template <typename T>
  size_t copyTo(T* array, size_t len) const {
    if (!_array) return 0;
    return _array->copyTo(array, len);
  }

  // Exports a 2D array
  template <typename T, size_t N1, size_t N2>
  void copyTo(T (&array)[N1][N2]) const {
    if (!_array) return;
    size_t i = 0;
    for (const_iterator it = begin(); it != end() && i < N1; ++it) {
      it->as<JsonArrayRef>().copyTo(array[i++]);
    }
  }

  JsonArrayRef createNestedArray() {
    if (!_array) return JsonArrayRef();
    return _array->createNestedArray();
  }

  JsonObjectRef createNestedObject();

  const Internals::JsonArraySubscript operator[](size_t index) const {
    if (!_array) return Internals::JsonArraySubscript(JsonArray::invalid(), 0);
    return _array->operator[](index);
  }

  Internals::JsonArraySubscript operator[](size_t index) {
    if (!_array) return Internals::JsonArraySubscript(JsonArray::invalid(), 0);
    return _array->operator[](index);
  }

  bool operator==(const JsonArrayRef& rhs) const {
    return _array == rhs._array;
  }

  void remove(iterator it) {
    if (!_array) return;
    _array->remove(it);
  }

  void remove(size_t index) {
    if (!_array) return;
    _array->remove(index);
  }

  // Sets the value at specified index.
  //
  // bool add(size_t index, const TValue&);
  // TValue = bool, long, int, short, float, double, RawJson, JsonVariant,
  //          std::string, String, JsonArray, JsonObject
  template <typename T>
  bool set(size_t index, const T& value) {
    if (!_array) return false;
    return _array->set_impl<const T&>(index, value);
  }
  //
  // bool add(size_t index, TValue);
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename T>
  bool set(size_t index, T* value) {
    if (!_array) return false;
    return _array->set_impl<T*>(index, value);
  }

  size_t size() const {
    if (!_array) return 0;
    return _array->size();
  }

  bool success() const {
    return _array;
  }

  template <typename Visitor>
  void visit(Visitor& visitor) const {
    if (!_array) return;
    return _array->visit(visitor);
  }

 private:
  JsonArray* _array;
};
}  // namespace ArduinoJson
