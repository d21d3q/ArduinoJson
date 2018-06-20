// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("Undefined JsonArrayRef") {
  SECTION("SubscriptFails") {
    REQUIRE_FALSE(JsonArrayRef()[0].success());
  }

  SECTION("AddFails") {
    JsonArrayRef array = JsonArrayRef();
    array.add(1);
    REQUIRE(0 == array.size());
  }

  SECTION("CreateNestedArrayFails") {
    REQUIRE_FALSE(JsonArrayRef().createNestedArray().success());
  }

  SECTION("CreateNestedObjectFails") {
    REQUIRE_FALSE(JsonArrayRef().createNestedObject().success());
  }

  SECTION("PrintToWritesBrackets") {
    char buffer[32];
    serializeJson(JsonArrayRef(), buffer, sizeof(buffer));
    // REQUIRE_THAT(buffer, Equals("[]")); // TODO
    REQUIRE_THAT(buffer, Equals(""));
  }
}
