#pragma once
#include <GLFW/glfw3.h>
#include <core/ui/UIGroups.h>
#include <vector>
#include <memory>

namespace cme::ui {
	class Window;

	/// @brief Se encarga de controlar las centanas y la interfaz de usuario del motor
	class UIManager
	{
	private:
		std::vector<std::unique_ptr<Window>> _windows;
	public:
		UIManager();
		~UIManager();
		bool initCoreUI(GLFWwindow* window);

		void render() const;

		void bind() const;
		void unbind() const;
	private:
		bool initImgui(GLFWwindow* window);
		void renderMenuBar() const;

	public:
		template<typename T, typename... Args>
		T* addWindow(Args&&... args) {
			auto window = std::make_unique<T>(std::forward<Args>(args)...);
			T* ptr = window.get();

			constexpr cme::ui::windowGroupID id = static_cast<cme::ui::windowGroupID>(cme::ui::getWindowID<T>);
			_windows[id] = std::move(window);
			return ptr;
		}
	};
}

