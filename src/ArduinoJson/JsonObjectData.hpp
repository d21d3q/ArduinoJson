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
#define JSON_OBJECT_SIZE(NUMBER_OF_ELEMENTS)        \
  (sizeof(ArduinoJson::Internals::JsonObjectData) + \
   (NUMBER_OF_ELEMENTS) *                           \
       sizeof(ArduinoJson::Internals::JsonObjectData::node_type))

namespace ArduinoJson {
namespace Internals {
struct JsonObjectData : Internals::ReferenceType,
                        Internals::NonCopyable,
                        Internals::List<JsonPair>,
                        Internals::JsonBufferAllocated {
  // Create an empty JsonArray attached to the specified JsonBuffer.
  // You should not use this constructor directly.
  explicit JsonObjectData(Internals::JsonBuffer* buf) throw()
      : Internals::List<JsonPair>(buf) {}
};
}  // namespace Internals
}  // namespace ArduinoJson
