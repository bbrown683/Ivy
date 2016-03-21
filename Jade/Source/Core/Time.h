#pragma once

namespace Jade
{
	namespace Core
	{
		class Time
		{
		private:

			float deltaTime;
			float elapsedTime;

		public:

			// Returns the time between frame refreshes.
			float GetDeltaTime() const
			{
				return deltaTime;
			}

			// Do not set this value as it is done manually...
			void SetDeltaTime(float value)
			{
				deltaTime = value;
			}

			// Returns the elapsed time of the program.
			float GetElaspedTime() const
			{
				return elapsedTime;
			}

			// Do not set this value as it is done manually...
			void SetElapsedTime(float value)
			{
				elapsedTime = value;
			}
		};
	}
}