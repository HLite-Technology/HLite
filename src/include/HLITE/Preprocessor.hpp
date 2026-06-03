#pragma once

#include <raylib.h>

#define GET_SINGLE_ARRAY_LENGTH(data) (sizeof(data) / sizeof(data[0]))

#define GET_CENTER_TEXT_X_INT(text, size) ((GetScreenWidth() - MeasureText(text, size)) / 2)
#define GET_CENTER_TEXT_Y_INT(size) ((GetScreenHeight() - size) / 2)
#define GET_CENTER_TEXT_X_FLOAT(text, size) ((GetScreenWidth() - MeasureText(text, size)) / 2.0f)
#define GET_CENTER_TEXT_Y_FLOAT(size) ((GetScreenHeight() - size) / 2.0f)

#define GET_CENTER_POSITION_TEXTURE ((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f})
#define GET_CENTER_POSITION_TEXTURE_X_FLOAT (GetScreenWidth() / 2.0f)
#define GET_CENTER_POSITION_TEXTURE_Y_FLOAT (GetScreenHeight() / 2.0f)
#define GET_CENTER_ORIGIN_TEXTURE_X_FLOAT(texture) (texture.width / 2.0f)
#define GET_CENTER_ORIGIN_TEXTURE_Y_FLOAT(texture) (texture.height / 2.0f)

#define NO_COLOR ((Color){0, 0, 0, 0})

#define MAX_PARTICLES (3000)