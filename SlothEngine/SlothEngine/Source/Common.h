#pragma once
#include "..\ThirdParty\TinyXML\tinyxml2.h"
#include <string>
#include <lua.hpp>
//#include <Utilities/Color.h>

#define _DEBUG_DRAW 0

using XmlData = tinyxml2::XMLElement;
using XmlDoc = tinyxml2::XMLDocument;

#define HASH(item) std::hash<std::string>()(item)

#define SLTH_API __declspec(dllexport)

#define GLUA()

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using Id = size_t;
using Id32 = u32; 
using Id64 = u64;
using EventType = u8;

// constants
constexpr float kMaxFrameDelay = 1.0f;
constexpr float kPixelsPerMeter = 64.0f;
constexpr float kFixedUpdateDelay = 1.0f / 60.f;
constexpr float kPi = 3.14159265f;






