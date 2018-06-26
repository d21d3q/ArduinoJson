// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonArray.hpp"
#include "JsonArrayRef.hpp"
#include "JsonObject.hpp"
#include "JsonObjectRef.hpp"

namespace ArduinoJson {

template <typename TStringRef>
inline JsonArrayRef JsonObjectRef::createNestedArray_impl(TStringRef key) {
  if (!_object) return JsonArrayRef();
  JsonArrayRef array(_object->_buffer);
  if (array.success()) set(key, array);
  return array;
}

template <typename TStringRef>
inline JsonObjectRef JsonObjectRef::createNestedObject_impl(TStringRef key) {
  if (!_object) return JsonObjectRef();
  JsonObject *object = new (_object->_buffer) JsonObject(_object->_buffer);
  if (object) set(key, object);
  return object;
}
}  // namespace ArduinoJson
