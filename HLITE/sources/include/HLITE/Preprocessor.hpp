#pragma once

#include <raylib.h>

#define GET_SINGLE_ARRAY_LENGTH(data) (sizeof(data) / sizeof(data[0]))

#define GET_DEFAULT_FONT_SPACING (2)

#define GET_CENTER_DEFAULT_TEXT_FONT_X_INT(text, fontSize) ((GetScreenWidth() - MeasureTextEx(GetFontDefault(), text, (float)(fontSize), GET_DEFAULT_FONT_SPACING).x) / 2)
#define GET_CENTER_DEFAULT_TEXT_FONT_Y_INT(text, fontSize) ((GetScreenHeight() - MeasureTextEx(GetFontDefault(), text, (float)(fontSize), GET_DEFAULT_FONT_SPACING).y) / 2)
#define GET_CENTER_DEFAULT_TEXT_FONT_X_FLOAT(text, fontSize) ((GetScreenWidth() - MeasureTextEx(GetFontDefault(), text, (float)(fontSize), GET_DEFAULT_FONT_SPACING).x) / 2.0f)
#define GET_CENTER_DEFAULT_TEXT_FONT_Y_FLOAT(text, fontSize) ((GetScreenHeight() - MeasureTextEx(GetFontDefault(), text, (float)(fontSize), GET_DEFAULT_FONT_SPACING).y) / 2.0f)

#define GET_CENTER_CUSTOM_TEXT_FONT_X_INT(text, font, fontSize, spacing) ((GetScreenWidth() - MeasureTextEx(font, text, (float)(fontSize), spacing).x) / 2)
#define GET_CENTER_CUSTOM_TEXT_FONT_Y_INT(text, font, fontSize, spacing) ((GetScreenHeight() - MeasureTextEx(font, text, (float)(fontSize), spacing).y) / 2)
#define GET_CENTER_CUSTOM_TEXT_FONT_X_FLOAT(text, font, fontSize, spacing) ((GetScreenWidth() - MeasureTextEx(font, text, (float)(fontSize), spacing).x) / 2.0f)
#define GET_CENTER_CUSTOM_TEXT_FONT_Y_FLOAT(text, font, fontSize, spacing) ((GetScreenHeight() - MeasureTextEx(font, text, (float)(fontSize), spacing).y) / 2.0f)

#define GET_CENTER_POSITION_X(width) ((GetScreenWidth() - width) / 2.0f)
#define GET_CENTER_POSITION_Y(high) ((GetScreenHeight() - high) / 2.0f)
#define GET_CENTER_POSITION_TEXTURE ((Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f})
#define GET_CENTER_POSITION_TEXTURE_X_FLOAT (GetScreenWidth() / 2.0f)
#define GET_CENTER_POSITION_TEXTURE_Y_FLOAT (GetScreenHeight() / 2.0f)
#define GET_CENTER_ORIGIN_TEXTURE_X_FLOAT(texture) (texture.width / 2.0f)
#define GET_CENTER_ORIGIN_TEXTURE_Y_FLOAT(texture) (texture.height / 2.0f)

#define WINDOW_COLOR (Color{210, 210, 210, 210})
#define NO_COLOR ((Color){0, 0, 0, 0})

#define MAX_PARTICLES (3000)

/*
 * Virtual Message Box
*/

#define MB_BTN_OK (0x001UL)
#define MB_BTN_CANCEL (0x002UL)
#define MB_BTN_ABORT (0x003UL)
#define MB_BTN_RETRY (0x004UL)
#define MB_BTN_IGNORE (0x005UL)
#define MB_BTN_YES (0x006UL)
#define MB_BTN_NO (0x007UL)
#define MB_BTN_CONTINUE (0x008UL)
#define MB_BTN_TRY (0x009UL)