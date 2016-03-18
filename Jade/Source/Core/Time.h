#pragma once

namespace Core
{
	class Time
	{
	private:

		float deltaTime;

	public:

		float GetDeltaTime() const
		{
			return deltaTime;
		}

		void SetDeltaTime(float value)
		{
			deltaTime = value;
		}
	};
}