// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "Configuration.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonVariant.hpp"
#include "Numbers/isFloat.hpp"
#include "Numbers/isInteger.hpp"
#include "Numbers/parseFloat.hpp"
#include "Numbers/parseInteger.hpp"

#include <string.h>  // for strcmp

namespace ArduinoJson {

inline JsonVariant::JsonVariant(JsonArrayRef array) {
  if (array.success()) {
    _type = Internals::JSON_ARRAY;
    _content.asArray = array._array;
  } else {
    _type = Internals::JSON_UNDEFINED;
  }
}

inline JsonVariant::JsonVariant(JsonObjectRef object) {
  if (object.success()) {
    _type = Internals::JSON_OBJECT;
    _content.asObject = object._object;
  } else {
    _type = Internals::JSON_UNDEFINED;
  }
}

inline JsonArrayRef JsonVariant::variantAsArray() const {
  if (_type == Internals::JSON_ARRAY) return *_content.asArray;
  return JsonArrayRef();
}

inline JsonObjectRef JsonVariant::variantAsObject() const {
  if (_type == Internals::JSON_OBJECT) return *_content.asObject;
  return JsonObjectRef();
}

template <typename T>
inline T JsonVariant::variantAsInteger() const {
  using namespace Internals;
  switch (_type) {
    case JSON_UNDEFINED:
      return 0;
    case JSON_POSITIVE_INTEGER:
    case JSON_BOOLEAN:
      return T(_content.asInteger);
    case JSON_NEGATIVE_INTEGER:
      return T(~_content.asInteger + 1);
    case JSON_STRING:
    case JSON_UNPARSED:
      return parseInteger<T>(_content.asString);
    default:
      return T(_content.asFloat);
  }
}

inline const char *JsonVariant::variantAsString() const {
  using namespace Internals;
  if (_type == JSON_UNPARSED && _content.asString &&
      !strcmp("null", _content.asString))
    return NULL;
  if (_type == JSON_STRING || _type == JSON_UNPARSED) return _content.asString;
  return NULL;
}

template <typename T>
inline T JsonVariant::variantAsFloat() const {
  using namespace Internals;
  switch (_type) {
    case JSON_UNDEFINED:
      return 0;
    case JSON_POSITIVE_INTEGER:
    case JSON_BOOLEAN:
      return static_cast<T>(_content.asInteger);
    case JSON_NEGATIVE_INTEGER:
      return -static_cast<T>(_content.asInteger);
    case JSON_STRING:
    case JSON_UNPARSED:
      return parseFloat<T>(_content.asString);
    default:
      return static_cast<T>(_content.asFloat);
  }
}

inline bool JsonVariant::variantIsBoolean() const {
  using namespace Internals;
  if (_type == JSON_BOOLEAN) return true;

  if (_type != JSON_UNPARSED || _content.asString == NULL) return false;

  return !strcmp(_content.asString, "true") ||
         !strcmp(_content.asString, "false");
}

inline bool JsonVariant::variantIsInteger() const {
  using namespace Internals;

  return _type == JSON_POSITIVE_INTEGER || _type == JSON_NEGATIVE_INTEGER ||
         (_type == JSON_UNPARSED && isInteger(_content.asString));
}

inline bool JsonVariant::variantIsFloat() const {
  using namespace Internals;

  return _type == JSON_FLOAT || _type == JSON_POSITIVE_INTEGER ||
         _type == JSON_NEGATIVE_INTEGER ||
         (_type == JSON_UNPARSED && isFloat(_content.asString));
}

}  // namespace ArduinoJson
