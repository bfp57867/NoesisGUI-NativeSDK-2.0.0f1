////////////////////////////////////////////////////////////////////////////////////////////////////
// Noesis Engine - http://www.noesisengine.com
// Copyright (c) 2009-2010 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////


#include <NsMath/Utils.h>


namespace Noesis
{
namespace Drawing
{

////////////////////////////////////////////////////////////////////////////////////////////////////
Color::Color()
{
    mColor[0] = 0.0f;
    mColor[1] = 0.0f;
    mColor[2] = 0.0f;
    mColor[3] = 1.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Color::Color(NsFloat32 red, NsFloat32 green, NsFloat32 blue, NsFloat32 alpha)
{
    mColor[0] = red;
    mColor[1] = green;
    mColor[2] = blue;
    mColor[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
Color::Color(NsInt red, NsInt green, NsInt blue, NsInt alpha)
{
    mColor[0] = red / 255.0f;
    mColor[1] = green / 255.0f;
    mColor[2] = blue / 255.0f;
    mColor[3] = alpha / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetRed(NsFloat32 red)
{
    mColor[0] = red;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetRed(NsInt red)
{
    mColor[0] = red / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetGreen(NsFloat32 green)
{
    mColor[1] = green;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetGreen(NsInt green)
{
    mColor[1] = green / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetBlue(NsFloat32 blue)
{
    mColor[2] = blue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetBlue(NsInt blue)
{
    mColor[2] = blue / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetAlpha(NsFloat32 alpha)
{
    mColor[3] = alpha;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetAlpha(NsInt alpha)
{
    mColor[3] = alpha / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetPackedColorBGRA(NsUInt32 color)
{
    mColor[0] = ((color >> 16) & 255) / 255.0f;
    mColor[1] = ((color >> 8) & 255) / 255.0f;
    mColor[2] = (color & 255) / 255.0f;
    mColor[3] = (color >> 24) / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Color::SetPackedColorRGBA(NsUInt32 color)
{
    mColor[0] = (color & 255) / 255.0f;
    mColor[1] = ((color >> 8) & 255) / 255.0f;
    mColor[2] = ((color >> 16) & 255) / 255.0f;
    mColor[3] = (color >> 24) / 255.0f;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsInt Color::GetRedI() const
{
    return Math::Clip(Math::Trunc(mColor[0] * 255.0f), 0, 255);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsInt Color::GetGreenI() const
{
    return Math::Clip(Math::Trunc(mColor[1] * 255.0f), 0, 255);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsInt Color::GetBlueI() const
{
    return Math::Clip(Math::Trunc(mColor[2] * 255.0f), 0, 255);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsInt Color::GetAlphaI() const
{
    return Math::Clip(Math::Trunc(mColor[3] * 255.0f), 0, 255);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat32 Color::GetRedF() const
{
    return mColor[0];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat32 Color::GetGreenF() const
{
    return mColor[1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat32 Color::GetBlueF() const
{
    return mColor[2];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsFloat32 Color::GetAlphaF() const
{
    return mColor[3];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Color::GetPackedColorBGRA() const
{
    return (GetAlphaI() << 24) | (GetRedI() << 16) | (GetGreenI() << 8) | GetBlueI();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsUInt32 Color::GetPackedColorRGBA() const
{
    return (GetAlphaI() << 24) | (GetBlueI() << 16) | (GetGreenI() << 8) | GetRedI();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool Color::operator==(const Color& color) const
{
    return mColor[0] == color.mColor[0] && mColor[1] == color.mColor[1] && 
        mColor[2] == color.mColor[2] && mColor[3] == color.mColor[3];
}

////////////////////////////////////////////////////////////////////////////////////////////////////
NsBool Color::operator!=(const Color& color) const
{
    return !(*this == color);
}

}
}