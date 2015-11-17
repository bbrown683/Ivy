/*
The MIT License (MIT)

Copyright (c) 2015 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Color.h"

// List of .NET Colors translated into their respective values for OpenGL and DirectX.

static const Jade::Math::Color IndianRed		= Jade::Math::Color(0.804f, 0.361f, 0.361f, 1.0f); //RGBA: {0.804f, 0.361f, 0.361f, 1.0f}
static const Jade::Math::Color LightCoral		= Jade::Math::Color(0.941f, 0.502f, 0.502f, 1.0f);//RGBA: {0.941f, 0.502f, 0.502f, 1.0f}
static const Jade::Math::Color Salmon			= Jade::Math::Color(0.980f, 0.502f, 0.447f, 1.0f); //RGBA: {0.980f, 0.502f, 0.447f, 1.0f}
static const Jade::Math::Color DarkSalmon		= Jade::Math::Color(0.914f, 0.588f, 0.478f, 1.0f); //RGBA: {0.914f, 0.588f, 0.478f, 1.0f}
static const Jade::Math::Color LightSalmon		= Jade::Math::Color(1.0f, 0.627f, 0.478f, 1.0f); //RGBA: {1.0f, 0.627f, 0.478f, 1.0f}
static const Jade::Math::Color Crimson			= Jade::Math::Color(0.863f, 0.078f, 0.235f, 1.0f); //RGBA: {0.863f, 0.078f, 0.235f, 1.0f}
static const Jade::Math::Color Red				= Jade::Math::Color(1.0f, 0.0f, 0.0f, 1.0f); //RGBA: {1.0f, 0.0f, 0.0f, 1.0f}
static const Jade::Math::Color FireBrick		= Jade::Math::Color(0.698f, 0.133f, 0.133f, 1.0f); //RGBA: {0.698f, 0.133f, 0.133f, 1.0f}
static const Jade::Math::Color DarkRed			= Jade::Math::Color(0.545f, 0.0f, 0.0f, 1.0f); //RGBA: {0.545f, 0.0f, 0.0f, 1.0f}
static const Jade::Math::Color Pink				= Jade::Math::Color(1.0f, 0.753f, 0.796f, 1.0f); //RGBA: {1.0f, 0.753f, 0.796f, 1.0f}
static const Jade::Math::Color LightPink		= Jade::Math::Color(1.0f, 0.714f, 0.747f, 1.0f); //RGBA: {1.0f, 0.714f, 0.747f, 1.0f}
static const Jade::Math::Color HotPink			= Jade::Math::Color(1.0f, 0.410f, 0.747f, 1.0f); //RGBA: {1.0f, 0.410f, 0.747f, 1.0f}
static const Jade::Math::Color DeepPink			= Jade::Math::Color(1.0f, 0.078f, 0.576f, 1.0f);//RGBA: {1.0f, 0.078f, 0.576f, 1.0f}
static const Jade::Math::Color MediumVioletRed	= Jade::Math::Color(0.780f, 0.082f, 0.522f, 1.0f); //RGBA: {0.780f, 0.082f, 0.522f, 1.0f}
static const Jade::Math::Color PaleVioletRed	= Jade::Math::Color(0.859f, 0.439f, 0.576f, 1.0f); //RGBA: {0.859f, 0.439f, 0.576f, 1.0f}
static const Jade::Math::Color Coral			= Jade::Math::Color(1.0f, 0.627f, 0.478f, 1.0f); //RGBA: {1.0f, 0.627f, 0.478f, 1.0f}
static const Jade::Math::Color Tomato			= Jade::Math::Color(1.0f, 0.388f, 0.278f, 1.0f); //RGBA: {1.0f, 0.388f, 0.278f, 1.0f}
static const Jade::Math::Color OrangeRed		= Jade::Math::Color(1.0f, 0.271f, 0.0f, 1.0f); //RGBA: {1.0f, 0.271f, 0.0f, 1.0f}
static const Jade::Math::Color DarkOrange		= Jade::Math::Color(1.0f, 0.549f, 0.0f, 1.0f); //RGBA: {1.0f, 0.549f, 0.0f, 1.0f}
static const Jade::Math::Color Orange			= Jade::Math::Color(1.0f, 0.647f, 0.0f, 1.0f); //RGBA: {1.0f, 0.647f, 0.0f, 1.0f}
static const Jade::Math::Color Gold				= Jade::Math::Color(1.0f, 0.843f, 0.0f, 1.0f); //RGBA: {1.0f, 0.843f, 0.0f, 1.0f}
static const Jade::Math::Color Yellow			= Jade::Math::Color(1.0f, 1.0f, 0.0f, 1.0f); //RGBA: {1.0f, 1.0f, 0.0f, 1.0f}
static const Jade::Math::Color LightYellow		= Jade::Math::Color(1.0f, 1.0f, 0.878f, 1.0f); //RGBA: {1.0f, 1.0f, 0.878f, 1.0f}
static const Jade::Math::Color LemonChion		= Jade::Math::Color(0.980f, 0.980f, 0.804f, 1.0f); //RGBA: {0.980f, 0.980f, 0.804f, 1.0f}
static const Jade::Math::Color LightGoldenRodYellow = Jade::Math::Color(0.980f, 0.980f, 0.824f, 1.0f); //RGBA: {0.980f, 0.980f, 0.824f, 1.0f}
static const Jade::Math::Color PapayaWhip		= Jade::Math::Color(1.0f, 0.937f, 0.835f, 1.0f); //RGBA: {1.0f, 0.937f, 0.835f, 1.0f}
static const Jade::Math::Color Moccasin			= Jade::Math::Color(1.0f, 0.894f, 0.710f, 1.0f); //RGBA: {1.0f, 0.894f, 0.710f, 1.0f}
static const Jade::Math::Color PeachPu			= Jade::Math::Color(1.0f, 0.855f, 0.725f, 1.0f); //RGBA: {1.0f, 0.855f, 0.725f, 1.0f}
static const Jade::Math::Color PaleGoldenRod	= Jade::Math::Color(0.933f, 0.910f, 0.667f, 1.0f); //RGBA: {0.933f, 0.910f, 0.667f, 1.0f}
static const Jade::Math::Color Khaki			= Jade::Math::Color(0.941f, 0.902f, 0.549f, 1.0f); //RGBA: {0.941f, 0.902f, 0.549f, 1.0f}
static const Jade::Math::Color DarkKhaki		= Jade::Math::Color(0.741f, 0.718f, 0.420f, 1.0f); //RGBA: {0.741f, 0.718f, 0.420f, 1.0f}
static const Jade::Math::Color Lavender			= Jade::Math::Color(0.902f, 0.902f, 0.980f, 1.0f); //RGBA: {0.902f, 0.902f, 0.980f, 1.0f}
static const Jade::Math::Color Thistle			= Jade::Math::Color(0.847f, 0.749f, 0.847f, 1.0f); //RGBA: {0.847f, 0.749f, 0.847f, 1.0f}
static const Jade::Math::Color Plum				= Jade::Math::Color(0.867f, 0.627f, 0.867f, 1.0f); //RGBA: {0.867f, 0.627f, 0.867f, 1.0f}
static const Jade::Math::Color Violet			= Jade::Math::Color(0.933f, 0.510f, 0.933f, 1.0f); //RGBA: {0.933f, 0.510f, 0.933f, 1.0f}
static const Jade::Math::Color Orchid			= Jade::Math::Color(0.655f, 0.439f, 0.839f, 1.0f); //RGBA: {0.655f, 0.439f, 0.839f, 1.0f}
static const Jade::Math::Color Magenta			= Jade::Math::Color(1.0f, 0.0f, 1.0f, 1.0f); //RGBA: {1.0f, 0.0f, 1.0f, 1.0f}
static const Jade::Math::Color MediumOrchid		= Jade::Math::Color(0.729f, 0.333f, 0.827f, 1.0f); //RGBA: {0.729f, 0.333f, 0.827f, 1.0f}
static const Jade::Math::Color MediumPurple		= Jade::Math::Color(0.576f, 0.439f, 0.859f, 1.0f); //RGBA: {0.576f, 0.439f, 0.859f, 1.0f}
static const Jade::Math::Color BlueViolet		= Jade::Math::Color(0.541f, 0.169f, 0.886f, 1.0f); //RGBA: {0.541f, 0.169f, 0.886f, 1.0f}
static const Jade::Math::Color DarkViolet		= Jade::Math::Color(0.580f, 0.0f, 0.827f, 1.0f); //RGBA: {0.580f, 0.0f, 0.827f, 1.0f}
static const Jade::Math::Color DarkOrchid		= Jade::Math::Color(0.600f, 0.196f, 0.800f, 1.0f); //RGBA: {0.600f, 0.196f, 0.800f, 1.0f}
static const Jade::Math::Color DarkMagenta		= Jade::Math::Color(0.545f, 0.0f, 0.545f, 1.0f); //RGBA: {0.545f, 0.0f, 0.545f, 1.0f}
static const Jade::Math::Color Purple			= Jade::Math::Color(0.502f, 0.0f, 0.502f, 1.0f); //RGBA: {0.502f, 0.0f, 0.502f, 1.0f}
static const Jade::Math::Color Indigo			= Jade::Math::Color(0.294f, 0.0f, 0.510f, 1.0f); //RGBA: {0.294f, 0.0f, 0.510f, 1.0f}
static const Jade::Math::Color SlateBlue		= Jade::Math::Color(0.416f, 0.353f, 0.804f, 1.0f); //RGBA: {0.416f, 0.353f, 0.804f, 1.0f}
static const Jade::Math::Color DarkSlateBlue	= Jade::Math::Color(0.282f, 0.239f, 0.545f, 1.0f); //RGBA: {0.282f, 0.239f, 0.545f, 1.0f}
static const Jade::Math::Color GreenYellow		= Jade::Math::Color(0.678f, 1.0f, 0.184f, 1.0f); //RGBA: {0.678f, 1.0f, 0.184f, 1.0f}
static const Jade::Math::Color Chartreuse		= Jade::Math::Color(0.498f, 1.0f, 0.0f, 1.0f); //RGBA: {0.498f, 1.0f, 0.0f, 1.0f}
static const Jade::Math::Color LawnGreen		= Jade::Math::Color(0.486f, 0.988f, 0.0f, 1.0f); //RGBA: {0.486f, 0.988f, 0.0f, 1.0f}
static const Jade::Math::Color Lime				= Jade::Math::Color(0.0f, 1.0f, 0.0f, 1.0f); //RGBA: {0.0f, 1.0f, 0.0f, 1.0f}
static const Jade::Math::Color LimeGreen		= Jade::Math::Color(0.196f, 0.804f, 0.196f, 1.0f); //RGBA: {0.196f, 0.804f, 0.196f, 1.0f}
static const Jade::Math::Color PaleGreen		= Jade::Math::Color(0.596f, 0.984f, 0.596f, 1.0f); //RGBA: {0.596f, 0.984f, 0.596f, 1.0f}
static const Jade::Math::Color LightGreen		= Jade::Math::Color(0.565f, 0.933f, 0.565f, 1.0f); //RGBA: {0.565f, 0.933f, 0.565f, 1.0f}
static const Jade::Math::Color MediumSpringGreen = Jade::Math::Color(0.0f, 0.980f, 0.604f, 1.0f); //RGBA: {0.0f, 0.980f, 0.604f, 1.0f}
static const Jade::Math::Color SpringGreen		= Jade::Math::Color(0.0f, 1.0f, 0.498f, 1.0f); //RGBA: {0.0f, 1.0f, 0.498f, 1.0f}
static const Jade::Math::Color MediumSeaGreen	= Jade::Math::Color(0.235f, 0.702f, 0.443f, 1.0f); //RGBA: {0.235f, 0.702f, 0.443f, 1.0f}
static const Jade::Math::Color SeaGreen			= Jade::Math::Color(0.180f, 0.545f, 0.341f, 1.0f); //RGBA: {0.180f, 0.545f, 0.341f, 1.0f}
static const Jade::Math::Color ForestGreen		= Jade::Math::Color(0.133f, 0.545f, 0.133f, 1.0f); //RGBA: {0.133f, 0.545f, 0.133f, 1.0f}
static const Jade::Math::Color Green			= Jade::Math::Color(0.0f, 0.502f, 0.0f, 1.0f); //RGBA: {0.0f, 0.502f, 0.0f, 1.0f}
static const Jade::Math::Color DarkGreen		= Jade::Math::Color(0.0f, 0.392f, 0.0f, 1.0f); //RGBA: {0.0f, 0.392f, 0.0f, 1.0f}
static const Jade::Math::Color YellowGreen		= Jade::Math::Color(0.604f, 0.804f, 0.196f, 1.0f); //RGBA: {0.604f, 0.804f, 0.196f, 1.0f}
static const Jade::Math::Color OliveDrab		= Jade::Math::Color(0.420f, 0.557f, 0.137f, 1.0f); //RGBA: {0.420f, 0.557f, 0.137f, 1.0f}
static const Jade::Math::Color Olive			= Jade::Math::Color(0.502f, 0.502f, 0.0f, 1.0f); //RGBA: {0.502f, 0.502f, 0.0f, 1.0f}
static const Jade::Math::Color DarkOliveGreen	= Jade::Math::Color(0.333f, 0.420f, 0.184f, 1.0f); //RGBA: {0.333f, 0.420f, 0.184f, 1.0f}
static const Jade::Math::Color MediumAquamarine = Jade::Math::Color(0.400f, 0.804f, 0.667f, 1.0f); //RGBA: {0.400f, 0.804f, 0.667f, 1.0f}
static const Jade::Math::Color DarkSeaGreen		= Jade::Math::Color(0.561f, 0.737f, 0.561f, 1.0f); //RGBA: {0.561f, 0.737f, 0.561f, 1.0f}
static const Jade::Math::Color LightSeaGreen	= Jade::Math::Color(0.125f, 0.698f, 0.667f, 1.0f); //RGBA: {0.125f, 0.698f, 0.667f, 1.0f}
static const Jade::Math::Color DarkCyan			= Jade::Math::Color(0.0f, 0.545f, 0.545f, 1.0f); //RGBA: {0.0f, 0.545f, 0.545f, 1.0f}
static const Jade::Math::Color Teal				= Jade::Math::Color(0.0f, 0.502f, 0.502f, 1.0f); //RGBA: {0.0f, 0.502f, 0.502f, 1.0f}
static const Jade::Math::Color Aqua				= Jade::Math::Color(0.0f, 1.0f, 1.0f, 1.0f); //RGBA: {0.0f, 1.0f, 1.0f, 1.0f}
static const Jade::Math::Color Cyan				= Jade::Math::Color(0.0f, 1.0f, 1.0f, 1.0f); //RGBA: {0.0f, 1.0f, 1.0f, 1.0f}
static const Jade::Math::Color LightCyan		= Jade::Math::Color(0.878f, 1.0f, 1.0f, 1.0f); //RGBA: {0.878f, 1.0f, 1.0f, 1.0f}
static const Jade::Math::Color PaleTurquoise	= Jade::Math::Color(0.686f, 0.933f, 0.933f, 1.0f); //RGBA: {0.686f, 0.933f, 0.933f, 1.0f}
static const Jade::Math::Color Aquamarine		= Jade::Math::Color(0.498f, 1.0f, 0.831f, 1.0f); //RGBA: {0.498f, 1.0f, 0.831f, 1.0f}
static const Jade::Math::Color Turquoise		= Jade::Math::Color(0.251f, 0.878f, 0.816f, 1.0f); //RGBA: {0.251f, 0.878f, 0.816f, 1.0f}
static const Jade::Math::Color MediumTurquoise	= Jade::Math::Color(0.282f, 0.820f, 0.800f, 1.0f); //RGBA: {0.282f, 0.820f, 0.800f, 1.0f}
static const Jade::Math::Color DarkTurquoise	= Jade::Math::Color(0.0f, 0.808f, 0.820f, 1.0f); //RGBA: {0.0f, 0.808f, 0.820f, 1.0f}
static const Jade::Math::Color CadetBlue		= Jade::Math::Color(0.373f, 0.620f, 0.627f, 1.0f); //RGBA: {0.373f, 0.620f, 0.627f, 1.0f}
static const Jade::Math::Color SteelBlue		= Jade::Math::Color(0.275f, 0.510f, 0.706f, 1.0f); //RGBA: {0.275f, 0.510f, 0.706f, 1.0f}
static const Jade::Math::Color LightSteelBlue	= Jade::Math::Color(0.690f, 0.769f, 0.871f, 1.0f); //RGBA: {0.690f, 0.769f, 0.871f, 1.0f}
static const Jade::Math::Color LightBlue		= Jade::Math::Color(0.678f, 0.847f, 0.902f, 1.0f); //RGBA: {0.678f, 0.847f, 0.902f, 1.0f}
static const Jade::Math::Color PowderBlue		= Jade::Math::Color(0.690f, 0.878f, 0.902f, 1.0f); //RGBA: {0.690f, 0.878f, 0.902f, 1.0f}
static const Jade::Math::Color SkyBlue			= Jade::Math::Color(0.529f, 0.808f, 0.922f, 1.0f); //RGBA: {0.529f, 0.808f, 0.922f, 1.0f}
static const Jade::Math::Color LightSkyBlue		= Jade::Math::Color(0.529f, 0.808f, 0.980f, 1.0f); //RGBA: {0.529f, 0.808f, 0.980f, 1.0f}
static const Jade::Math::Color DeepSkyBlue		= Jade::Math::Color(0.0f, 0.749f, 1.0f, 1.0f); //RGBA: {0.0f, 0.749f, 1.0f, 1.0f}
static const Jade::Math::Color DodgerBlue		= Jade::Math::Color(0.118f, 0.565f, 1.0f, 1.0f); //RGBA: {0.118f, 0.565f, 1.0f, 1.0f}
static const Jade::Math::Color CornflowerBlue	= Jade::Math::Color(0.392f, 0.584f, 0.929f, 1.0f); //RGBA: {0.392f, 0.584f, 0.929f, 1.0f}
static const Jade::Math::Color MediumSlateBlue	= Jade::Math::Color(0.482f, 0.408f, 0.933f, 1.0f); //RGBA: {0.482f, 0.408f, 0.933f, 1.0f}
static const Jade::Math::Color RoyalBlue		= Jade::Math::Color(0.255f, 0.412f, 0.882f, 1.0f); //RGBA: {0.255f, 0.412f, 0.882f, 1.0f}
static const Jade::Math::Color Blue				= Jade::Math::Color(0.0f, 0.0f, 1.0f, 1.0f); //RGBA: {0.0f, 0.0f, 1.0f, 1.0f}
static const Jade::Math::Color MediumBlue		= Jade::Math::Color(0.0f, 0.0f, 0.804f, 1.0f); //RGBA: {0.0f, 0.0f, 0.804f, 1.0f}
static const Jade::Math::Color DarkBlue			= Jade::Math::Color(0.0f, 0.0f, 0.545f, 1.0f); //RGBA: {0.0f, 0.0f, 0.545f, 1.0f}
static const Jade::Math::Color Navy				= Jade::Math::Color(0.0f, 0.0f, 0.502f, 1.0f); //RGBA: {0.0f, 0.0f, 0.502f, 1.0f}
static const Jade::Math::Color MidnightBlue		= Jade::Math::Color(0.098f, 0.098f, 0.439f, 1.0f); //RGBA: {0.098f, 0.098f, 0.439f, 1.0f}
static const Jade::Math::Color Cornsilk			= Jade::Math::Color(1.0f, 0.973f, 0.863f, 1.0f); //RGBA: {1.0f, 0.973f, 0.863f, 1.0f}
static const Jade::Math::Color BlanchedAlmond	= Jade::Math::Color(1.0f, 0.922f, 0.804f, 1.0f); //RGBA: {1.0f, 0.922f, 0.804f, 1.0f}
static const Jade::Math::Color Bisque			= Jade::Math::Color(1.0f, 0.894f, 0.769f, 1.0f); //RGBA: {1.0f, 0.894f, 0.769f, 1.0f}
static const Jade::Math::Color NavajoWhite		= Jade::Math::Color(1.0f, 0.871f, 0.678f, 1.0f); //RGBA: {1.0f, 0.871f, 0.678f, 1.0f}
static const Jade::Math::Color Wheat			= Jade::Math::Color(0.961f, 0.871f, 0.702f, 1.0f); //RGBA: {0.961f, 0.871f, 0.702f, 1.0f}
static const Jade::Math::Color BurlyWood		= Jade::Math::Color(0.871f, 0.722f, 0.529f, 1.0f); //RGBA: {0.871f, 0.722f, 0.529f, 1.0f}
static const Jade::Math::Color Tan				= Jade::Math::Color(0.824f, 0.706f, 0.549f, 1.0f); //RGBA: {0.824f, 0.706f, 0.549f, 1.0f}
static const Jade::Math::Color RosyBrown		= Jade::Math::Color(0.737f, 0.561f, 0.561f, 1.0f); //RGBA: {0.737f, 0.561f, 0.561f, 1.0f}
static const Jade::Math::Color SandyBrown		= Jade::Math::Color(0.957f, 0.643f, 0.376f, 1.0f); //RGBA: {0.957f, 0.643f, 0.376f, 1.0f}
static const Jade::Math::Color Goldenrod		= Jade::Math::Color(0.855f, 0.647f, 0.125f, 1.0f); //RGBA: {0.855f, 0.647f, 0.125f, 1.0f}
static const Jade::Math::Color DarkGoldenrod	= Jade::Math::Color(0.722f, 0.525f, 0.043f, 1.0f); //RGBA: {0.722f, 0.525f, 0.043f, 1.0f}
static const Jade::Math::Color Peru				= Jade::Math::Color(0.804f, 0.522f, 0.247f, 1.0f); //RGBA: {0.804f, 0.522f, 0.247f, 1.0f}
static const Jade::Math::Color Chocolate		= Jade::Math::Color(0.824f, 0.412f, 0.118f, 1.0f); //RGBA: {0.824f, 0.412f, 0.118f, 1.0f}
static const Jade::Math::Color SaddleBrown		= Jade::Math::Color(0.545f, 0.271f, 0.075f, 1.0f); //RGBA: {0.545f, 0.271f, 0.075f, 1.0f}
static const Jade::Math::Color Sienna			= Jade::Math::Color(0.627f, 0.322f, 0.176f, 1.0f); //RGBA: {0.627f, 0.322f, 0.176f, 1.0f}
static const Jade::Math::Color Brown			= Jade::Math::Color(0.647f, 0.165f, 0.165f, 1.0f); //RGBA: {0.647f, 0.165f, 0.165f, 1.0f}
static const Jade::Math::Color Maroon			= Jade::Math::Color(0.502f, 0.0f, 0.0f, 1.0f); //RGBA: {0.502f, 0.0f, 0.0f, 1.0f}
static const Jade::Math::Color White			= Jade::Math::Color(1.0f, 1.0f, 1.0f, 1.0f); //RGBA: {1.0f, 1.0f, 1.0f, 1.0f}
static const Jade::Math::Color Snow				= Jade::Math::Color(1.0f, 0.980f, 0.980f, 1.0f); //RGBA: {1.0f, 0.980f, 0.980f, 1.0f}
static const Jade::Math::Color Honeydew			= Jade::Math::Color(0.941f, 1.0f, 0.941f, 1.0f); //RGBA: {0.941f, 1.0f, 0.941f, 1.0f}
static const Jade::Math::Color MintCream		= Jade::Math::Color(0.961f, 1.0f, 0.980f, 1.0f); //RGBA: {0.961f, 1.0f, 0.980f, 1.0f}
static const Jade::Math::Color Azure			= Jade::Math::Color(0.941f, 1.0f, 1.0f, 1.0f); //RGBA: {0.941f, 1.0f, 1.0f, 1.0f}
static const Jade::Math::Color AliceBlue		= Jade::Math::Color(0.941f, 0.973f, 1.0f, 1.0f); //RGBA: {0.941f, 0.973f, 1.0f, 1.0f}
static const Jade::Math::Color GhostWhite		= Jade::Math::Color(0.973f, 0.973f, 1.0f, 1.0f); //RGBA: {0.973f, 0.973f, 1.0f, 1.0f}
static const Jade::Math::Color WhiteSmoke		= Jade::Math::Color(0.961f, 0.961f, 0.961f, 1.0f); //RGBA: {0.961f, 0.961f, 0.961f, 1.0f}
static const Jade::Math::Color SeaShell			= Jade::Math::Color(1.0f, 0.961f, 0.933f, 1.0f); //RGBA: {1.0f, 0.961f, 0.933f, 1.0f}
static const Jade::Math::Color Beige			= Jade::Math::Color(0.961f, 0.961f, 0.863f, 1.0f); //RGBA: {0.961f, 0.961f, 0.863f, 1.0f}
static const Jade::Math::Color OldLace			= Jade::Math::Color(0.992f, 0.961f, 0.902f, 1.0f); //RGBA: {0.992f, 0.961f, 0.902f, 1.0f}
static const Jade::Math::Color FloralWhite		= Jade::Math::Color(1.0f, 0.980f, 0.941f, 1.0f); //RGBA: {1.0f, 0.980f, 0.941f, 1.0f}
static const Jade::Math::Color Ivory			= Jade::Math::Color(1.0f, 1.0f, 0.941f, 1.0f); //RGBA: {1.0f, 1.0f, 0.941f, 1.0f}
static const Jade::Math::Color AntiqueWhite		= Jade::Math::Color(0.980f, 0.922f, 0.843f, 1.0f); //RGBA: {0.980f, 0.922f, 0.843f, 1.0f}
static const Jade::Math::Color Linen			= Jade::Math::Color(0.980f, 0.941f, 0.902f, 1.0f); //RGBA: {0.980f, 0.941f, 0.902f, 1.0f}
static const Jade::Math::Color LavenderBlush	= Jade::Math::Color(1.0f, 0.941f, 0.961f, 1.0f); //RGBA: {1.0f, 0.941f, 0.961f, 1.0f}
static const Jade::Math::Color MistyRose		= Jade::Math::Color(1.0f, 0.894f, 0.882f, 1.0f); //RGBA: {1.0f, 0.894f, 0.882f, 1.0f}
static const Jade::Math::Color Gainsboro		= Jade::Math::Color(0.863f, 0.863f, 0.863f, 1.0f); //RGBA: {0.863f, 0.863f, 0.863f, 1.0f}
static const Jade::Math::Color LightGrey		= Jade::Math::Color(0.827f, 0.827f, 0.827f, 1.0f); //RGBA: {0.827f, 0.827f, 0.827f, 1.0f}
static const Jade::Math::Color Silver			= Jade::Math::Color(0.753f, 0.753f, 0.753f, 1.0f); //RGBA: {0.753f, 0.753f, 0.753f, 1.0f}
static const Jade::Math::Color DarkGrey			= Jade::Math::Color(0.663f, 0.663f, 0.633f, 1.0f); //RGBA: {0.663f, 0.663f, 0.633f, 1.0f
static const Jade::Math::Color Gray				= Jade::Math::Color(0.502f, 0.502f, 0.502f, 1.0f); //RGBA: {0.502f, 0.502f, 0.502f, 1.0f}
static const Jade::Math::Color DimGray			= Jade::Math::Color(0.412f, 0.412f, 0.412f, 1.0f); //RGBA: {0.412f, 0.412f, 0.412f, 1.0f}
static const Jade::Math::Color LightSlateGray	= Jade::Math::Color(0.467f, 0.533f, 0.600f, 1.0f); //RGBA: {0.467f, 0.533f, 0.600f, 1.0f}
static const Jade::Math::Color SlateGray		= Jade::Math::Color(0.439f, 0.502f, 0.565f, 1.0f); //RGBA: {0.439f, 0.502f, 0.565f, 1.0f}
static const Jade::Math::Color DarkSlateGray	= Jade::Math::Color(0.184f, 0.310f, 0.310f, 1.0f); //RGBA: {0.184f, 0.310f, 0.310f, 1.0f}
static const Jade::Math::Color Black			= Jade::Math::Color(0.0f, 0.0f, 0.0f, 1.0f); //RGBA: {0.0f, 0.0f, 0.0f, 1.0f}