// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Data/List.hpp"
#include "Data/ReferenceType.hpp"
#include "Data/ValueSaver.hpp"
#include "JsonPair.hpp"
#include "Memory/JsonBufferAllocated.hpp"
#include "Polyfills/type_traits.hpp"
#include "Strings/StringTraits.hpp"

// Returns the size (in bytes) of an object with n elements.
// Can be very handy to determine the size of a StaticJsonBuffer.
#define JSON_OBJECT_SIZE(NUMBER_OF_ELEMENTS) \
  (sizeof(ArduinoJson::JsonObject) +         \
   (NUMBER_OF_ELEMENTS) * sizeof(ArduinoJson::JsonObject::node_type))

namespace ArduinoJson {

// Forward declarations
namespace Internals {
class JsonBuffer;
}  // namespace Internals

class JsonObject : public Internals::ReferenceType,
                   public Internals::NonCopyable,
                   public Internals::List<JsonPair>,
                   public Internals::JsonBufferAllocated {
  friend class JsonObjectRef;

 public:
  // Create an empty JsonArray attached to the specified JsonBuffer.
  // You should not use this constructor directly.
  explicit JsonObject(Internals::JsonBuffer* buf) throw()
      : Internals::List<JsonPair>(buf) {}

  // Tells weither the specified key is present and associated with a value.
  //
  // bool containsKey(TKey);
  // TKey = const std::string&, const String&
  template <typename TString>
  bool containsKey(const TString& key) const {
    return findKey<const TString&>(key) != end();
  }
  //
  // bool containsKey(TKey);
  // TKey = char*, const char*, char[], const char[], const FlashStringHelper*
  template <typename TString>
  bool containsKey(TString* key) const {
    return findKey<TString*>(key) != end();
  }

  // Removes the specified key and the associated value.
  //
  // void remove(TKey);
  // TKey = const std::string&, const String&
  template <typename TString>
  void remove(const TString& key) {
    remove(findKey<const TString&>(key));
  }
  //
  // void remove(TKey);
  // TKey = char*, const char*, char[], const char[], const FlashStringHelper*
  template <typename TString>
  void remove(TString* key) {
    remove(findKey<TString*>(key));
  }
  //
  // void remove(iterator)
  using Internals::List<JsonPair>::remove;

 private:
  // Returns the list node that matches the specified key.
  template <typename TStringRef>
  iterator findKey(TStringRef key) {
    iterator it;
    for (it = begin(); it != end(); ++it) {
      if (Internals::StringTraits<TStringRef>::equals(key, it->key)) break;
    }
    return it;
  }
  template <typename TStringRef>
  const_iterator findKey(TStringRef key) const {
    return const_cast<JsonObject*>(this)->findKey<TStringRef>(key);
  }
};
}  // namespace ArduinoJson
