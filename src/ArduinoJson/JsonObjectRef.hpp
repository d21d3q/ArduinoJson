// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "./JsonObject.hpp"

namespace ArduinoJson {

class JsonObjectRef {
  friend class JsonVariant;

 public:
  typedef JsonObject::iterator iterator;
  typedef JsonObject::const_iterator const_iterator;

  JsonObjectRef(JsonObject& arr) : _object(&arr) {}

  iterator begin() {
    return _object->begin();
  }

  const_iterator begin() const {
    return _object->begin();
  }

  template <typename T>
  bool containsKey(const T& key) const {
    return _object->containsKey(key);
  }

  iterator end() {
    return _object->end();
  }

  const_iterator end() const {
    return _object->end();
  }

  // JsonObjectRef createNestedObject() {
  //   return _object->createNestedObject();
  // }

  // JsonObject& createNestedObject() {
  //   return _object->createNestedObject();
  // }

  template <typename TValue, typename TString>
  typename Internals::JsonVariantAs<TValue>::type get(
      const TString& key) const {
    return _object->get<TValue>(key);
  }

  // const Internals::JsonObjectSubscript operator[](size_t index) const {
  //   return _object->operator[](index);
  // }

  // Internals::JsonObjectSubscript operator[](size_t index) {
  //   return _object->operator[](index);
  // }

  // bool operator==(const JsonObjectRef& rhs) const {
  //   return _object == rhs._object;
  // }

  void remove(iterator it) {
    _object->remove(it);
  }

  template <typename TKey>
  void remove(const TKey& key) {
    _object->remove(key);
  }

  template <typename TKey, typename TValue>
  bool set(const TKey& key, const TValue& value) {
    return _object->set(key, value);
  }

  // size_t size() const {
  //   return _object->size();
  // }

  bool success() const {
    return _object->success();
  }

  template <typename Visitor>
  void visit(Visitor& visitor) const {
    return _object->visit(visitor);
  }

 private:
  JsonObject* _object;
};

// inline JsonVariant::JsonVariant(JsonObjectRef Object) {
//   _content.asObject = Object._object;
//   _type = Internals::JSON_Object;
// }
}  // namespace ArduinoJson
