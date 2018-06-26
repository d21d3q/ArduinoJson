// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "JsonVariant.hpp"
#include "Memory/StaticJsonBuffer.hpp"

namespace ArduinoJson {

template <size_t CAPACITY = sizeof(JsonVariant)>
class StaticJsonDocument {
  Internals::StaticJsonBuffer<CAPACITY> _buffer;
  JsonVariant _root;

 public:
  uint8_t nestingLimit;

  StaticJsonDocument() : nestingLimit(ARDUINOJSON_DEFAULT_NESTING_LIMIT) {}

  Internals::StaticJsonBufferBase& buffer() {
    return _buffer;
  }

  template <typename T>
  bool is() const {
    return _root.is<T>();
  }

  template <typename T>
  typename Internals::JsonVariantAs<T>::type as() const {
    return _root.as<T>();
  }

  // JsonObjectRef to<JsonObjectRef>()
  template <typename T>
  typename Internals::enable_if<Internals::is_same<T, JsonObjectRef>::value,
                                JsonObjectRef>::type
  to() {
    clear();
    JsonObjectRef object(&_buffer);
    _root = object;
    return object;
  }

  // JsonArrayRef to<JsonArrayRef>()
  template <typename T>
  typename Internals::enable_if<Internals::is_same<T, JsonArrayRef>::value,
                                JsonArrayRef>::type
  to() {
    clear();
    JsonArrayRef array(&_buffer);
    _root = array;
    return array;
  }

  // JsonVariant to<JsonVariant>()
  template <typename T>
  typename Internals::enable_if<Internals::is_same<T, JsonVariant>::value,
                                T&>::type
  to() {
    clear();
    return _root;
  }

  void clear() {
    _buffer.clear();
    _root = JsonVariant();
  }

  size_t memoryUsage() const {
    return _buffer.size();
  }

  template <typename Visitor>
  void visit(Visitor& visitor) const {
    return _root.visit(visitor);
  }
};

}  // namespace ArduinoJson
