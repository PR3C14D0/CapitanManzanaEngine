#pragma once
#include <core/ui/Window.h>

namespace capiEngine::ui {
	class SceneWindow : public Window
	{
	public:
		WINDOW_ID(capiEngine::ui::windowGroupID::SCENE)
			SceneWindow(const char* name, ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse) :
			Window(name, flags) {
		}

	protected:
		virtual void renderWindowContent() const override;
	};
}