#include "ESP.h"
#include "../Utils/CInitialization.h"
#include "../../Menu/src/Menu.h"
#include "../../Menu/ImGui/imgui_internal.h"

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )

GL::Font font;

ImVec4 enemyBox = ImColor(255, 0, 0, 1); //Default: Red
ImVec4 enemyBoxVisible = ImColor(0, 255, 0, 1);
ImVec4 teamBox = ImColor(0, 0, 255, 1);
ImVec4 text = ImColor(125, 125, 200, 1);
ImVec4 snapline = ImColor(0, 0, 0, 1);
ImVec4 healthBarBackground = ImColor(255, 0, 0, 1);
ImVec4 healthBar = ImColor(0, 255, 0, 1);

void CESP::Run()
{
	if (vars::m_bESP)
	{
		float viewport[4];
		glGetFloatv(GL_VIEWPORT, viewport);

		GL::SetupOrtho();

		for (int i = 0; i < GData::p_num; i++) //Loop through entity list
		{
			CPlayer* currPlayer = *(CPlayer**)(*(uintptr_t*)(GData::module_start + offsets::ent_list) + i * 0x4);
			if (g_Utils.IsValid(currPlayer) && g_Utils.IsTeamGameMode() && currPlayer->m_iTeamNum != GData::p_local->m_iTeamNum || g_Utils.IsValid(currPlayer) && !g_Utils.IsTeamGameMode()) //Check if entity is not on our team and is valid. Gosh what a long line of code
			{

				Vector3 headPos = currPlayer->m_vecHeadPos;
				Vector3 feetPos = currPlayer->m_vecPos;

				headPos.z += 0.8f; //Makes boxes a little higher

				if (currPlayer->bCrouching) //Boxes show actual headheight better
				{
					headPos.z -= 0.5625; //When someone crouches, their head height decreases by 1.125 so I just divided by 2
				}

				Vector3 headScreenPos, feetScreenPos;
				if (g_Utils.World2Screen(headPos, headScreenPos) && g_Utils.World2Screen(feetPos, feetScreenPos))
				{
					float height = feetScreenPos.y - headScreenPos.y; //Get entity height
					float width = height / 2.0f; //Get entity width

					Vector2 tl; //Top left of box
					tl.x = headScreenPos.x - width / 2.0f;
					tl.y = headScreenPos.y;
					Vector2 br; //Bottom right of box
					br.x = headScreenPos.x + width / 2.0f;
					br.y = headScreenPos.y + height;

					GL::DrawOutline(tl.x, tl.y, br.x, br.y, 2.0f, enemyBox);

					//Name
					if (vars::m_bName)
					{
						std::string name = currPlayer->m_sName;
						int tWidth = name.length() * 9;
						float dif = width - tWidth;

						font.Print(tl.x + dif / 2, tl.y - 16 / 2, text, "%s", currPlayer->m_sName);
					}

					//Healthbar
					if (vars::m_bHealthBar)
					{
						//Constrains the healthbar to not go past a certain position while scaling
						float x = width / 8.0f;
						if (x < 3.5)
						{
							x = 3.5;
						}

						//Background(Red part)
						Vector2 healthB;
						healthB.x = br.x + x;
						healthB.y = br.y;
						Vector2 healthT;
						healthT.x = br.x + x;
						healthT.y = tl.y;

						GL::DrawLine(healthB.x, healthB.y, healthT.x, healthT.y, 5, healthBarBackground);

						//Actual health(Green part)
						float healthBarHeight = healthT.y - healthB.y;
						float health = currPlayer->m_iHealth * healthBarHeight / 100;
						Vector2 healthA;
						healthA.y = healthB.y + health;

						GL::DrawLine(healthB.x, healthB.y, healthT.x, healthA.y, 5, healthBar);
					}
				}
			}

			//TeamEsp(Same thing as regular esp)
			if (vars::m_bTeam && g_Utils.IsTeamGameMode())
			{
				if (g_Utils.IsValid(currPlayer) && currPlayer->m_iTeamNum == GData::p_local->m_iTeamNum)
				{
					Vector3 headPos = currPlayer->m_vecHeadPos;
					Vector3 feetPos = currPlayer->m_vecPos;

					headPos.z += 0.8f;

					Vector3 headScreenPos, feetScreenPos;
					if (g_Utils.World2Screen(headPos, headScreenPos) && g_Utils.World2Screen(feetPos, feetScreenPos))
					{
						float height = feetScreenPos.y - headScreenPos.y;
						float width = height / 2.0f;

						Vector2 tl;
						tl.x = headScreenPos.x - width / 2.0f;
						tl.y = headScreenPos.y;
						Vector2 br;
						br.x = headScreenPos.x + width / 2.0f;
						br.y = headScreenPos.y + height;

						GL::DrawOutline(tl.x, tl.y, br.x, br.y, 2.0f, teamBox);

						//Name
						if (vars::m_bName)
						{
							std::string name = currPlayer->m_sName;
							int tWidth = name.length() * 9;
							float dif = width - tWidth;

							font.Print(tl.x + dif / 2, tl.y - 16 / 2, text, "%s", currPlayer->m_sName);
						}

						if (vars::m_bHealthBar)
						{
							//Constrains the healthbar to not go past a certain position while scaling
							float x = width / 8.0f;
							if (x < 3.5)
							{
								x = 3.5;
							}

							//Background(Red part)
							Vector2 healthB;
							healthB.x = br.x + x;
							healthB.y = br.y;
							Vector2 healthT;
							healthT.x = br.x + x;
							healthT.y = tl.y;

							GL::DrawLine(healthB.x, healthB.y, healthT.x, healthT.y, 5, healthBarBackground);

							//Actual health(Green part)
							float healthBarHeight = healthT.y - healthB.y;
							float health = currPlayer->m_iHealth * healthBarHeight / 100;
							Vector2 healthA;
							healthA.y = healthB.y + health;

							GL::DrawLine(healthB.x, healthB.y, healthT.x, healthA.y, 5, healthBar);
						}
					}
				}
			}
		}

		GL::RestoreGL();
	}
}

CESP g_Esp;