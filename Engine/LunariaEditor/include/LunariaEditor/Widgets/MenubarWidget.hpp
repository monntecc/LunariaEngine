#pragma once

#include <LunariaEngine.hpp>

namespace Lunaria {

	class MenubarWidget 
	{
	public:
		MenubarWidget();

		void Draw();
	private:
		bool BeginMenubar(const ImRect& barRectangle);
		void EndMenubar();
	};

}