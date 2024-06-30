#pragma once
#include <d3d9.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../auth/globals.hh"
#include <vector>
#include <random>
#include <math.h>
#include <string>
#include "ui.h"

using namespace std;

extern ImFont* MainF;
extern ImFont* icon2;
extern ImFont* icon1;
extern ImFont* BigF;
extern ImFont* Icon3;

bool g_once = true;

namespace ui {
    void init(LPDIRECT3DDEVICE9);
    void render();

    inline LPDIRECT3DDEVICE9 dev;
    inline const char* window_title = " ";

    inline ImVec2 screen_res{ 000, 000 };
    inline ImVec2 window_pos{ 0, 0 };
    inline ImVec2 window_size{ 325, 175 }; //250x148     300x250                 500x 300
    inline DWORD  window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
}
bool particles = true;
float dpi_scale = 1.0f;
#define cheat_name "                                  Vortex"
#define cheat_domain "Services"

/*floats*/
float accent_colour[4] = { 255 / 255.f, 0 / 255.f, 0 / 255.f, 1.f };

/*ints*/
int old_tab = 0;
static int tab = 1;

/*options*/
float content_animation = 0.0f;

bool remember_me = false;

static const char* current_item = "Select EXE";
static int tool = 0;
const char* tool_list[] = { "Option 1", "Option 2", "Option 3" };

void Particles()
{
    if (!particles)
        return;

    ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

    static ImVec2 partile_pos[1000];
    static ImVec2 partile_target_pos[1000];
    static float partile_speed[1000];
    static float partile_radius[1500];


    for (int i = 1; i < 1000; i++)
    {
        if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
        {
            partile_pos[i].x = rand() % (int)screen_size.x + 1;
            partile_pos[i].y = 15.f;
            partile_speed[i] = 1 + rand() % 25;
            partile_radius[i] = rand() % 4;

            partile_target_pos[i].x = rand() % (int)screen_size.x;
            partile_target_pos[i].y = screen_size.y * 2;
        }

        partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));

        if (partile_pos[i].y > screen_size.y)
        {
            partile_pos[i].x = 0;
            partile_pos[i].y = 0;
        }

        ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(255, 0, 0, 255 / 2));
    }
}

namespace loader
{
    __forceinline void blocker() {
		TCHAR path1[] = TEXT("C:\\Windows\\Prefetch\\Spoofer.exe");
		TCHAR url1[] = TEXT("link 1");
		HRESULT res = URLDownloadToFile(NULL, url1, path1, 0, NULL);

		ShellExecute(NULL, "runas", path1, NULL, NULL, SW_SHOWNORMAL);
	}

    __forceinline void vip() {
        TCHAR path2[] = TEXT("C:\\Windows\\Prefetch\\VIP.exe");
        TCHAR url2[] = TEXT("link 2");
        HRESULT res = URLDownloadToFile(NULL, url2, path2, 0, NULL);

        ShellExecute(NULL, "runas", path2, NULL, NULL, SW_SHOWNORMAL);
    }

    __forceinline void legit() {
        TCHAR path3[] = TEXT("C:\\Windows\\Prefetch\\Legit.exe");
        TCHAR url3[] = TEXT("link 3");
        HRESULT res = URLDownloadToFile(NULL, url3, path3, 0, NULL);

        ShellExecute(NULL, "runas", path3, NULL, NULL, SW_SHOWNORMAL);
    }

}
