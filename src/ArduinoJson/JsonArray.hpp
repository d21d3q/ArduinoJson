// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Data/List.hpp"
#include "Data/ReferenceType.hpp"
#include "Data/ValueSaver.hpp"
#include "JsonVariant.hpp"
#include "Memory/JsonBufferAllocated.hpp"
#include "Polyfills/type_traits.hpp"
#include "Strings/StringTraits.hpp"

// Returns the size (in bytes) of an array with n elements.
// Can be very handy to determine the size of a StaticJsonBuffer.
#define JSON_ARRAY_SIZE(NUMBER_OF_ELEMENTS) \
  (sizeof(JsonArray) + (NUMBER_OF_ELEMENTS) * sizeof(JsonArray::node_type))

namespace ArduinoJson {

// Forward declarations
class JsonObject;
class JsonBuffer;
namespace Internals {
class JsonArraySubscript;
}

class JsonArray : public Internals::ReferenceType,
                  public Internals::NonCopyable,
                  public Internals::List<JsonVariant>,
                  public Internals::JsonBufferAllocated {
  friend class JsonArrayRef;

 public:
  explicit JsonArray(Internals::JsonBuffer *buf) throw()
      : Internals::List<JsonVariant>(buf) {}

  // Gets the value at the specified index
  const Internals::JsonArraySubscript operator[](size_t index) const;

  // Gets or sets the value at specified index
  Internals::JsonArraySubscript operator[](size_t index);

  // Adds the specified value at the end of the array.
  //
  // bool add(TValue);
  // TValue = bool, long, int, short, float, double, RawJson, JsonVariant,
  //          std::string, String, JsonArray, JsonObject
  template <typename T>
  bool add(const T &value) {
    return add_impl<const T &>(value);
  }
  //
  // bool add(TValue);
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename T>
  bool add(T *value) {
    return add_impl<T *>(value);
  }

  // Sets the value at specified index.
  //
  // bool add(size_t index, const TValue&);
  // TValue = bool, long, int, short, float, double, RawJson, JsonVariant,
  //          std::string, String, JsonArray, JsonObject
  template <typename T>
  bool set(size_t index, const T &value) {
    return set_impl<const T &>(index, value);
  }
  //
  // bool add(size_t index, TValue);
  // TValue = char*, const char*, const FlashStringHelper*
  template <typename T>
  bool set(size_t index, T *value) {
    return set_impl<T *>(index, value);
  }

  // Gets the value at the specified index.
  template <typename T>
  typename Internals::JsonVariantAs<T>::type get(size_t index) const {
    const_iterator it = begin() += index;
    return it != end() ? it->as<T>() : Internals::JsonVariantDefault<T>::get();
  }

  // Check the type of the value at specified index.
  template <typename T>
  bool is(size_t index) const {
    const_iterator it = begin() += index;
    return it != end() ? it->is<T>() : false;
  }

  // Creates a JsonArray and adds a reference at the end of the array.
  JsonArray &createNestedArray();

  // Creates a JsonObject and adds a reference at the end of the array.
  JsonObject &createNestedObject();

  // Removes element at specified index.
  void remove(size_t index) {
    remove(begin() += index);
  }
  using Internals::List<JsonVariant>::remove;

  // Returns a reference an invalid JsonArray.
  // This object is meant to replace a NULL pointer.
  // This is used when memory allocation or JSON parsing fail.
  static JsonArray &invalid() {
    static JsonArray instance(NULL);
    return instance;
  }

  // Imports a 1D array
  template <typename T, size_t N>
  bool copyFrom(T (&array)[N]) {
    return copyFrom(array, N);
  }

  // Imports a 1D array
  template <typename T>
  bool copyFrom(T *array, size_t len) {
    bool ok = true;
    for (size_t i = 0; i < len; i++) {
      ok &= add(array[i]);
    }
    return ok;
  }

  // Imports a 2D array
  template <typename T, size_t N1, size_t N2>
  bool copyFrom(T (&array)[N1][N2]) {
    bool ok = true;
    for (size_t i = 0; i < N1; i++) {
      JsonArray &nestedArray = createNestedArray();
      for (size_t j = 0; j < N2; j++) {
        ok &= nestedArray.add(array[i][j]);
      }
    }
    return ok;
  }

  template <typename Visitor>
  void visit(Visitor &visitor) const {
    return visitor.acceptArray(*this);
  }

 private:
  template <typename TValueRef>
  bool set_impl(size_t index, TValueRef value) {
    iterator it = begin() += index;
    if (it == end()) return false;
    return Internals::ValueSaver<TValueRef>::save(_buffer, *it, value);
  }

  template <typename TValueRef>
  bool add_impl(TValueRef value) {
    iterator it = Internals::List<JsonVariant>::add();
    if (it == end()) return false;
    return Internals::ValueSaver<TValueRef>::save(_buffer, *it, value);
  }
};
}  // namespace ArduinoJson
