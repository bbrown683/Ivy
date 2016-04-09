#pragma once

namespace Jade
{
	namespace Core
	{
		//! All content will inherit the load method which allows us 
		//! to load the content through a multiethreaded pipeline.
		//! In doing so, we do not hinder the main process by loading
		//! the content.
		struct IAsset
		{
			virtual void Load() = 0;
		};
	}
}