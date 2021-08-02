#pragma once
#include <iostream>
#include <windows.h>
#include <thread>
#include <random>
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_internal.h"

#define WINDOW_TITLE " "
#define WINDOW_WIDTH  750
#define WINDOW_HEIGHT 450
#define COLOUR(x) x/255

enum states {
	loading,
	menu
};

class Menu {
public:
	ImFont* smallFont;
	ImFont* mediumFont;
	void Main(bool loader_active, PDIRECT3DTEXTURE9 my_texture);
private:
	void MainMenu();
	void LoadingScene();
};

template< typename ... Args >
std::string stringer(Args const& ... args)
{
	std::ostringstream stream;
	using List = int[];
	(void)List {
		0, ((void)(stream << args), 0) ...
	};
	return stream.str();
}

extern std::unique_ptr<Menu> m_Menu;