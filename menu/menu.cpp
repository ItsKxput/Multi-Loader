#include "menu.h"
#include "../auth/globals.hh"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#pragma comment(lib, "urlmon.lib")

//#pragma warning(disable : 4996)

void ui::render() {
    //if (!globals.active) return;

    static float rainbow;
    rainbow += 0.0050f;
    if (rainbow > 1.f)
        rainbow = 0.f;

    auto rgb = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
    auto rgb_a = ImColor::HSV(rainbow, 1.f, 1.f, 0.9f);
    auto rgb_b = ImColor::HSV(rainbow, 1.f, 1.f, 0.7f);

    //ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
    ImGuiStyle* Style = &ImGui::GetStyle();
    ImGuiIO& io = ImGui::GetIO();
    Style->WindowBorderSize = 3;
    Style->FrameBorderSize = 0;
    Style->WindowRounding = 1;
    Style->FrameRounding = 1;
    Style->ScrollbarSize = 0;
    Style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    Style->Colors[ImGuiCol_FrameBg] = ImColor(26, 26, 26);
    Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_Button] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_ButtonHovered] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_ButtonActive] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_TitleBgActive] = ImColor(40, 40, 40, 255);
    //Style->Colors[ImGuiCol_TitleBg] = rgb; //ImVec4(1.000f, 0.000f, 0.935f, 1.000f);
    //Style->Colors[ImGuiCol_Text] = rgb; //ImVec4(1.000f, 0.000f, 0.935f, 1.000f);
    Style->Colors[ImGuiCol_Text] = ImColor(200, 200, 200);
    Style->Colors[ImGuiCol_HeaderHovered] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_Header] = ImColor(40, 40, 40, 255);
    Style->Colors[ImGuiCol_HeaderActive] = ImColor(40, 40, 40);
    Style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
    Style->ButtonTextAlign = ImVec2(0.5f, 0.5f);
    Style->ScrollbarSize = 10;
    Style->GrabRounding = 5.000f;
    Style->ChildRounding = 8.000f;


    Style->FrameRounding = 1.0f;
    Style->FrameBorderSize = 1.0f;
    Style->Colors[ImGuiCol_Border] = ImColor(255, 0, 0, 255);
    Style->Colors[ImGuiCol_Button] = ImColor(26, 26, 26);

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);
    //window_size{ 330, 298 };
    ImGui::Begin(window_title, &globals.active, window_flags);
    {
        Particles();

        auto draw = ImGui::GetWindowDrawList();
        ImVec2 pos = ImGui::GetWindowPos();
        ImVec2 size = ImGui::GetWindowSize();
        ImVec2 cheat_name_size = ImGui::CalcTextSize(cheat_name);

        draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + 23), ImColor(0.06f, 0.06f, 0.06f, 0.94f), 8.0f, ImDrawFlags_RoundCornersTopLeft | ImDrawFlags_RoundCornersTopRight);

        draw->AddText(ImVec2(pos.x + 6, pos.y + 4), ImColor(200, 200, 200), cheat_name);
        draw->AddText(ImVec2(pos.x + 6 + cheat_name_size.x, pos.y + 4), ImColor(255, 0, 0), cheat_domain);

        draw->AddLine(ImVec2(pos.x, pos.y + 23), ImVec2(pos.x + size.x, pos.y + 23), ImColor(40, 40, 40)); // upper line
        draw->AddRectFilledMultiColor(ImVec2(pos.x, pos.y + 24), ImVec2(pos.x + size.x, pos.y + 34), ImColor(16, 15, 19), ImColor(16, 15, 19), ImColor(16, 15, 19, 0), ImColor(16, 15, 19, 0)); // upper 'glow'

        ImGui::SetCursorPos(ImVec2(size.x - 15, 3));
        if (custom::selected("x"))
        {
            exit(0);
        }

        ImGui::SetCursorPos(ImVec2(size.x - 34, 3));
        if (custom::selected("-"))
        {
            ShowWindow(FindWindow(NULL, " "), SW_MINIMIZE);
        }

        content_animation = ImLerp(content_animation, content_animation < 1.0f ? 1.0f : 0.0f, 0.03f * (0.04f - ImGui::GetIO().DeltaTime));

        if (tab == 1)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, content_animation);
            ImGui::PushItemWidth(200);
            ImGui::SetCursorPos(ImVec2(60, 75));
            if (ImGui::BeginCombo("##combo", current_item))
            {
                for (int n = 0; n < IM_ARRAYSIZE(tool_list); n++)
                {
                    bool is_selected = (current_item == tool_list[n]);
                    if (ImGui::Selectable(tool_list[n], is_selected))
                        current_item = tool_list[n];
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            ImGui::PopItemWidth();
            // "MW19 Unlock All", "MW19 AIO", "HWID Blocker", "Boost Tool", "MW2 Chair + Blocker", "mw2 Unlock All + Blocker"
            ImGui::SetCursorPos(ImVec2(120, 105));
            if (ImGui::Button("Launch", ImVec2(85, 25)))
            {
                if (current_item == "Blocker")
                {
                    loader::blocker();
                }

                if (current_item == "Unlock All")
                {
                    loader::ua();
                }

                if (current_item == "AIO + Blocker")
                {
                    loader::aio();
                }

                if (current_item == "Vortex V2 Chair")
                {
                    loader::v2();
                }

                if (current_item == "Legit Chair")
                {
                    loader::legit();
                }

                if (current_item == "VIP Chair")
                {
                    loader::vip();
                }

                if (current_item == "Pro Chair")
                {
                    loader::pro();
                }
            }
        }
        ImGui::PopStyleVar();
    }
    ImGui::End();
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;

    if (window_pos.x == 0) {
        RECT screen_rect{};
        GetWindowRect(GetDesktopWindow(), &screen_rect);
        screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
        window_pos = (screen_res - window_size) * 0.5f;
    }
}