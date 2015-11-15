#pragma once

namespace Jade
{
	namespace Graphics
	{
		class Event
		{
		public:

			enum class EventType : int
			{
				Unknown,
				Close,
				Resize,
				KeyPressed,
				KeyReleased,
			};

			EventType GetEventType();

			void SetEventType(EventType value);

		private:

			EventType type;
		};
	}
}
