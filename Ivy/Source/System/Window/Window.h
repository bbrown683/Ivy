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

#include "System/Window/Win32Window.h"
#include "System/Window/X11Window.h"

namespace Ivy
{
    namespace System
    {
        //! \brief Multi-platform window implementation.
        class Window
        {            
            int width;
            int height;
            int x;
            int y;
            std::string title;
            bool fullscreen;

            //! \brief All of our windows use this interface for their general implementations 
            // to create interoperability for multiple operating systems.
            std::shared_ptr<IWindow> window;

        public:

            // Returns a boolean determining if the window is still active.
            bool IsOpen() const
            {
                return window->IsOpen();
            }

            // Returns the width of the window.
            int GetWidth() const
            {
                return window->GetWidth();
            }

            // Sets the width of the window.
            void SetWidth(int width) const
            {
                window->SetWidth(width);
            }

            // Returns the height of the window.
            int GetHeight() const
            {
                return window->GetHeight();
            }

            // Sets the height of the window.
            void SetHeight(int height) const
            {
                window->SetHeight(height);
            }

            // Returns the aspect ratio of the window.
            float GetAspectRatio() const
            {
                return window->GetAspectRatio();
            }

            //! \brief Determines if the rendering viewport needs to be resized.
            bool GetRenderViewportNeedsResize() const
            {
                return window->GetRenderViewportNeedsResize();
            }

            //! \brief Sets the value if the viewport needs to be resized;
            void SetRenderViewportNeedsResize(bool value) const
            {
                window->SetRenderViewportNeedsResize(value);
            }

            //! \brief Returns the platform display for the window.
            PlatformDisplay GetPlatformDisplay() const
            {
                return window->GetPlatformDisplay();
            }

            //! \brief Returns the platform handle for the window.
            PlatformWindow GetPlatformWindow() const
            {
                return window->GetPlatformWindow();
            }

            // Returns the title of the window.
            std::string GetTitle() const
            {
                return window->GetTitle();
            }

            // Sets the title of the window.
            void SetTitle(std::string title) const
            {
                window->SetTitle(title);
            }

            // Sets the icon of the window.
            void SetIcon(std::string filename) const
            {
                window->SetIcon(filename);
            }

            // Returns a boolean determining if the window is in fullscreen mode.
            bool IsFullscreen() const
            {
                return window->IsFullscreen();
            }

            // Returns a boolean determining if the window has focus.
            bool IsActive() const
            {
                return window->IsActive();
            }

            // Returns the underlying interface object of the window.
            std::shared_ptr<IWindow> GetIWindow() const
            {
                return window;
            }

            // Returns an object that manages timers related to the window.
            Timer GetTime() const
            {
                return window->GetTimer();
            }

            // Returns an object that handles window input.
            Input::Input GetInput() const
            {
                return window->GetInput();
            }

            Window() : window(nullptr) { }

            // Use this constructor.
            Window(int width, int height, int x, int y, std::string title, bool fullscreen)
            {
                this->width = width;
                this->height = height;
                this->x = x;
                this->y = y;
                this->title = title;
                this->fullscreen = fullscreen;
            }

            // Creates the window and returns a boolean if it was successful.
            bool Create()
            {
                // Create our window.
                window = std::make_shared<NativeWindow>(width, height, x, y, title, fullscreen);
                return window != nullptr;
            }

            // Runs through the main window messaging loop handling events.
            bool PollEvents() const
            {
                return window->PollWindowEvents();
            }

            // Closes the window and exits the application.
            void Close() const
            {
                window->Close();
            }
        };
    }
}



