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

  template <typename TKey>
  JsonArrayRef createNestedArray(const TKey& key) {
    return _object->createNestedArray(key);
  }

  template <typename TKey>
  JsonObjectRef createNestedObject(const TKey& key) {
    return _object->createNestedObject(key);
  }

  template <typename TValue, typename TString>
  typename Internals::JsonVariantAs<TValue>::type get(
      const TString& key) const {
    return _object->get<TValue>(key);
  }

  // Gets or sets the value associated with the specified key.
  //
  // JsonObjectSubscript operator[](TKey)
  // TKey = const std::string&, const String&
  template <typename TString>
  Internals::JsonObjectSubscript<const TString&> operator[](
      const TString& key) {
    return _object->operator[](key);
  }
  //
  // JsonObjectSubscript operator[](TKey)
  // TKey = char*, const char*, char[], const char[N], const FlashStringHelper*
  template <typename TString>
  Internals::JsonObjectSubscript<TString*> operator[](TString* key) {
    return _object->operator[](key);
  }

  // Gets the value associated with the specified key.
  //
  // const JsonObjectSubscript operator[](TKey) const;
  // TKey = const std::string&, const String&
  template <typename TString>
  const Internals::JsonObjectSubscript<const TString&> operator[](
      const TString& key) const {
    return _object->operator[](key);
  }
  //
  // const JsonObjectSubscript operator[](TKey) const;
  // TKey = const char*, const char[N], const FlashStringHelper*
  template <typename TString>
  const Internals::JsonObjectSubscript<TString*> operator[](
      TString* key) const {
    return _object->operator[](key);
  }

  bool operator==(const JsonObjectRef& rhs) const {
    return _object == rhs._object;
  }

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

  size_t size() const {
    return _object->size();
  }

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

inline JsonVariant::JsonVariant(JsonObjectRef object) {
  _content.asObject = object._object;
  _type = Internals::JSON_OBJECT;
}
}  // namespace ArduinoJson
