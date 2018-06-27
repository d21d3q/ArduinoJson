// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonArray.hpp"
#include "JsonObjectRef.hpp"

namespace ArduinoJson {

inline JsonArray JsonArray::createNestedArray() {
  if (!_array) return JsonArray();
  JsonArray array(_array->_buffer);
  if (array.success()) add(array);
  return array;
}

inline JsonObjectRef JsonArray::createNestedObject() {
  if (!_array) return JsonObjectRef();
  JsonObjectRef object(_array->_buffer);
  if (object.success()) add(object);
  return object;
}
}  // namespace ArduinoJson
