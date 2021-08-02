#pragma once
#include <iostream>
#include <windows.h>
#include <thread>

#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#include <D3dx9tex.h>
#pragma comment(lib, "D3dx9")
#pragma comment(lib, "user32.lib")

#include "bytes/font.h"
#include "bytes/logo.hpp"

#include "encrypt/xor.h"
#include "btfile/bytetofile.hpp"


std::string imagePath = _xor_("C:\\Windows\\System32\\Speech\\a16fb36f0911f878998c136191af705e.png");

#define COLOUR(x) x/255 
#define CENTER(width) ((ImGui::GetWindowSize().x - width) * 0.5f)

bool loader_active = true;
HWND main_hwnd = nullptr;

LPDIRECT3DDEVICE9        g_pd3dDevice;
D3DPRESENT_PARAMETERS    g_d3dpp;
LPDIRECT3D9              g_pD3D;

bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
    PDIRECT3DTEXTURE9 texture;
    HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice, filename, &texture);
    if (hr != S_OK)
        return false;

    D3DSURFACE_DESC my_image_desc;
    texture->GetLevelDesc(0, &my_image_desc);
    *out_texture = texture;
    *out_width = (int)my_image_desc.Width;
    *out_height = (int)my_image_desc.Height;
    return true;
}

inline bool FileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void Theme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(COLOUR(22.0f), COLOUR(24.0f), COLOUR(29.0f), 1.f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(COLOUR(30.0f), COLOUR(31.0f), COLOUR(38.0f), 1.f);
    style.Colors[ImGuiCol_Border] = ImVec4(COLOUR(22.0f), COLOUR(24.0f), COLOUR(29.0f), 0.9f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(COLOUR(50.0f), COLOUR(50.0f), COLOUR(50.0f), 1.f);
    style.Colors[ImGuiCol_Button] = ImVec4(COLOUR(67.0f), COLOUR(38.0f), COLOUR(235.0f), 1.f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(COLOUR(5.0f), COLOUR(116.0f), COLOUR(203.0f), 1.f);
    style.Colors[ImGuiCol_Header] = ImVec4(COLOUR(5.0f), COLOUR(116.0f), COLOUR(203.0f), 1.f);
    style.WindowRounding = 0.0f;
    style.FrameRounding = 2.f;
}

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;
    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = NULL; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}