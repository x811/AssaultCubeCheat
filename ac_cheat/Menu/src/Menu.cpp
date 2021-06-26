#include "Menu.h"

typedef int(__cdecl* tSDL_ShowCursor)(int);
tSDL_ShowCursor SDL_ShowCursor;

namespace vars
{
    bool m_bAimBot = false;
    float m_fFov = 1.f;
    bool m_bVisible = false;
    bool m_bTeamAim = false;

    bool m_bPseudoWalls = false;

    bool m_bOnlyHeadShot = false;
    bool m_bTeleKill = false;
    bool m_bNoRecoil = false;
    bool m_bTrigger = false;
}

void CMenu::Initialize()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    SDL_ShowCursor = (tSDL_ShowCursor)(GetProcAddress(GetModuleHandle("SDL.dll"), "SDL_ShowCursor"));
    HWND hwnd = FindWindow(NULL, "AssaultCube");
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplOpenGL2_Init();
}

void CMenu::Update()
{
    if (bOpen)
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        SDL_ShowCursor(1);
        ImGui::SetNextWindowSize(ImVec2(350, 200), 0);
		ImGui::Begin("the_x811r", &bOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

        {
            ImGui::BeginTabBar("Meme", 0);
            {
                if (ImGui::BeginTabItem("AimBot"))
                {
                    ImGui::Checkbox("Enable", &vars::m_bAimBot);
                    ImGui::Separator();
                    if (vars::m_bAimBot)
                    {
                        ImGui::SliderFloat("FOV", &vars::m_fFov, 1.f, 360.f);
                        ImGui::Checkbox("Visible", &vars::m_bVisible);
                        ImGui::Checkbox("Aim Teammates", &vars::m_bTeamAim);
                    }
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Visuals"))
                {
                    ImGui::Checkbox("Pseudo Walls", &vars::m_bPseudoWalls);
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Exploits"))
                {
                    ImGui::Checkbox("Only Headshot", &vars::m_bOnlyHeadShot);
                    ImGui::Checkbox("Tele Kill", &vars::m_bTeleKill);
                    ImGui::Checkbox("No Recoil/Spread", &vars::m_bNoRecoil);
                    ImGui::Checkbox("Trigger", &vars::m_bTrigger);
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }
    else
    {
        SDL_ShowCursor(0);
    }
}

void CMenu::ShutDown()
{
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    SDL_ShowCursor(0);
}

CMenu g_Menu;