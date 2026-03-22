#pragma once
#include <core/ui/Window.h>

namespace capiEngine::ui {
	class ConsoleWindow : public Window
	{
	public:
		WINDOW_ID(capiEngine::ui::windowGroupID::CONSOLE)
		ConsoleWindow(const char* name, ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse) :
			Window(name, flags) { }

	protected:
		virtual void renderWindowContent() const override;
	};
}

