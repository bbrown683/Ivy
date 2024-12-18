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

// Assimp headers.
#include "assimp/Importer.hpp"
#include "assimp/Scene.h"
#include "assimp/postprocess.h"

#include "Core/Include.h"
#include "Graphics/Blender/Blender.h"
#include "Graphics/Mesh/Mesh.h"
#include "Math/Helper.h"

namespace Ivy
{
    namespace Graphics
    {
        /* \brief A model is a collection of triangular meshes. */ 
        class Model
        {
            Device device;
            Shader shader;
            Blender blender;

            // Mesh(s) used to draw our shape.
            std::vector<Mesh> meshes;

            // Transformations on the model.
            Math::Vector3 position;
            Math::Vector3 rotation;
            Math::Vector3 scale;

            bool blending;

        public:

            Model(Device device, Shader shader)
            {
                this->device = device;
                this->shader = shader;

                blender = Blender(device);
            }

            void Draw();
            void Blending(bool blending);
            void Load(std::string filename);

            std::vector<Mesh> GetMeshes() const;

            Math::Vector3 GetPosition() const;
            Math::Vector3 GetRotation() const;
            Math::Vector3 GetScale() const;

            void SetPosition(Math::Vector3 position);
            void SetRotation(Math::Vector3 rotation);
            void SetScale(Math::Vector3 scale);

        };
    }
}
