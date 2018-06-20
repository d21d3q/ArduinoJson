// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("JsonArray basics") {
  DynamicJsonDocument doc;
  JsonArrayRef array = doc.to<JsonArrayRef>();

  SECTION("SuccessIsTrue") {
    REQUIRE(array.success());
  }

  SECTION("InitialSizeIsZero") {
    REQUIRE(0U == array.size());
  }

  SECTION("CreateNestedArray") {
    JsonArrayRef arr = array.createNestedArray();
    REQUIRE(arr == array[0].as<JsonArrayRef>());
  }

  SECTION("CreateNestedObject") {
    JsonObjectRef obj = array.createNestedObject();
    REQUIRE(obj == array[0].as<JsonObjectRef>());
  }
}
