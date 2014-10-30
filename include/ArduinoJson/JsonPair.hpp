// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#pragma once

#include "JsonValue.hpp"
#include "Internals/JsonObjectNode.hpp"

namespace ArduinoJson {

struct JsonPair {
  JsonPair(const char* k) : key(k) {}

  const char* const key;
  JsonValue value;

  // warning C4512: assignment operator could not be generated
  #pragma warning( suppress : 4512 ) 
};
}