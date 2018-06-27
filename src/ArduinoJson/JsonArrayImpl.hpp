// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonArrayRef.hpp"
#include "JsonObjectRef.hpp"

namespace ArduinoJson {

inline JsonArrayRef JsonArrayRef::createNestedArray() {
  if (!_array) return JsonArrayRef();
  JsonArrayRef array(_array->_buffer);
  if (array.success()) add(array);
  return array;
}

inline JsonObjectRef JsonArrayRef::createNestedObject() {
  if (!_array) return JsonObjectRef();
  JsonObjectRef object(_array->_buffer);
  if (object.success()) add(object);
  return object;
}
}  // namespace ArduinoJson
