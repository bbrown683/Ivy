﻿/*
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

// Main engine definitions.
#define IVY_USING_NAMESPACE 
#define IVY_INCLUDE_ALL

// Include the header.
#include "Ivy.h"

int main()
{
    // Creates a basic window that can be rendered with either graphics API.
    Window window(1080, 720, 100, 100, "Ivy Game Framework", false);
    if(window.Create())
    {
        // Creates a graphics device.
        Device device(window, GraphicsAPI::DirectX);

        Audio audio;

        if (device.Create())
        {
            device.SetDrawType(DrawType::Indexed);

            // Used to enable culling or wireframe modes.
            // Can also be pushed underneath sprite and model drawing.
            Rasterizer rasterizer(device);

            // Create our shaders.
            Shader modelShader(device, ".\\resources\\shaders\\ModelPixel.hlsl",
                ".\\resources\\shaders\\ModelVertex.hlsl");

            // Camera with initial position and target.
            Camera camera(device, Vector3(0.0f, 1.0f, -10.0f), Vector3(0.0f, 1.0f, 0.0f));

            // Dynamic model and font loading.
            // This allows us to load a new instance with the same object.
            Model model(device, modelShader);
            model.Load(".\\resources\\models\\MonoCube.dae");
            model.Blending(true);

            Font font(device, modelShader);
            font.Load(".\\resources\\fonts\\consola.ttf", 30);

            while (window.IsOpen())
            {
                // Rendering
                device.Clear(Color::CornflowerBlue);

                // Rotate and draw the models.
                if (window.GetInput().keyboard.IsKeyDown(Key::Shift))
                    model.SetRotation(Vector3(0.0f, 0.025f, 0.0f));

                model.Draw();
                //font.Draw("A", 0, 10);

                // Camera movement.
                // Setting a camera with no orbiting requires us to update
                // not only the camera position, but also the target.
                // This could be moved into a lua script at a future date.
                if (window.GetInput().keyboard.IsKeyDown(Key::W))
                {
                    camera.SetCameraPosition(camera.GetCameraPosition() + Vector3(0.0f, 0.0f, 0.25f));
                    camera.SetTargetPosition(camera.GetTargetPosition() + Vector3(0.0f, 0.0f, 0.25f));
                }
                if (window.GetInput().keyboard.IsKeyDown(Key::A))
                {
                    camera.SetCameraPosition(camera.GetCameraPosition() + Vector3(-0.25f, 0.0f, 0.0f));
                    camera.SetTargetPosition(camera.GetTargetPosition() + Vector3(-0.25f, 0.0f, 0.0f));
                }
                if (window.GetInput().keyboard.IsKeyDown(Key::S))
                {
                    camera.SetCameraPosition(camera.GetCameraPosition() + Vector3(0.0f, 0.0f, -0.25f));
                    camera.SetTargetPosition(camera.GetTargetPosition() + Vector3(0.0f, 0.0f, -0.25f));
                }
                if (window.GetInput().keyboard.IsKeyDown(Key::D))
                {
                    camera.SetCameraPosition(camera.GetCameraPosition() + Vector3(0.25f, 0.0f, 0.0f));
                    camera.SetTargetPosition(camera.GetTargetPosition() + Vector3(0.25f, 0.0f, 0.0f));
                }
                if (window.GetInput().keyboard.IsKeyDown(Key::Space))
                {
                    camera.SetCameraPosition(camera.GetCameraPosition() + Vector3(0.0f, 0.25f, 0.0f));
                    camera.SetTargetPosition(camera.GetTargetPosition() + Vector3(0.0f, 0.25f, 0.0f));
                }
                if (window.GetInput().keyboard.IsKeyDown(Key::Tab))
                {
                    camera.SetCameraPosition(camera.GetCameraPosition() + Vector3(0.0f, -0.25f, 0.0f));
                    camera.SetTargetPosition(camera.GetTargetPosition() + Vector3(0.0f, -0.25f, 0.0f));
                }

                // Example rasterizer mode swapping while rendering.
                if (window.GetInput().keyboard.IsKeyDown(Key::R))
                    rasterizer.SetRasterizerState(CullMode::Back, FillMode::Wireframe, WindMode::Clockwise);
                else
                    rasterizer.SetRasterizerState(CullMode::Back, FillMode::Solid, WindMode::Clockwise);

                // This will update the viewport and camera projection in the event of a window resize.
                camera.Update();

                // Swap buffers and perform system event loop.
                device.Present();
                window.PollEvents();

                // Submit close request if we detect user is exiting application.
                if (window.GetInput().keyboard.IsKeyDown(Key::Escape))
                    window.Close();
            }
        }
    }
    
    return 0;
}
