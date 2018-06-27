// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("Undefined JsonArray") {
  JsonArray array;

  SECTION("SubscriptFails") {
    REQUIRE_FALSE(array[0].success());
  }

  SECTION("AddFails") {
    array.add(1);
    REQUIRE(0 == array.size());
  }

  SECTION("CreateNestedArrayFails") {
    REQUIRE_FALSE(array.createNestedArray().success());
  }

  SECTION("CreateNestedObjectFails") {
    REQUIRE_FALSE(array.createNestedObject().success());
  }

  SECTION("PrintToWritesBrackets") {
    char buffer[32];
    serializeJson(array, buffer, sizeof(buffer));
    REQUIRE_THAT(buffer, Equals("undefined"));
  }
}
