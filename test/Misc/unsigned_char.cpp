// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

#if defined(__clang__)
#define CONFLICTS_WITH_BUILTIN_OPERATOR
#endif

TEST_CASE("unsigned char[]") {
  SECTION("deserializeJson()") {
    unsigned char input[] = "{\"a\":42}";

    StaticJsonDocument<JSON_OBJECT_SIZE(1)> doc;
    DeserializationError err = deserializeJson(doc, input);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("deserializeMsgPack()") {
    unsigned char input[] = "\xDE\x00\x01\xA5Hello\xA5world";

    StaticJsonDocument<JSON_OBJECT_SIZE(2)> doc;
    DeserializationError err = deserializeMsgPack(doc, input);

    REQUIRE(err == DeserializationError::Ok);
  }

  SECTION("JsonVariant") {
    SECTION("constructor") {
      unsigned char value[] = "42";

      JsonVariant variant(value);

      REQUIRE(42 == variant.as<int>());
    }

    SECTION("operator=") {
      unsigned char value[] = "42";

      JsonVariant variant(666);
      variant = value;

      REQUIRE(42 == variant.as<int>());
    }

#ifndef CONFLICTS_WITH_BUILTIN_OPERATOR
    SECTION("operator[]") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");
      JsonVariant variant = doc.as<JsonVariant>();

      REQUIRE(std::string("world") == variant[key]);
    }
#endif

#ifndef CONFLICTS_WITH_BUILTIN_OPERATOR
    SECTION("operator[] const") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");
      const JsonVariant variant = doc.as<JsonVariant>();

      REQUIRE(std::string("world") == variant[key]);
    }
#endif

    SECTION("operator==") {
      unsigned char comparand[] = "hello";

      JsonVariant variant;
      variant = "hello";

      REQUIRE(comparand == variant);
      REQUIRE(variant == comparand);
      REQUIRE_FALSE(comparand != variant);
      REQUIRE_FALSE(variant != comparand);
    }

    SECTION("operator!=") {
      unsigned char comparand[] = "hello";

      JsonVariant variant;
      variant = "world";

      REQUIRE(comparand != variant);
      REQUIRE(variant != comparand);
      REQUIRE_FALSE(comparand == variant);
      REQUIRE_FALSE(variant == comparand);
    }
  }

  SECTION("JsonObject") {
#ifndef CONFLICTS_WITH_BUILTIN_OPERATOR
    SECTION("operator[]") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj[key] = "world";

      REQUIRE(std::string("world") == obj["hello"]);
    }

    SECTION("JsonObject::operator[] const") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");

      JsonObjectRef obj = doc.as<JsonObjectRef>();
      REQUIRE(std::string("world") == obj[key]);
    }
#endif

    SECTION("get()") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");
      JsonObjectRef obj = doc.as<JsonObjectRef>();
      REQUIRE(std::string("world") == obj.get<char*>(key));
    }

    SECTION("set() key") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj.set(key, "world");

      REQUIRE(std::string("world") == obj["hello"]);
    }

    SECTION("set() value") {
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj.set("hello", value);

      REQUIRE(std::string("world") == obj["hello"]);
    }

    SECTION("set() key&value") {
      unsigned char key[] = "world";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj.set(key, key);

      REQUIRE(std::string("world") == obj["world"]);
    }

    SECTION("containsKey()") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");
      JsonObjectRef obj = doc.as<JsonObjectRef>();
      REQUIRE(true == obj.containsKey(key));
    }

    SECTION("remove()") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":\"world\"}");
      JsonObjectRef obj = doc.as<JsonObjectRef>();
      obj.remove(key);

      REQUIRE(0 == obj.size());
    }

    SECTION("is()") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      deserializeJson(doc, "{\"hello\":42}");
      JsonObjectRef obj = doc.as<JsonObjectRef>();

      REQUIRE(true == obj.is<int>(key));
    }

    SECTION("createNestedArray()") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj.createNestedArray(key);
    }

    SECTION("createNestedObject()") {
      unsigned char key[] = "hello";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj.createNestedObject(key);
    }
  }

  SECTION("JsonObjectSubscript") {
    SECTION("operator=") {  // issue #416
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj["hello"] = value;

      REQUIRE(std::string("world") == obj["hello"]);
    }

    SECTION("set()") {
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonObjectRef obj = doc.to<JsonObjectRef>();
      obj["hello"].set(value);

      REQUIRE(std::string("world") == obj["hello"]);
    }
  }

  SECTION("JsonArray") {
    SECTION("add()") {
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonArrayRef arr = doc.to<JsonArrayRef>();
      arr.add(value);

      REQUIRE(std::string("world") == arr[0]);
    }

    SECTION("set()") {
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonArrayRef arr = doc.to<JsonArrayRef>();
      arr.add("hello");
      arr.set(0, value);

      REQUIRE(std::string("world") == arr[0]);
    }
  }

  SECTION("JsonArraySubscript") {
    SECTION("set()") {
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonArrayRef arr = doc.to<JsonArrayRef>();
      arr.add("hello");
      arr[0].set(value);

      REQUIRE(std::string("world") == arr[0]);
    }

    SECTION("operator=") {
      unsigned char value[] = "world";

      DynamicJsonDocument doc;
      JsonArrayRef arr = doc.to<JsonArrayRef>();
      arr.add("hello");
      arr[0] = value;

      REQUIRE(std::string("world") == arr[0]);
    }
  }
}
