// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

TEST_CASE("measureMsgPack()") {
  DynamicJsonDocument doc;
  JsonObjectRef object = doc.to<JsonObjectRef>();
  object["hello"] = "world";

  REQUIRE(measureMsgPack(doc) == 13);
}
