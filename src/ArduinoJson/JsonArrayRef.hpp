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

 private:
  JsonArray* _array;
};
}  // namespace ArduinoJson
