#pragma once

#include <cstdint>

enum class TexelEncoding
{
  NONE = 0,
  LINEAR,
  SRGB,
};

enum class ToneMapping
{
  None = 0,
  LINEAR,
  REINHARD,
  CINEON,
  ACES_FILMIC,
  CUSTOM,
};

enum class Precision
{
  HIGHP,
  MEDIUMP,
  LOW,
};

enum class Usage
{
    NONE = 0,
    STREAM_DRAW,
    STREAM_READ,
    STREAM_COPY,
    STATIC_DRAW,
    STATIC_READ,
    STATIC_COPY,
    DYNAMIC_DRAW,
    DYNAMIC_READ,
    DYNAMIC_COPY,
};

enum class DrawMode
{
  None,
  Points,
  Line,
  Triangles,
};