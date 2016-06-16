#pragma once

/*
     __             ___      
    |__|____     __| _/____  
    |  \__  \   / __ |/ __ \ 
    |  |/ __ \_/ /_/ \  ___/ 
/\__|  (____  /\____ |\___  >
\______|    \/      \/    \/ 

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
// Jade default header.
// ===============================

// Includes all the capabilities of Jade.
#ifdef JADE_INCLUDE_ALL
#define JADE_INCLUDE_AUDIO
#define JADE_INCLUDE_CORE
#define JADE_INCLUDE_GRAPHICS
#define JADE_INCLUDE_INPUT
#define JADE_INCLUDE_MATH
#define JADE_INCLUDE_SYSTEM
#endif // JADE_INCLUDE_ALL

// Audio
#ifdef JADE_INCLUDE_AUDIO
#include "Audio/AudioDevice.h"
#endif // JADE_INCLUDE_AUDIO

// Core
#ifdef JADE_INCLUDE_CORE
#include "Core/Utility.h"
#include "Core/Exception/Exception.h"
#include "Core/Script/Script.h"
#endif // JADE_INCLUDE_CORE

// Graphics
#ifdef JADE_INCLUDE_GRAPHICS
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
#endif // JADE_INCLUDE_GRAPHICS

// Input
#ifdef JADE_INCLUDE_INPUT
#include "Input/Input.h"
#endif // JADE_INCLUDE_INPUT

// Math
#ifdef JADE_INCLUDE_MATH
#include "Math/Math.h"
#include "Math/Matrix.h"
#include "Math/Rectangle.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Vertex.h"
#endif // JADE_INCLUDE_MATH

// System
#ifdef JADE_INCLUDE_SYSTEM
#include "System/Configuration.h"
#include "System/File.h"
#include "System/Log.h"
#include "System/Window/Window.h"
#include "System/Window/WinMain.h"
#endif // JADE_INCLUDE_SYSTEM

// Retains the namespace style of declaration but
// with shorthand definitions.
#ifdef JADE_INCLUDE_AUDIO
#define JAudio Jade::Audio
#endif // JADE_INCLUDE_AUDIO
#ifdef JADE_INCLUDE_CORE
#define JCore Jade::Core
#endif // JADE_INCLUDE_CORE
#ifdef JADE_INCLUDE_GRAPHICS
#define JGraphics Jade::Graphics
#endif // JADE_INCLUDE_GRAPHICS
#ifdef JADE_INCLUDE_INPUT
#define JInput Jade::Input
#endif // JADE_INCLUDE_INPUT
#ifdef JADE_INCLUDE_MATH
#define JMath Jade::Math
#endif // JADE_INCLUDE_MATH
#ifdef JADE_INCLUDE_SYSTEM
#define JSystem Jade::System
#endif // JADE_INCLUDE_SYSTEM

// Include before calling header.
// Ultimate cleanliness without the namespace clutter. 
// This can possibly conflict with other definitions.
#ifdef JADE_USING_NAMESPACE
#ifdef JADE_INCLUDE_AUDIO
using namespace JAudio;
#endif // JADE_INCLUDE_AUDIO
#ifdef JADE_INCLUDE_CORE
using namespace JCore;
#endif // JADE_INCLUDE_CORE
#ifdef JADE_INCLUDE_GRAPHICS
using namespace JGraphics;
#endif // JADE_INCLUDE_GRAPHICS
#ifdef JADE_INCLUDE_INPUT
using namespace JInput;
#endif // JADE_INCLUDE_INPUT
#ifdef JADE_INCLUDE_MATH
using namespace JMath;
#endif // JADE_INCLUDE_MATH
#ifdef JADE_INCLUDE_SYSTEM
using namespace JSystem;
#endif // JADE_INCLUDE_SYSTEM
#endif // JADE_USING_NAMESPACE