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

  JsonObjectRef() : _object(0) {}
  JsonObjectRef(JsonObject& object) : _object(&object) {}
  JsonObjectRef(JsonObject* object) : _object(object) {}

  iterator begin() {
    if (!_object) return iterator();
    return _object->begin();
  }

  const_iterator begin() const {
    if (!_object) return const_iterator();
    return _object->begin();
  }

  // Tells weither the specified key is present and associated with a value.
  //
  // bool containsKey(TKey);
  // TKey = const std::string&, const String&
  template <typename TString>
  bool containsKey(const TString& key) const {
    if (!_object) return false;
    return _object->containsKey(key);
  }
  //
  // bool containsKey(TKey);
  // TKey = char*, const char*, char[], const char[], const FlashStringHelper*
  template <typename TString>
  bool containsKey(TString* key) const {
    if (!_object) return false;
    return _object->containsKey(key);
  }

  iterator end() {
    if (!_object) return iterator();
    return _object->end();
  }

  const_iterator end() const {
    if (!_object) return const_iterator();
    return _object->end();
  }

  // Creates and adds a JsonArray.
  //
  // JsonArray& createNestedArray(TKey);
  // TKey = const std::string&, const String&
  template <typename TString>
  JsonArrayRef createNestedArray(const TString& key) {
    if (!_object) return JsonArrayRef();
    return _object->createNestedArray_impl<const TString&>(key);
  }
  // JsonArray& createNestedArray(TKey);
  // TKey = char*, const char*, char[], const char[], const FlashStringHelper*
  template <typename TString>
  JsonArrayRef createNestedArray(TString* key) {
    if (!_object) return JsonArrayRef();
    return _object->createNestedArray_impl<TString*>(key);
  }

  // Creates and adds a JsonObject.
  //
  // JsonObject& createNestedObject(TKey);
  // TKey = const std::string&, const String&
  template <typename TString>
  JsonObjectRef createNestedObject(const TString& key) {
    if (!_object) return JsonObjectRef();
    return _object->createNestedObject_impl<const TString&>(key);
  }
  //
  // JsonObject& createNestedObject(TKey);
  // TKey = char*, const char*, char[], const char[], const FlashStringHelper*
  template <typename TString>
  JsonObjectRef createNestedObject(TString* key) {
    if (!_object) return JsonObjectRef();
    return _object->createNestedObject_impl<TString*>(key);
  }

  // Gets the value associated with the specified key.
  //
  // TValue get<TValue>(TKey) const;
  // TKey = const std::string&, const String&
  // TValue = bool, char, long, int, short, float, double,
  //          std::string, String, JsonArray, JsonObject
  template <typename TValue, typename TString>
  typename Internals::JsonVariantAs<TValue>::type get(
      const TString& key) const {
    if (!_object) return Internals::JsonVariantDefault<TValue>::get();
    return _object->get_impl<const TString&, TValue>(key);
  }
  //
  // TValue get<TValue>(TKey) const;
  // TKey = char*, const char*, const FlashStringHelper*
  // TValue = bool, char, long, int, short, float, double,
  //          std::string, String, JsonArray, JsonObject
  template <typename TValue, typename TString>
  typename Internals::JsonVariantAs<TValue>::type get(TString* key) const {
    if (!_object) return Internals::JsonVariantDefault<TValue>::get();
    return _object->get_impl<TString*, TValue>(key);
  }

  // Checks the type of the value associated with the specified key.
  //
  //
  // bool is<TValue>(TKey) const;
  // TKey = const std::string&, const String&
  // TValue = bool, char, long, int, short, float, double,
  //          std::string, String, JsonArray, JsonObject
  template <typename TValue, typename TString>
  bool is(const TString& key) const {
    if (!_object) return false;
    return _object->is_impl<const TString&, TValue>(key);
  }
  //
  // bool is<TValue>(TKey) const;
  // TKey = char*, const char*, const FlashStringHelper*
  // TValue = bool, char, long, int, short, float, double,
  //          std::string, String, JsonArray, JsonObject
  template <typename TValue, typename TString>
  bool is(TString* key) const {
    if (!_object) return false;
    return _object->is_impl<TString*, TValue>(key);
  }

  // Gets or sets the value associated with the specified key.
  //
  // JsonObjectSubscript operator[](TKey)
  // TKey = const std::string&, const String&
  template <typename TString>
  Internals::JsonObjectSubscript<const TString&> operator[](
      const TString& key) {
    return Internals::JsonObjectSubscript<const TString&>(*this, key);
  }
  //
  // JsonObjectSubscript operator[](TKey)
  // TKey = char*, const char*, char[], const char[N], const FlashStringHelper*
  template <typename TString>
  Internals::JsonObjectSubscript<TString*> operator[](TString* key) {
    return Internals::JsonObjectSubscript<TString*>(*this, key);
  }

  // Gets the value associated with the specified key.
  //
  // const JsonObjectSubscript operator[](TKey) const;
  // TKey = const std::string&, const String&
  template <typename TString>
  const Internals::JsonObjectSubscript<const TString&> operator[](
      const TString& key) const {
    return Internals::JsonObjectSubscript<const TString&>(*this, key);
  }
  //
  // const JsonObjectSubscript operator[](TKey) const;
  // TKey = const char*, const char[N], const FlashStringHelper*
  template <typename TString>
  const Internals::JsonObjectSubscript<TString*> operator[](
      TString* key) const {
    return Internals::JsonObjectSubscript<TString*>(*this, key);
  }

  bool operator==(const JsonObjectRef& rhs) const {
    return _object == rhs._object;
  }

  void remove(iterator it) {
    if (!_object) return;
    _object->remove(it);
  }

  // Removes the specified key and the associated value.
  //
  // void remove(TKey);
  // TKey = const std::string&, const String&
  template <typename TString>
  void remove(const TString& key) {
    if (!_object) return;
    _object->remove(key);
  }
  //
  // void remove(TKey);
  // TKey = char*, const char*, char[], const char[], const FlashStringHelper*
  template <typename TString>
  void remove(TString* key) {
    if (!_object) return;
    _object->remove(key);
  }

  // Sets the specified key with the specified value.
  //
  // bool set(TKey, TValue);
  // TKey = const std::string&, const String&
  // TValue = bool, long, int, short, float, double, RawJson, JsonVariant,
  //          std::string, String, JsonArray, JsonObject
  template <typename TValue, typename TString>
  bool set(const TString& key, const TValue& value) {
    if (!_object) return false;
    return _object->set_impl<const TString&, const TValue&>(key, value);
  }
  //
  // bool set(TKey, TValue);
  // TKey = const std::string&, const String&
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename TValue, typename TString>
  bool set(const TString& key, TValue* value) {
    if (!_object) return false;
    return _object->set_impl<const TString&, TValue*>(key, value);
  }
  //
  // bool set(TKey, const TValue&);
  // TKey = char*, const char*, const FlashStringHelper*
  // TValue = bool, long, int, short, float, double, RawJson, JsonVariant,
  //          std::string, String, JsonArray, JsonObject
  template <typename TValue, typename TString>
  bool set(TString* key, const TValue& value) {
    if (!_object) return false;
    return _object->set_impl<TString*, const TValue&>(key, value);
  }
  //
  // bool set(TKey, TValue);
  // TKey = char*, const char*, const FlashStringHelper*
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename TValue, typename TString>
  bool set(TString* key, TValue* value) {
    if (!_object) return false;
    return _object->set_impl<TString*, TValue*>(key, value);
  }

  size_t size() const {
    if (!_object) return 0;
    return _object->size();
  }

  bool success() const {
    return _object != 0;
  }

  template <typename Visitor>
  void visit(Visitor& visitor) const {
    if (_object)
      visitor.acceptObject(*this);
    else
      return visitor.acceptUndefined();
  }

 private:
  JsonObject* _object;
};
}  // namespace ArduinoJson
