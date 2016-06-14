#pragma once

namespace Jade
{
    namespace System
    {
        enum class Event
        {
            None,
            KeyPressed,
            KeyReleased,
            MouseMoved,
            WindowClosed,
            WindowCreated,
            WindowMoved,
            WindowResized,
        };
    }
}