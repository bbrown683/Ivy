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

#include "Core/Utility.h"
#include "System/Window/Event.h"
#include "System/Window/IWindow.h"

namespace Ivy
{
    namespace System
    {
#ifdef IVY_PLATFORM_WINDOWS
        class Win32Window : public IWindow
        {
            HDC hDC;
            HWND hWnd;
            
            std::queue<Event> events;
            
            unsigned int width;
            unsigned int height;
            int x;
            int y;
            std::string title;
            bool fullscreen;

            bool open = false;
            bool viewportNeedsResize = false;

            Timer timer;
            Input::Input input;

        public:

            int GetWidth() override;
            void SetWidth(int value) override;
            int GetHeight() override;
            void SetHeight(int value) override;
            float GetAspectRatio() override;
            bool GetRenderViewportNeedsResize() override;
            void SetRenderViewportNeedsResize(bool value) override;
            int GetX() override;
            void SetX(int value) override;
            int GetY() override;
            void SetY(int value) override;
            std::string GetTitle() override;
            void SetTitle(std::string value) override;
            Math::Point<int> GetPosition() override;
            void SetPosition(int x, int y) override;
            void SetIcon(std::string filename) override;
            bool PollWindowEvents() override;
            void Close() override;
            PlatformDisplay GetPlatformDisplay() override;
            PlatformWindow GetPlatformWindow() override;
            bool Create() override;
            void Show() override;
            void Hide() override;
            void Restore() override;
            void Maximize() override;
            bool Minimized() override;
            void Minimize() override;
            bool Maximized() override;
            bool IsVisible() override;
            bool IsOpen() override;
            bool IsFullscreen() override;
            bool IsActive() override;
            Timer GetTimer() override;
            Input::Input GetInput() override;

            Win32Window(unsigned int width, unsigned int height, int x, int y, 
                std::string title, bool fullscreen)
            {
                this->width = width;
                this->height = height;
                this->x = x;
                this->y = y;
                this->title = title;
                this->fullscreen = fullscreen;

                if (!Win32Window::Create())
                    Win32Window::Close();
            }

            ~Win32Window()
            {
                if(open)
                    Win32Window::Close();
            }

            Input::Key ConvertVirtualKey(WPARAM key);
            bool RegisterWindowClass(HINSTANCE hInstance);
            void UnregisterWindowClass();
            LRESULT WindowEventHandler(UINT msg, WPARAM wParam, LPARAM lParam);
            static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        };

        typedef Win32Window NativeWindow;
#endif
    }
}