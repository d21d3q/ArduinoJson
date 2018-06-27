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
  (sizeof(ArduinoJson::JsonArray) +         \
   (NUMBER_OF_ELEMENTS) * sizeof(ArduinoJson::JsonArray::node_type))

namespace ArduinoJson {

namespace Internals {
class JsonBuffer;
}

class JsonArray : public Internals::ReferenceType,
                  public Internals::NonCopyable,
                  public Internals::List<JsonVariant>,
                  public Internals::JsonBufferAllocated {
  friend class JsonArrayRef;

 public:
  explicit JsonArray(Internals::JsonBuffer *buf) throw()
      : Internals::List<JsonVariant>(buf) {}
};
}  // namespace ArduinoJson
