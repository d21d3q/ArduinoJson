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

  const Internals::JsonArraySubscript operator[](size_t index) const {
    return _array->operator[](index);
  }

 private:
  JsonArray* _array;
};
}  // namespace ArduinoJson
