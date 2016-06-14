#include "Win32Window.h"

int Jade::System::Win32Window::GetWidth()
{
    return width;
}

void Jade::System::Win32Window::SetWidth(int value)
{

}

int Jade::System::Win32Window::GetHeight()
{
    return height;
}

void Jade::System::Win32Window::SetHeight(int value)
{

}

float Jade::System::Win32Window::GetAspectRatio()
{
    return width / static_cast<float>(height);
}

bool Jade::System::Win32Window::GetRenderViewportNeedsResize()
{
    return false;
}

void Jade::System::Win32Window::SetRenderViewportNeedsResize(bool value)
{

}

int Jade::System::Win32Window::GetX()
{
    return x;
}

void Jade::System::Win32Window::SetX(int value)
{

}

int Jade::System::Win32Window::GetY()
{
    return y;
}

void Jade::System::Win32Window::SetY(int value)
{

}

istring Jade::System::Win32Window::GetTitle()
{
    return title;
}

void Jade::System::Win32Window::SetTitle(istring value)
{
    SetWindowText(hWnd, value.c_str());
    this->title = title;
}

Jade::Math::Point<int> Jade::System::Win32Window::GetPosition()
{
    return Math::Point<int>(x, y);
}

void Jade::System::Win32Window::SetPosition(int x, int y)
{

}

void Jade::System::Win32Window::SetIcon(std::string filename)
{

}

bool Jade::System::Win32Window::PollWindowEvents()
{
    MSG msg;
    while(PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (events.empty())
        return false;

    Event event = events.front();
    events.pop();

    return true;
}

void Jade::System::Win32Window::Close()
{
    RemoveProp(hWnd, TEXT("WINDOW"));
    UnregisterWindowClass();
    DestroyWindow(hWnd);
    open = false;

    std::cout << "Window closing..." << std::endl;
}

PlatformDisplay Jade::System::Win32Window::GetPlatformDisplay()
{
    return hDC;
}

PlatformWindow Jade::System::Win32Window::GetPlatformWindow()
{
    return hWnd;
}

bool Jade::System::Win32Window::Create()
{
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    if(RegisterWindowClass(hInstance))
    {
        DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_OVERLAPPED;

        HWND hWnd = CreateWindow(TEXT("JADE_APP"), title.c_str(), dwStyle,
            x, y, width, height, nullptr, nullptr, hInstance, nullptr);
    
        if (!hWnd)
            return false;

        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        this->hDC = GetDC(hWnd);
        this->hWnd = hWnd;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->title = title;

        // This will allow us to store the reference inside the Window Procedure.
        SetProp(hWnd, TEXT("WINDOW"), this);

        std::cout << "Window created..." << std::endl;

        return open = true;
    }

    return false;
}

void Jade::System::Win32Window::Show()
{
    ShowWindow(hWnd, SW_SHOW);
}

void Jade::System::Win32Window::Hide()
{
    ShowWindow(hWnd, SW_HIDE);
}

void Jade::System::Win32Window::Restore()
{

}

void Jade::System::Win32Window::Maximize()
{

}

bool Jade::System::Win32Window::Minimized()
{
    return false;
}

void Jade::System::Win32Window::Minimize()
{

}

bool Jade::System::Win32Window::Maximized()
{
    return false;
}

bool Jade::System::Win32Window::IsVisible()
{
    return false;
}

bool Jade::System::Win32Window::IsOpen()
{
    return open;
}

bool Jade::System::Win32Window::IsFullscreen()
{
    return fullscreen;
}

bool Jade::System::Win32Window::IsActive()
{
    return false;
}

Jade::System::Timer Jade::System::Win32Window::GetTimer()
{
    return timer;
}

Jade::Input::Input Jade::System::Win32Window::GetInput()
{
    return input;
}

Jade::Input::Key Jade::System::Win32Window::ConvertVirtualKey(WPARAM key)
{
    switch (key)
    {
    case VK_BACK: return Input::Key::Backspace;
    case VK_TAB: return Input::Key::Tab;
    case VK_SHIFT: return Input::Key::Shift;
    case VK_CONTROL: return Input::Key::Control;
    case VK_MENU: return Input::Key::Alt;
    case VK_PAUSE: return Input::Key::PauseBreak;
    case VK_CAPITAL: return Input::Key::CapsLock;
    case VK_ESCAPE: return Input::Key::Escape;
    case VK_SPACE: return Input::Key::Space;
    case VK_PRIOR: return Input::Key::PageUp;
    case VK_NEXT: return Input::Key::PageDown;
    case VK_END: return Input::Key::End;
    case VK_HOME: return Input::Key::Home;
    case VK_LEFT: return Input::Key::Left;
    case VK_UP: return Input::Key::Up;
    case VK_RIGHT: return Input::Key::Right;
    case VK_DOWN: return Input::Key::Down;
    case VK_SNAPSHOT: return Input::Key::PrintScreen;
    case VK_INSERT: return Input::Key::Insert;
    case VK_DELETE: return Input::Key::Delete;
    case 0x30: return Input::Key::Digit0;
    case 0x31: return Input::Key::Digit1;
    case 0x32: return Input::Key::Digit2;
    case 0x33: return Input::Key::Digit3;
    case 0x34: return Input::Key::Digit4;
    case 0x35: return Input::Key::Digit5;
    case 0x36: return Input::Key::Digit6;
    case 0x37: return Input::Key::Digit7;
    case 0x38: return Input::Key::Digit8;
    case 0x39: return Input::Key::Digit9;
    case 0x41: return Input::Key::A;
    case 0x42: return Input::Key::B;
    case 0x43: return Input::Key::C;
    case 0x44: return Input::Key::D;
    case 0x45: return Input::Key::E;
    case 0x46: return Input::Key::F;
    case 0x47: return Input::Key::G;
    case 0x48: return Input::Key::H;
    case 0x49: return Input::Key::I;
    case 0x4A: return Input::Key::J;
    case 0x4B: return Input::Key::K;
    case 0x4C: return Input::Key::L;
    case 0x4D: return Input::Key::M;
    case 0x4E: return Input::Key::N;
    case 0x4F: return Input::Key::O;
    case 0x50: return Input::Key::P;
    case 0x51: return Input::Key::Q;
    case 0x52: return Input::Key::R;
    case 0x53: return Input::Key::S;
    case 0x54: return Input::Key::T;
    case 0x55: return Input::Key::U;
    case 0x56: return Input::Key::V;
    case 0x57: return Input::Key::W;
    case 0x58: return Input::Key::X;
    case 0x59: return Input::Key::Y;
    case 0x5A: return Input::Key::Z;
    case VK_NUMPAD0: return Input::Key::NumberPad0;
    case VK_NUMPAD1: return Input::Key::NumberPad1;
    case VK_NUMPAD2: return Input::Key::NumberPad2;
    case VK_NUMPAD3: return Input::Key::NumberPad3;
    case VK_NUMPAD4: return Input::Key::NumberPad4;
    case VK_NUMPAD5: return Input::Key::NumberPad5;
    case VK_NUMPAD6: return Input::Key::NumberPad6;
    case VK_NUMPAD7: return Input::Key::NumberPad7;
    case VK_NUMPAD8: return Input::Key::NumberPad8;
    case VK_NUMPAD9: return Input::Key::NumberPad9;
    case VK_F1: return Input::Key::F1;
    case VK_F2: return Input::Key::F2;
    case VK_F3: return Input::Key::F3;
    case VK_F4: return Input::Key::F4;
    case VK_F5: return Input::Key::F5;
    case VK_F6: return Input::Key::F6;
    case VK_F7: return Input::Key::F7;
    case VK_F8: return Input::Key::F8;
    case VK_F9: return Input::Key::F9;
    case VK_F10: return Input::Key::F10;
    case VK_F11: return Input::Key::F11;
    case VK_F12: return Input::Key::F12;
    default: return Input::Key::Unknown;
    }
}

bool Jade::System::Win32Window::RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = WindowProcedure;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = reinterpret_cast<HBRUSH>(NULL_BRUSH);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = TEXT("JADE_APP");
    wcex.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
        return false;

    return true;
}

