// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonObject::operator[]") {
  DynamicJsonDocument doc;
  JsonObjectRef obj = doc.to<JsonObjectRef>();

  SECTION("int") {
    obj["hello"] = 123;

    REQUIRE(123 == obj["hello"].as<int>());
    REQUIRE(true == obj["hello"].is<int>());
    REQUIRE(false == obj["hello"].is<bool>());
  }

  SECTION("volatile int") {  // issue #415
    volatile int i = 123;
    obj["hello"] = i;

    REQUIRE(123 == obj["hello"].as<int>());
    REQUIRE(true == obj["hello"].is<int>());
    REQUIRE(false == obj["hello"].is<bool>());
  }

  SECTION("double") {
    obj["hello"] = 123.45;

    REQUIRE(true == obj["hello"].is<double>());
    REQUIRE(false == obj["hello"].is<long>());
    REQUIRE(123.45 == obj["hello"].as<double>());
  }

  SECTION("bool") {
    obj["hello"] = true;

    REQUIRE(true == obj["hello"].is<bool>());
    REQUIRE(false == obj["hello"].is<long>());
    REQUIRE(true == obj["hello"].as<bool>());
  }

  SECTION("const char*") {
    obj["hello"] = "h3110";

    REQUIRE(true == obj["hello"].is<const char*>());
    REQUIRE(false == obj["hello"].is<long>());
    REQUIRE(std::string("h3110") == obj["hello"].as<const char*>());
    REQUIRE(std::string("h3110") == obj["hello"].as<char*>());  // <- short hand
  }

  SECTION("array") {
    DynamicJsonDocument doc2;
    JsonArrayRef arr = doc2.to<JsonArray>();

    obj["hello"] = arr;

    REQUIRE(arr == obj["hello"].as<JsonArray&>());
    REQUIRE(arr == obj["hello"].as<JsonArray>());  // <- short hand
    // REQUIRE(arr == obj["hello"].as<const JsonArray&>());
    // REQUIRE(arr == obj["hello"].as<const JsonArray>());  // <- short hand
    REQUIRE(true == obj["hello"].is<JsonArray&>());
    REQUIRE(true == obj["hello"].is<JsonArray>());
    REQUIRE(true == obj["hello"].is<const JsonArray&>());
    REQUIRE(true == obj["hello"].is<const JsonArray>());
    REQUIRE(false == obj["hello"].is<JsonObjectRef>());
  }

  SECTION("object") {
    DynamicJsonDocument doc2;
    JsonObjectRef obj2 = doc2.to<JsonObjectRef>();

    obj["hello"] = obj2;

    REQUIRE(obj2 == obj["hello"].as<JsonObjectRef>());
    REQUIRE(obj2 == obj["hello"].as<JsonObjectRef>());  // <- short hand
    // REQUIRE(obj2 == obj["hello"].as<const JsonObjectRef>());
    // REQUIRE(obj2 == obj["hello"].as<const JsonObject>());  // <- short hand
    REQUIRE(true == obj["hello"].is<JsonObjectRef>());
    REQUIRE(true == obj["hello"].is<JsonObjectRef>());
    REQUIRE(true == obj["hello"].is<const JsonObjectRef>());
    REQUIRE(true == obj["hello"].is<const JsonObject>());
    REQUIRE(false == obj["hello"].is<JsonArray&>());
  }

  SECTION("array subscript") {
    DynamicJsonDocument doc2;
    JsonArrayRef arr = doc2.to<JsonArray>();
    arr.add(42);

    obj["a"] = arr[0];

    REQUIRE(42 == obj["a"]);
  }

  SECTION("object subscript") {
    DynamicJsonDocument doc2;
    JsonObjectRef obj2 = doc2.to<JsonObjectRef>();
    obj2.set("x", 42);

    obj["a"] = obj2["x"];

    REQUIRE(42 == obj["a"]);
  }

  SECTION("char key[]") {  // issue #423
    char key[] = "hello";
    obj[key] = 42;
    REQUIRE(42 == obj[key]);
  }

  SECTION("should not duplicate const char*") {
    obj["hello"] = "world";
    const size_t expectedSize = JSON_OBJECT_SIZE(1);
    REQUIRE(expectedSize == doc.memoryUsage());
  }

  SECTION("should duplicate char* value") {
    obj["hello"] = const_cast<char*>("world");
    const size_t expectedSize = JSON_OBJECT_SIZE(1) + 6;
    REQUIRE(expectedSize == doc.memoryUsage());
  }

  SECTION("should duplicate char* key") {
    obj[const_cast<char*>("hello")] = "world";
    const size_t expectedSize = JSON_OBJECT_SIZE(1) + 6;
    REQUIRE(expectedSize == doc.memoryUsage());
  }

  SECTION("should duplicate char* key&value") {
    obj[const_cast<char*>("hello")] = const_cast<char*>("world");
    const size_t expectedSize = JSON_OBJECT_SIZE(1) + 12;
    REQUIRE(expectedSize <= doc.memoryUsage());
  }

  SECTION("should duplicate std::string value") {
    obj["hello"] = std::string("world");
    const size_t expectedSize = JSON_OBJECT_SIZE(1) + 6;
    REQUIRE(expectedSize == doc.memoryUsage());
  }

  SECTION("should duplicate std::string key") {
    obj[std::string("hello")] = "world";
    const size_t expectedSize = JSON_OBJECT_SIZE(1) + 6;
    REQUIRE(expectedSize == doc.memoryUsage());
  }

  SECTION("should duplicate std::string key&value") {
    obj[std::string("hello")] = std::string("world");
    const size_t expectedSize = JSON_OBJECT_SIZE(1) + 12;
    REQUIRE(expectedSize <= doc.memoryUsage());
  }

  SECTION("should ignore null key") {
    // object must have a value to make a call to strcmp()
    obj["dummy"] = 42;

    const char* null = 0;
    obj[null] = 666;

    REQUIRE(obj.size() == 1);
    REQUIRE(obj[null] == 0);
  }
}
