// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonArray.hpp"
#include "JsonObject.hpp"

namespace ArduinoJson {

template <typename TString>
inline JsonArray JsonObject::createNestedArray(const TString& key) {
  return createNestedArray_impl<const TString&>(key);
}

template <typename TString>
inline JsonArray JsonObject::createNestedArray(TString* key) {
  return createNestedArray_impl<TString*>(key);
}

template <typename TStringRef>
inline JsonArray JsonObject::createNestedArray_impl(TStringRef key) {
  if (!_object) return JsonArray();
  JsonArray array(_object->_buffer);
  if (array.success()) set(key, array);
  return array;
}

template <typename TStringRef>
inline JsonObject JsonObject::createNestedObject_impl(TStringRef key) {
  if (!_object) return JsonObject();
  JsonObject object(_object->_buffer);
  if (object.success()) set(key, object);
  return object;
}
}  // namespace ArduinoJson
