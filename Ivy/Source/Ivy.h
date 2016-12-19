#pragma once

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

// ===============================
// Ivy default header.
// ===============================

// Includes all the capabilities of Ivy.
#ifdef IVY_INCLUDE_ALL
#define IVY_INCLUDE_AUDIO
#define IVY_INCLUDE_CORE
#define IVY_INCLUDE_GRAPHICS
#define IVY_INCLUDE_INPUT
#define IVY_INCLUDE_MATH
#define IVY_INCLUDE_SYSTEM
#endif // IVY_INCLUDE_ALL

// Audio
#ifdef IVY_INCLUDE_AUDIO
#include "Audio/Audio.h"
#endif // IVY_INCLUDE_AUDIO

// Core
#ifdef IVY_INCLUDE_CORE
#include "Core/Utility.h"
#include "Core/Exception/Exception.h"
#endif // IVY_INCLUDE_CORE

// Graphics
#ifdef IVY_INCLUDE_GRAPHICS
#include "Graphics/Blender/Blender.h"
#include "Graphics/Buffer/ConstantBuffer.h"
#include "Graphics/Buffer/IndexBuffer.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Device/Device.h"
#include "Graphics/Font/Font.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Model/Model.h"
#include "Graphics/Rasterizer/Rasterizer.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Sprite/Sprite.h"
#include "Graphics/Texture/Texture.h"
#endif // IVY_INCLUDE_GRAPHICS

// Input
#ifdef IVY_INCLUDE_INPUT
#include "Input/Input.h"
#endif // IVY_INCLUDE_INPUT

// Math
#ifdef IVY_INCLUDE_MATH
#include "Math/Math.h"
#include "Math/Matrix.h"
#include "Math/Rectangle.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Vertex.h"
#endif // IVY_INCLUDE_MATH

// System
#ifdef IVY_INCLUDE_SYSTEM
#include "System/Configuration.h"
#include "System/File.h"
#include "System/Log.h"
#include "System/Window/Window.h"
#include "System/Window/WinMain.h"
#endif // IVY_INCLUDE_SYSTEM

// Retains the namespace style of declaration but
// with shorthand definitions.
#ifdef IVY_INCLUDE_AUDIO
#define JAudio Ivy::Audio
#endif // IVY_INCLUDE_AUDIO
#ifdef IVY_INCLUDE_CORE
#define JCore Ivy::Core
#endif // IVY_INCLUDE_CORE
#ifdef IVY_INCLUDE_GRAPHICS
#define JGraphics Ivy::Graphics
#endif // IVY_INCLUDE_GRAPHICS
#ifdef IVY_INCLUDE_INPUT
#define JInput Ivy::Input
#endif // IVY_INCLUDE_INPUT
#ifdef IVY_INCLUDE_MATH
#define JMath Ivy::Math
#endif // IVY_INCLUDE_MATH
#ifdef IVY_INCLUDE_SYSTEM
#define JSystem Ivy::System
#endif // IVY_INCLUDE_SYSTEM

// Include before calling header.
// Ultimate cleanliness without the namespace clutter. 
// This can possibly conflict with other definitions.
#ifdef IVY_USING_NAMESPACE
#ifdef IVY_INCLUDE_AUDIO
using namespace JAudio;
#endif // IVY_INCLUDE_AUDIO
#ifdef IVY_INCLUDE_CORE
using namespace JCore;
#endif // IVY_INCLUDE_CORE
#ifdef IVY_INCLUDE_GRAPHICS
using namespace JGraphics;
#endif // IVY_INCLUDE_GRAPHICS
#ifdef IVY_INCLUDE_INPUT
using namespace JInput;
#endif // IVY_INCLUDE_INPUT
#ifdef IVY_INCLUDE_MATH
using namespace JMath;
#endif // IVY_INCLUDE_MATH
#ifdef IVY_INCLUDE_SYSTEM
using namespace JSystem;
#endif // IVY_INCLUDE_SYSTEM
#endif // IVY_USING_NAMESPACE