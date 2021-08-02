#include "menus.h"
#include "encrypt/xor.h"
#include "hwid.h"
#include "spoof/spoof.h"
#include "spoof\caches.h"

DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;
int state = states::menu;
PDIRECT3DTEXTURE9 logo_texture;
#define CENTER(width) ((ImGui::GetWindowSize().x - width) * 0.5f)

extern "C" {
    #include "spoof/cleaner/clean.h"
}

namespace UserInfo {
    std::string productID = getProductId();
    std::string currentBuild = getCurrentBuild();
    std::string macAddr = getMAC();
    std::string volumeID = getVolumeId();
    std::string processorID = GetProcessorId();
    std::string baseboardID = GetBaseboard();
}

void Menu::Main(bool loader_active, PDIRECT3DTEXTURE9 my_texture) {
    logo_texture = my_texture;

    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto xx = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto yy = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

    ImGui::SetNextWindowPos(ImVec2(xx, yy), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2{ WINDOW_WIDTH, WINDOW_HEIGHT }, ImGuiCond_Once);

    ImGui::Begin(WINDOW_TITLE, &loader_active, window_flags);
    {
        if (state == states::menu) {
            MainMenu();
        }
        else if (state == states::loading) {
            LoadingScene();
        }
    }
    ImGui::End();
}

void Menu::MainMenu() {

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 p = ImGui::GetCursorScreenPos();

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
    ImGui::SetCursorPosX(CENTER(220));

    if (logo_texture != NULL) {
        ImGui::Image((void*)logo_texture, ImVec2(220, 80));
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 20));
    {
        draw_list->AddRectFilled(ImVec2(p.x + 30.f, p.y + 100.f), ImVec2(p.x + 300.f, p.y + 385.f), ImColor(ImVec4(COLOUR(27.0f), COLOUR(29.0f), COLOUR(36.0f), 1.f)), 5.0f);

        draw_list->AddRectFilled(ImVec2(p.x + 45.f, p.y + 155.f), ImVec2(p.x + 285.f, p.y + 195.f), ImColor(ImVec4(COLOUR(34.0f), COLOUR(36.0f), COLOUR(44.0f), 1.f)), 7.0f);
        draw_list->AddRectFilled(ImVec2(p.x + 45.f, p.y + 210.f), ImVec2(p.x + 285.f, p.y + 250.f), ImColor(ImVec4(COLOUR(34.0f), COLOUR(36.0f), COLOUR(44.0f), 1.f)), 7.0f);
        draw_list->AddRectFilled(ImVec2(p.x + 45.f, p.y + 265.f), ImVec2(p.x + 285.f, p.y + 305.f), ImColor(ImVec4(COLOUR(34.0f), COLOUR(36.0f), COLOUR(44.0f), 1.f)), 7.0f);
        draw_list->AddRectFilled(ImVec2(p.x + 45.f, p.y + 320.f), ImVec2(p.x + 285.f, p.y + 360.f), ImColor(ImVec4(COLOUR(34.0f), COLOUR(36.0f), COLOUR(44.0f), 1.f)), 7.0f);

        draw_list->AddRectFilled(ImVec2(p.x + 330.f, p.y + 100.f), ImVec2(p.x + 710.f, p.y + 185.f), ImColor(ImVec4(COLOUR(27.0f), COLOUR(29.0f), COLOUR(36.0f), 1.f)), 5.0f);

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 45);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Text(_xor_("System Information:").c_str());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 35);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 345);
        ImGui::Text(_xor_("What is HWID Spoofer?").c_str());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 345);
        ImGui::Text(_xor_("Basically, HWID Spoofer (as know as HWID Changer) is the tool").c_str());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 15);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 345);
        ImGui::Text(_xor_("that can change HWID on your PC.").c_str());

        static bool diskdrive = true;
        static bool ram = true;
        static bool bios = true;
        static bool mac = true;
        static bool cpu = true;
        static bool volume = true;
        static bool gpu = true;

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 330);
        ImGui::Text(_xor_("Select the tracks you want to spoof.").c_str());

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 330);

        ImGui::Checkbox(_xor_(" Diskdrive").c_str(), &diskdrive); ImGui::SameLine();
        ImGui::Checkbox(_xor_(" Ram").c_str(), &ram); ImGui::SameLine();
        ImGui::Checkbox(_xor_(" Bios").c_str(), &bios); ImGui::SameLine();
        ImGui::Checkbox(_xor_(" Mac").c_str(), &mac); ImGui::SameLine();
        ImGui::Checkbox(_xor_(" CPU").c_str(), &cpu);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 10);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 330);
        
        ImGui::Checkbox(_xor_(" Volume").c_str(), &volume); ImGui::SameLine();
        
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 8);
        ImGui::Checkbox(_xor_(" GPU").c_str(), &gpu);

        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 15);
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 330);
        if (ImGui::Button("Spoof", ImVec2(375, 40))) {
            state = states::loading;

            std::thread t1(VanguardDrivers);
            t1.detach();

            std::thread t2(ProcessKiller);
            t2.detach();

            std::thread t3(GayMacChanger);
            t3.detach();

            std::thread t4(DriverLoad);
            t4.detach();

            std::thread t5(CleanProcess);
            t5.detach();

            std::thread t6(CleanCaches);
            t6.detach();
        }

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 55);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 228);
        std::string macAddrText = stringer(_xor_("MacAddr: "), UserInfo::macAddr);
        ImGui::Text(macAddrText.c_str());

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 55);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 22);
        std::string volText = stringer(_xor_("Volume: "), UserInfo::volumeID);
        ImGui::Text(volText.c_str());

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 55);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 21);
        std::string cpuText = stringer(_xor_("CPU: "), UserInfo::processorID);
        ImGui::Text(cpuText.c_str());

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 55);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 21);
        std::string bboardText = stringer(_xor_("Baseboard: "), UserInfo::baseboardID);
        ImGui::Text(bboardText.c_str());
    }
    ImGui::PopStyleVar();
}

void Menu::LoadingScene() {
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
    ImGui::SetCursorPosX(CENTER(220));

    if (logo_texture != NULL) {
        ImGui::Image((void*)logo_texture, ImVec2(220, 80));
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 20));
    {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 325);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
        ImGui::Text(_xor_("Spoof starting...").c_str());
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 255);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
        ImGui::Text(_xor_("Do not close if you don't see MessageBox!").c_str());
    }
    ImGui::PopStyleVar();
}

std::unique_ptr<Menu> m_Menu;