void Jade::System::Win32Window::UnregisterWindowClass()
{
    UnregisterClass(TEXT("JADE_APP"), GetModuleHandle(nullptr));
}

LRESULT Jade::System::Win32Window::WindowEventHandler(UINT msg, WPARAM wParam, LPARAM lParam)
{
    Event event;

    switch (msg)
    {
    case WM_CLOSE:
        event = Event::WindowClosed;
        Close();
        events.push(event);
        break;
    case WM_CREATE:
        event = Event::WindowCreated;
        events.push(event);
        break;
    case WM_KEYDOWN:
        event = Event::KeyPressed;
        input.keyboard.SetKeyState(ConvertVirtualKey(wParam), Input::InputState::Pressed);
        events.push(event);
        break;
    case WM_KEYUP:
        event = Event::KeyReleased;
        input.keyboard.SetKeyState(ConvertVirtualKey(wParam), Input::InputState::Released);
        events.push(event);
        break;
    case WM_MOUSEMOVE:
        event = Event::MouseMoved;
        input.mouse.SetCursorPosition(Math::Point<int>(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
        events.push(event);
        break;
    case WM_MOVE:
        event = Event::WindowMoved;
        x = GET_X_LPARAM(lParam);
        y = GET_Y_LPARAM(lParam);
        events.push(event);
        break;
    case WM_SIZE:
        event = Event::WindowResized;
        width = GET_X_LPARAM(lParam);
        height = GET_Y_LPARAM(lParam);
        events.push(event);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

LRESULT Jade::System::Win32Window::WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // Retieve a pointer to the window.
    Win32Window* window = reinterpret_cast<Win32Window*>(GetProp(hWnd, TEXT("WINDOW")));

    // Pointer will be null until window is "fully constructed."
    if (!window)
        return DefWindowProc(hWnd, msg, wParam, lParam);
   
    // Once the pointer exists we can call our own event handler for the object.
    return window->WindowEventHandler(msg, wParam, lParam);
}
