// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonArray.hpp"
#include "JsonArrayRef.hpp"
#include "JsonObject.hpp"
#include "JsonObjectSubscript.hpp"

namespace ArduinoJson {

template <typename TStringRef>
inline JsonArray *JsonObject::createNestedArray_impl(TStringRef key) {
  JsonArray *array = new (_buffer) JsonArray(_buffer);
  if (array) set(key, array);
  return array;
}

template <typename TStringRef>
inline JsonObject *JsonObject::createNestedObject_impl(TStringRef key) {
  JsonObject *object = new (_buffer) JsonObject(_buffer);
  if (object) set(key, object);
  return object;
}
}  // namespace ArduinoJson
