#pragma once

namespace Core
{
	class Time
	{
	private:

		long deltaTime;

	public:

		long GetDeltaTime() const
		{
			return deltaTime;
		}

		void SetDeltaTime(long value)
		{
			deltaTime = value;
		}
	};
}