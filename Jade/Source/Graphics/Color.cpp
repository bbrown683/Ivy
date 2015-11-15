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

static const Jade::Graphics::Color IndianRed		= Jade::Graphics::Color(0.804f, 0.361f, 0.361f, 1.0f); //RGBA: {0.804f, 0.361f, 0.361f, 1.0f}
static const Jade::Graphics::Color LightCoral		= Jade::Graphics::Color(0.941f, 0.502f, 0.502f, 1.0f);//RGBA: {0.941f, 0.502f, 0.502f, 1.0f}
static const Jade::Graphics::Color Salmon			= Jade::Graphics::Color(0.980f, 0.502f, 0.447f, 1.0f); //RGBA: {0.980f, 0.502f, 0.447f, 1.0f}
static const Jade::Graphics::Color DarkSalmon		= Jade::Graphics::Color(0.914f, 0.588f, 0.478f, 1.0f); //RGBA: {0.914f, 0.588f, 0.478f, 1.0f}
static const Jade::Graphics::Color LightSalmon		= Jade::Graphics::Color(1.0f, 0.627f, 0.478f, 1.0f); //RGBA: {1.0f, 0.627f, 0.478f, 1.0f}
static const Jade::Graphics::Color Crimson			= Jade::Graphics::Color(0.863f, 0.078f, 0.235f, 1.0f); //RGBA: {0.863f, 0.078f, 0.235f, 1.0f}
static const Jade::Graphics::Color Red				= Jade::Graphics::Color(1.0f, 0.0f, 0.0f, 1.0f); //RGBA: {1.0f, 0.0f, 0.0f, 1.0f}
static const Jade::Graphics::Color FireBrick		= Jade::Graphics::Color(0.698f, 0.133f, 0.133f, 1.0f); //RGBA: {0.698f, 0.133f, 0.133f, 1.0f}
static const Jade::Graphics::Color DarkRed			= Jade::Graphics::Color(0.545f, 0.0f, 0.0f, 1.0f); //RGBA: {0.545f, 0.0f, 0.0f, 1.0f}
static const Jade::Graphics::Color Pink				= Jade::Graphics::Color(1.0f, 0.753f, 0.796f, 1.0f); //RGBA: {1.0f, 0.753f, 0.796f, 1.0f}
static const Jade::Graphics::Color LightPink		= Jade::Graphics::Color(1.0f, 0.714f, 0.747f, 1.0f); //RGBA: {1.0f, 0.714f, 0.747f, 1.0f}
static const Jade::Graphics::Color HotPink			= Jade::Graphics::Color(1.0f, 0.410f, 0.747f, 1.0f); //RGBA: {1.0f, 0.410f, 0.747f, 1.0f}
static const Jade::Graphics::Color DeepPink			= Jade::Graphics::Color(1.0f, 0.078f, 0.576f, 1.0f);//RGBA: {1.0f, 0.078f, 0.576f, 1.0f}
static const Jade::Graphics::Color MediumVioletRed	= Jade::Graphics::Color(0.780f, 0.082f, 0.522f, 1.0f); //RGBA: {0.780f, 0.082f, 0.522f, 1.0f}
static const Jade::Graphics::Color PaleVioletRed	= Jade::Graphics::Color(0.859f, 0.439f, 0.576f, 1.0f); //RGBA: {0.859f, 0.439f, 0.576f, 1.0f}
static const Jade::Graphics::Color Coral			= Jade::Graphics::Color(1.0f, 0.627f, 0.478f, 1.0f); //RGBA: {1.0f, 0.627f, 0.478f, 1.0f}
static const Jade::Graphics::Color Tomato			= Jade::Graphics::Color(1.0f, 0.388f, 0.278f, 1.0f); //RGBA: {1.0f, 0.388f, 0.278f, 1.0f}
static const Jade::Graphics::Color OrangeRed		= Jade::Graphics::Color(1.0f, 0.271f, 0.0f, 1.0f); //RGBA: {1.0f, 0.271f, 0.0f, 1.0f}
static const Jade::Graphics::Color DarkOrange		= Jade::Graphics::Color(1.0f, 0.549f, 0.0f, 1.0f); //RGBA: {1.0f, 0.549f, 0.0f, 1.0f}
static const Jade::Graphics::Color Orange			= Jade::Graphics::Color(1.0f, 0.647f, 0.0f, 1.0f); //RGBA: {1.0f, 0.647f, 0.0f, 1.0f}
static const Jade::Graphics::Color Gold				= Jade::Graphics::Color(1.0f, 0.843f, 0.0f, 1.0f); //RGBA: {1.0f, 0.843f, 0.0f, 1.0f}
static const Jade::Graphics::Color Yellow			= Jade::Graphics::Color(1.0f, 1.0f, 0.0f, 1.0f); //RGBA: {1.0f, 1.0f, 0.0f, 1.0f}
static const Jade::Graphics::Color LightYellow		= Jade::Graphics::Color(1.0f, 1.0f, 0.878f, 1.0f); //RGBA: {1.0f, 1.0f, 0.878f, 1.0f}
static const Jade::Graphics::Color LemonChion		= Jade::Graphics::Color(0.980f, 0.980f, 0.804f, 1.0f); //RGBA: {0.980f, 0.980f, 0.804f, 1.0f}
static const Jade::Graphics::Color LightGoldenRodYellow = Jade::Graphics::Color(0.980f, 0.980f, 0.824f, 1.0f); //RGBA: {0.980f, 0.980f, 0.824f, 1.0f}
static const Jade::Graphics::Color PapayaWhip		= Jade::Graphics::Color(1.0f, 0.937f, 0.835f, 1.0f); //RGBA: {1.0f, 0.937f, 0.835f, 1.0f}
static const Jade::Graphics::Color Moccasin			= Jade::Graphics::Color(1.0f, 0.894f, 0.710f, 1.0f); //RGBA: {1.0f, 0.894f, 0.710f, 1.0f}
static const Jade::Graphics::Color PeachPu			= Jade::Graphics::Color(1.0f, 0.855f, 0.725f, 1.0f); //RGBA: {1.0f, 0.855f, 0.725f, 1.0f}
static const Jade::Graphics::Color PaleGoldenRod	= Jade::Graphics::Color(0.933f, 0.910f, 0.667f, 1.0f); //RGBA: {0.933f, 0.910f, 0.667f, 1.0f}
static const Jade::Graphics::Color Khaki			= Jade::Graphics::Color(0.941f, 0.902f, 0.549f, 1.0f); //RGBA: {0.941f, 0.902f, 0.549f, 1.0f}
static const Jade::Graphics::Color DarkKhaki		= Jade::Graphics::Color(0.741f, 0.718f, 0.420f, 1.0f); //RGBA: {0.741f, 0.718f, 0.420f, 1.0f}
static const Jade::Graphics::Color Lavender			= Jade::Graphics::Color(0.902f, 0.902f, 0.980f, 1.0f); //RGBA: {0.902f, 0.902f, 0.980f, 1.0f}
static const Jade::Graphics::Color Thistle			= Jade::Graphics::Color(0.847f, 0.749f, 0.847f, 1.0f); //RGBA: {0.847f, 0.749f, 0.847f, 1.0f}
static const Jade::Graphics::Color Plum				= Jade::Graphics::Color(0.867f, 0.627f, 0.867f, 1.0f); //RGBA: {0.867f, 0.627f, 0.867f, 1.0f}
static const Jade::Graphics::Color Violet			= Jade::Graphics::Color(0.933f, 0.510f, 0.933f, 1.0f); //RGBA: {0.933f, 0.510f, 0.933f, 1.0f}
static const Jade::Graphics::Color Orchid			= Jade::Graphics::Color(0.655f, 0.439f, 0.839f, 1.0f); //RGBA: {0.655f, 0.439f, 0.839f, 1.0f}
static const Jade::Graphics::Color Magenta			= Jade::Graphics::Color(1.0f, 0.0f, 1.0f, 1.0f); //RGBA: {1.0f, 0.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color MediumOrchid		= Jade::Graphics::Color(0.729f, 0.333f, 0.827f, 1.0f); //RGBA: {0.729f, 0.333f, 0.827f, 1.0f}
static const Jade::Graphics::Color MediumPurple		= Jade::Graphics::Color(0.576f, 0.439f, 0.859f, 1.0f); //RGBA: {0.576f, 0.439f, 0.859f, 1.0f}
static const Jade::Graphics::Color BlueViolet		= Jade::Graphics::Color(0.541f, 0.169f, 0.886f, 1.0f); //RGBA: {0.541f, 0.169f, 0.886f, 1.0f}
static const Jade::Graphics::Color DarkViolet		= Jade::Graphics::Color(0.580f, 0.0f, 0.827f, 1.0f); //RGBA: {0.580f, 0.0f, 0.827f, 1.0f}
static const Jade::Graphics::Color DarkOrchid		= Jade::Graphics::Color(0.600f, 0.196f, 0.800f, 1.0f); //RGBA: {0.600f, 0.196f, 0.800f, 1.0f}
static const Jade::Graphics::Color DarkMagenta		= Jade::Graphics::Color(0.545f, 0.0f, 0.545f, 1.0f); //RGBA: {0.545f, 0.0f, 0.545f, 1.0f}
static const Jade::Graphics::Color Purple			= Jade::Graphics::Color(0.502f, 0.0f, 0.502f, 1.0f); //RGBA: {0.502f, 0.0f, 0.502f, 1.0f}
static const Jade::Graphics::Color Indigo			= Jade::Graphics::Color(0.294f, 0.0f, 0.510f, 1.0f); //RGBA: {0.294f, 0.0f, 0.510f, 1.0f}
static const Jade::Graphics::Color SlateBlue		= Jade::Graphics::Color(0.416f, 0.353f, 0.804f, 1.0f); //RGBA: {0.416f, 0.353f, 0.804f, 1.0f}
static const Jade::Graphics::Color DarkSlateBlue	= Jade::Graphics::Color(0.282f, 0.239f, 0.545f, 1.0f); //RGBA: {0.282f, 0.239f, 0.545f, 1.0f}
static const Jade::Graphics::Color GreenYellow		= Jade::Graphics::Color(0.678f, 1.0f, 0.184f, 1.0f); //RGBA: {0.678f, 1.0f, 0.184f, 1.0f}
static const Jade::Graphics::Color Chartreuse		= Jade::Graphics::Color(0.498f, 1.0f, 0.0f, 1.0f); //RGBA: {0.498f, 1.0f, 0.0f, 1.0f}
static const Jade::Graphics::Color LawnGreen		= Jade::Graphics::Color(0.486f, 0.988f, 0.0f, 1.0f); //RGBA: {0.486f, 0.988f, 0.0f, 1.0f}
static const Jade::Graphics::Color Lime				= Jade::Graphics::Color(0.0f, 1.0f, 0.0f, 1.0f); //RGBA: {0.0f, 1.0f, 0.0f, 1.0f}
static const Jade::Graphics::Color LimeGreen		= Jade::Graphics::Color(0.196f, 0.804f, 0.196f, 1.0f); //RGBA: {0.196f, 0.804f, 0.196f, 1.0f}
static const Jade::Graphics::Color PaleGreen		= Jade::Graphics::Color(0.596f, 0.984f, 0.596f, 1.0f); //RGBA: {0.596f, 0.984f, 0.596f, 1.0f}
static const Jade::Graphics::Color LightGreen		= Jade::Graphics::Color(0.565f, 0.933f, 0.565f, 1.0f); //RGBA: {0.565f, 0.933f, 0.565f, 1.0f}
static const Jade::Graphics::Color MediumSpringGreen = Jade::Graphics::Color(0.0f, 0.980f, 0.604f, 1.0f); //RGBA: {0.0f, 0.980f, 0.604f, 1.0f}
static const Jade::Graphics::Color SpringGreen		= Jade::Graphics::Color(0.0f, 1.0f, 0.498f, 1.0f); //RGBA: {0.0f, 1.0f, 0.498f, 1.0f}
static const Jade::Graphics::Color MediumSeaGreen	= Jade::Graphics::Color(0.235f, 0.702f, 0.443f, 1.0f); //RGBA: {0.235f, 0.702f, 0.443f, 1.0f}
static const Jade::Graphics::Color SeaGreen			= Jade::Graphics::Color(0.180f, 0.545f, 0.341f, 1.0f); //RGBA: {0.180f, 0.545f, 0.341f, 1.0f}
static const Jade::Graphics::Color ForestGreen		= Jade::Graphics::Color(0.133f, 0.545f, 0.133f, 1.0f); //RGBA: {0.133f, 0.545f, 0.133f, 1.0f}
static const Jade::Graphics::Color Green			= Jade::Graphics::Color(0.0f, 0.502f, 0.0f, 1.0f); //RGBA: {0.0f, 0.502f, 0.0f, 1.0f}
static const Jade::Graphics::Color DarkGreen		= Jade::Graphics::Color(0.0f, 0.392f, 0.0f, 1.0f); //RGBA: {0.0f, 0.392f, 0.0f, 1.0f}
static const Jade::Graphics::Color YellowGreen		= Jade::Graphics::Color(0.604f, 0.804f, 0.196f, 1.0f); //RGBA: {0.604f, 0.804f, 0.196f, 1.0f}
static const Jade::Graphics::Color OliveDrab		= Jade::Graphics::Color(0.420f, 0.557f, 0.137f, 1.0f); //RGBA: {0.420f, 0.557f, 0.137f, 1.0f}
static const Jade::Graphics::Color Olive			= Jade::Graphics::Color(0.502f, 0.502f, 0.0f, 1.0f); //RGBA: {0.502f, 0.502f, 0.0f, 1.0f}
static const Jade::Graphics::Color DarkOliveGreen	= Jade::Graphics::Color(0.333f, 0.420f, 0.184f, 1.0f); //RGBA: {0.333f, 0.420f, 0.184f, 1.0f}
static const Jade::Graphics::Color MediumAquamarine = Jade::Graphics::Color(0.400f, 0.804f, 0.667f, 1.0f); //RGBA: {0.400f, 0.804f, 0.667f, 1.0f}
static const Jade::Graphics::Color DarkSeaGreen		= Jade::Graphics::Color(0.561f, 0.737f, 0.561f, 1.0f); //RGBA: {0.561f, 0.737f, 0.561f, 1.0f}
static const Jade::Graphics::Color LightSeaGreen	= Jade::Graphics::Color(0.125f, 0.698f, 0.667f, 1.0f); //RGBA: {0.125f, 0.698f, 0.667f, 1.0f}
static const Jade::Graphics::Color DarkCyan			= Jade::Graphics::Color(0.0f, 0.545f, 0.545f, 1.0f); //RGBA: {0.0f, 0.545f, 0.545f, 1.0f}
static const Jade::Graphics::Color Teal				= Jade::Graphics::Color(0.0f, 0.502f, 0.502f, 1.0f); //RGBA: {0.0f, 0.502f, 0.502f, 1.0f}
static const Jade::Graphics::Color Aqua				= Jade::Graphics::Color(0.0f, 1.0f, 1.0f, 1.0f); //RGBA: {0.0f, 1.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color Cyan				= Jade::Graphics::Color(0.0f, 1.0f, 1.0f, 1.0f); //RGBA: {0.0f, 1.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color LightCyan		= Jade::Graphics::Color(0.878f, 1.0f, 1.0f, 1.0f); //RGBA: {0.878f, 1.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color PaleTurquoise	= Jade::Graphics::Color(0.686f, 0.933f, 0.933f, 1.0f); //RGBA: {0.686f, 0.933f, 0.933f, 1.0f}
static const Jade::Graphics::Color Aquamarine		= Jade::Graphics::Color(0.498f, 1.0f, 0.831f, 1.0f); //RGBA: {0.498f, 1.0f, 0.831f, 1.0f}
static const Jade::Graphics::Color Turquoise		= Jade::Graphics::Color(0.251f, 0.878f, 0.816f, 1.0f); //RGBA: {0.251f, 0.878f, 0.816f, 1.0f}
static const Jade::Graphics::Color MediumTurquoise	= Jade::Graphics::Color(0.282f, 0.820f, 0.800f, 1.0f); //RGBA: {0.282f, 0.820f, 0.800f, 1.0f}
static const Jade::Graphics::Color DarkTurquoise	= Jade::Graphics::Color(0.0f, 0.808f, 0.820f, 1.0f); //RGBA: {0.0f, 0.808f, 0.820f, 1.0f}
static const Jade::Graphics::Color CadetBlue		= Jade::Graphics::Color(0.373f, 0.620f, 0.627f, 1.0f); //RGBA: {0.373f, 0.620f, 0.627f, 1.0f}
static const Jade::Graphics::Color SteelBlue		= Jade::Graphics::Color(0.275f, 0.510f, 0.706f, 1.0f); //RGBA: {0.275f, 0.510f, 0.706f, 1.0f}
static const Jade::Graphics::Color LightSteelBlue	= Jade::Graphics::Color(0.690f, 0.769f, 0.871f, 1.0f); //RGBA: {0.690f, 0.769f, 0.871f, 1.0f}
static const Jade::Graphics::Color LightBlue		= Jade::Graphics::Color(0.678f, 0.847f, 0.902f, 1.0f); //RGBA: {0.678f, 0.847f, 0.902f, 1.0f}
static const Jade::Graphics::Color PowderBlue		= Jade::Graphics::Color(0.690f, 0.878f, 0.902f, 1.0f); //RGBA: {0.690f, 0.878f, 0.902f, 1.0f}
static const Jade::Graphics::Color SkyBlue			= Jade::Graphics::Color(0.529f, 0.808f, 0.922f, 1.0f); //RGBA: {0.529f, 0.808f, 0.922f, 1.0f}
static const Jade::Graphics::Color LightSkyBlue		= Jade::Graphics::Color(0.529f, 0.808f, 0.980f, 1.0f); //RGBA: {0.529f, 0.808f, 0.980f, 1.0f}
static const Jade::Graphics::Color DeepSkyBlue		= Jade::Graphics::Color(0.0f, 0.749f, 1.0f, 1.0f); //RGBA: {0.0f, 0.749f, 1.0f, 1.0f}
static const Jade::Graphics::Color DodgerBlue		= Jade::Graphics::Color(0.118f, 0.565f, 1.0f, 1.0f); //RGBA: {0.118f, 0.565f, 1.0f, 1.0f}
static const Jade::Graphics::Color CornflowerBlue	= Jade::Graphics::Color(0.392f, 0.584f, 0.929f, 1.0f); //RGBA: {0.392f, 0.584f, 0.929f, 1.0f}
static const Jade::Graphics::Color MediumSlateBlue	= Jade::Graphics::Color(0.482f, 0.408f, 0.933f, 1.0f); //RGBA: {0.482f, 0.408f, 0.933f, 1.0f}
static const Jade::Graphics::Color RoyalBlue		= Jade::Graphics::Color(0.255f, 0.412f, 0.882f, 1.0f); //RGBA: {0.255f, 0.412f, 0.882f, 1.0f}
static const Jade::Graphics::Color Blue				= Jade::Graphics::Color(0.0f, 0.0f, 1.0f, 1.0f); //RGBA: {0.0f, 0.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color MediumBlue		= Jade::Graphics::Color(0.0f, 0.0f, 0.804f, 1.0f); //RGBA: {0.0f, 0.0f, 0.804f, 1.0f}
static const Jade::Graphics::Color DarkBlue			= Jade::Graphics::Color(0.0f, 0.0f, 0.545f, 1.0f); //RGBA: {0.0f, 0.0f, 0.545f, 1.0f}
static const Jade::Graphics::Color Navy				= Jade::Graphics::Color(0.0f, 0.0f, 0.502f, 1.0f); //RGBA: {0.0f, 0.0f, 0.502f, 1.0f}
static const Jade::Graphics::Color MidnightBlue		= Jade::Graphics::Color(0.098f, 0.098f, 0.439f, 1.0f); //RGBA: {0.098f, 0.098f, 0.439f, 1.0f}
static const Jade::Graphics::Color Cornsilk			= Jade::Graphics::Color(1.0f, 0.973f, 0.863f, 1.0f); //RGBA: {1.0f, 0.973f, 0.863f, 1.0f}
static const Jade::Graphics::Color BlanchedAlmond	= Jade::Graphics::Color(1.0f, 0.922f, 0.804f, 1.0f); //RGBA: {1.0f, 0.922f, 0.804f, 1.0f}
static const Jade::Graphics::Color Bisque			= Jade::Graphics::Color(1.0f, 0.894f, 0.769f, 1.0f); //RGBA: {1.0f, 0.894f, 0.769f, 1.0f}
static const Jade::Graphics::Color NavajoWhite		= Jade::Graphics::Color(1.0f, 0.871f, 0.678f, 1.0f); //RGBA: {1.0f, 0.871f, 0.678f, 1.0f}
static const Jade::Graphics::Color Wheat			= Jade::Graphics::Color(0.961f, 0.871f, 0.702f, 1.0f); //RGBA: {0.961f, 0.871f, 0.702f, 1.0f}
static const Jade::Graphics::Color BurlyWood		= Jade::Graphics::Color(0.871f, 0.722f, 0.529f, 1.0f); //RGBA: {0.871f, 0.722f, 0.529f, 1.0f}
static const Jade::Graphics::Color Tan				= Jade::Graphics::Color(0.824f, 0.706f, 0.549f, 1.0f); //RGBA: {0.824f, 0.706f, 0.549f, 1.0f}
static const Jade::Graphics::Color RosyBrown		= Jade::Graphics::Color(0.737f, 0.561f, 0.561f, 1.0f); //RGBA: {0.737f, 0.561f, 0.561f, 1.0f}
static const Jade::Graphics::Color SandyBrown		= Jade::Graphics::Color(0.957f, 0.643f, 0.376f, 1.0f); //RGBA: {0.957f, 0.643f, 0.376f, 1.0f}
static const Jade::Graphics::Color Goldenrod		= Jade::Graphics::Color(0.855f, 0.647f, 0.125f, 1.0f); //RGBA: {0.855f, 0.647f, 0.125f, 1.0f}
static const Jade::Graphics::Color DarkGoldenrod	= Jade::Graphics::Color(0.722f, 0.525f, 0.043f, 1.0f); //RGBA: {0.722f, 0.525f, 0.043f, 1.0f}
static const Jade::Graphics::Color Peru				= Jade::Graphics::Color(0.804f, 0.522f, 0.247f, 1.0f); //RGBA: {0.804f, 0.522f, 0.247f, 1.0f}
static const Jade::Graphics::Color Chocolate		= Jade::Graphics::Color(0.824f, 0.412f, 0.118f, 1.0f); //RGBA: {0.824f, 0.412f, 0.118f, 1.0f}
static const Jade::Graphics::Color SaddleBrown		= Jade::Graphics::Color(0.545f, 0.271f, 0.075f, 1.0f); //RGBA: {0.545f, 0.271f, 0.075f, 1.0f}
static const Jade::Graphics::Color Sienna			= Jade::Graphics::Color(0.627f, 0.322f, 0.176f, 1.0f); //RGBA: {0.627f, 0.322f, 0.176f, 1.0f}
static const Jade::Graphics::Color Brown			= Jade::Graphics::Color(0.647f, 0.165f, 0.165f, 1.0f); //RGBA: {0.647f, 0.165f, 0.165f, 1.0f}
static const Jade::Graphics::Color Maroon			= Jade::Graphics::Color(0.502f, 0.0f, 0.0f, 1.0f); //RGBA: {0.502f, 0.0f, 0.0f, 1.0f}
static const Jade::Graphics::Color White			= Jade::Graphics::Color(1.0f, 1.0f, 1.0f, 1.0f); //RGBA: {1.0f, 1.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color Snow				= Jade::Graphics::Color(1.0f, 0.980f, 0.980f, 1.0f); //RGBA: {1.0f, 0.980f, 0.980f, 1.0f}
static const Jade::Graphics::Color Honeydew			= Jade::Graphics::Color(0.941f, 1.0f, 0.941f, 1.0f); //RGBA: {0.941f, 1.0f, 0.941f, 1.0f}
static const Jade::Graphics::Color MintCream		= Jade::Graphics::Color(0.961f, 1.0f, 0.980f, 1.0f); //RGBA: {0.961f, 1.0f, 0.980f, 1.0f}
static const Jade::Graphics::Color Azure			= Jade::Graphics::Color(0.941f, 1.0f, 1.0f, 1.0f); //RGBA: {0.941f, 1.0f, 1.0f, 1.0f}
static const Jade::Graphics::Color AliceBlue		= Jade::Graphics::Color(0.941f, 0.973f, 1.0f, 1.0f); //RGBA: {0.941f, 0.973f, 1.0f, 1.0f}
static const Jade::Graphics::Color GhostWhite		= Jade::Graphics::Color(0.973f, 0.973f, 1.0f, 1.0f); //RGBA: {0.973f, 0.973f, 1.0f, 1.0f}
static const Jade::Graphics::Color WhiteSmoke		= Jade::Graphics::Color(0.961f, 0.961f, 0.961f, 1.0f); //RGBA: {0.961f, 0.961f, 0.961f, 1.0f}
static const Jade::Graphics::Color SeaShell			= Jade::Graphics::Color(1.0f, 0.961f, 0.933f, 1.0f); //RGBA: {1.0f, 0.961f, 0.933f, 1.0f}
static const Jade::Graphics::Color Beige			= Jade::Graphics::Color(0.961f, 0.961f, 0.863f, 1.0f); //RGBA: {0.961f, 0.961f, 0.863f, 1.0f}
static const Jade::Graphics::Color OldLace			= Jade::Graphics::Color(0.992f, 0.961f, 0.902f, 1.0f); //RGBA: {0.992f, 0.961f, 0.902f, 1.0f}
static const Jade::Graphics::Color FloralWhite		= Jade::Graphics::Color(1.0f, 0.980f, 0.941f, 1.0f); //RGBA: {1.0f, 0.980f, 0.941f, 1.0f}
static const Jade::Graphics::Color Ivory			= Jade::Graphics::Color(1.0f, 1.0f, 0.941f, 1.0f); //RGBA: {1.0f, 1.0f, 0.941f, 1.0f}
static const Jade::Graphics::Color AntiqueWhite		= Jade::Graphics::Color(0.980f, 0.922f, 0.843f, 1.0f); //RGBA: {0.980f, 0.922f, 0.843f, 1.0f}
static const Jade::Graphics::Color Linen			= Jade::Graphics::Color(0.980f, 0.941f, 0.902f, 1.0f); //RGBA: {0.980f, 0.941f, 0.902f, 1.0f}
static const Jade::Graphics::Color LavenderBlush	= Jade::Graphics::Color(1.0f, 0.941f, 0.961f, 1.0f); //RGBA: {1.0f, 0.941f, 0.961f, 1.0f}
static const Jade::Graphics::Color MistyRose		= Jade::Graphics::Color(1.0f, 0.894f, 0.882f, 1.0f); //RGBA: {1.0f, 0.894f, 0.882f, 1.0f}
static const Jade::Graphics::Color Gainsboro		= Jade::Graphics::Color(0.863f, 0.863f, 0.863f, 1.0f); //RGBA: {0.863f, 0.863f, 0.863f, 1.0f}
static const Jade::Graphics::Color LightGrey		= Jade::Graphics::Color(0.827f, 0.827f, 0.827f, 1.0f); //RGBA: {0.827f, 0.827f, 0.827f, 1.0f}
static const Jade::Graphics::Color Silver			= Jade::Graphics::Color(0.753f, 0.753f, 0.753f, 1.0f); //RGBA: {0.753f, 0.753f, 0.753f, 1.0f}
static const Jade::Graphics::Color DarkGrey			= Jade::Graphics::Color(0.663f, 0.663f, 0.633f, 1.0f); //RGBA: {0.663f, 0.663f, 0.633f, 1.0f
static const Jade::Graphics::Color Gray				= Jade::Graphics::Color(0.502f, 0.502f, 0.502f, 1.0f); //RGBA: {0.502f, 0.502f, 0.502f, 1.0f}
static const Jade::Graphics::Color DimGray			= Jade::Graphics::Color(0.412f, 0.412f, 0.412f, 1.0f); //RGBA: {0.412f, 0.412f, 0.412f, 1.0f}
static const Jade::Graphics::Color LightSlateGray	= Jade::Graphics::Color(0.467f, 0.533f, 0.600f, 1.0f); //RGBA: {0.467f, 0.533f, 0.600f, 1.0f}
static const Jade::Graphics::Color SlateGray		= Jade::Graphics::Color(0.439f, 0.502f, 0.565f, 1.0f); //RGBA: {0.439f, 0.502f, 0.565f, 1.0f}
static const Jade::Graphics::Color DarkSlateGray	= Jade::Graphics::Color(0.184f, 0.310f, 0.310f, 1.0f); //RGBA: {0.184f, 0.310f, 0.310f, 1.0f}
static const Jade::Graphics::Color Black			= Jade::Graphics::Color(0.0f, 0.0f, 0.0f, 1.0f); //RGBA: {0.0f, 0.0f, 0.0f, 1.0f}