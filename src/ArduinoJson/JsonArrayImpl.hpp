// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonArray.hpp"
#include "JsonArrayRef.hpp"
#include "JsonObject.hpp"
#include "JsonObjectRef.hpp"

namespace ArduinoJson {

inline JsonArray &JsonArray::createNestedArray() {
  JsonArray *array = new (_buffer) JsonArray(_buffer);
  if (!array) return JsonArray::invalid();

  add(array);
  return *array;
}

inline JsonObjectRef JsonArrayRef::createNestedObject() {
  if (!_array) return JsonObjectRef();
  return _array->createNestedObject();
}

inline JsonObject &JsonArray::createNestedObject() {
  JsonObject *object = new (_buffer) JsonObject(_buffer);
  if (!object) return JsonObject::invalid();

  add(object);
  return *object;
}
}  // namespace ArduinoJson
