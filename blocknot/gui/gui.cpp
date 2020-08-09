#include <iostream>
#include "gui.h"
#include "../defines.h"
#include "../utils/utils.h"
#include <string>
#include "../ImGuiFileDialog/ImGuiFileDialog.h"
#include "../filesystem/filesystem.h"

cGui gui;

HWND hwndWindow;

struct fonts
{
	ImFont* title;
}font;

void cGui::ImGuiInit(HWND h, LPDIRECT3DDEVICE9 g_pd3dDevice)
{
	ImGui::CreateContext();

	auto io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 13.9f, NULL, io.Fonts->GetGlyphRangesCyrillic());

	font.title = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 26);

	ImGui_ImplWin32_Init(h);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	auto& style = ImGui::GetStyle();
	style.FramePadding = ImVec2(5, 3);
	style.ItemSpacing = ImVec2(6, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 0.0f;
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameRounding = 0.0f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 9.0f;
	style.ScrollbarRounding = 0.0f;
	style.WindowPadding = ImVec2(0, 16);
	colorAccent[0] = 1.f, colorAccent[1] = 0.f, colorAccent[2] = 0.f;
	hwndWindow = h;
}

void cGui::DestroyImgui()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void cGui::Reset(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

void cGui::Render(LPDIRECT3DDEVICE9 g_pd3dDevice, D3DPRESENT_PARAMETERS g_d3dpp)
{
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);

	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (g_pd3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		g_pd3dDevice->EndScene();
	}

	HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		Reset(g_pd3dDevice, g_d3dpp);
	}
}

SIZE GetWindowSize(HWND hwnd) 
{
	RECT Rect; SIZE sz;
	GetWindowRect(hwnd, &Rect);
	sz.cx = (Rect.right - Rect.left);
	sz.cy = (Rect.bottom - Rect.top);
	return sz;
}

void setColorTheme(int theme)
{
	auto& style = ImGui::GetStyle();
	if (theme == 0)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.81f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.70f, 0.70f, 0.70f, 0.65f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.55f, 0.55f, 0.55f, 0.30f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.55f, 0.55f, 0.55f, 0.40f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.55f, 0.55f, 0.55f, 0.45f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.41f, 0.41f, 0.41f, 0.83f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.40f, 0.40f, 0.40f, 0.20f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.57f, 0.57f, 0.57f, 0.87f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.00f, 0.00f, 0.30f);
		style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.00f, 0.00f, 0.60f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.45f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(1.00f, 0.00f, 0.00f, 0.80f); //eto
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f); //eto
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	}	
	else
	{
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(58 / 255.f, 62 / 255.f, 71 / 255.f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(20 / 255.f, 20 / 255.f, 31 / 255.f, 1.0f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(28 / 255.f, 30 / 255.f, 42 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(33 / 255.f, 35 / 255.f, 47 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(35 / 255.f, 35 / 255.f, 35 / 255.f, 1.0f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.f, 0.40f, 1.f, 1.f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.f, 0.50f, 1.f, 1.f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.f, 0.30f, 1.f, 1.f);
		style.Colors[ImGuiCol_Header] = ImVec4(74 / 255.f, 87 / 255.f, 109 / 255.f, 1.0f); //multicombo, combo selected item color.
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.f, 0.40f, 1.f, 0.5f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(74 / 255.f, 87 / 255.f, 109 / 255.f, 1.0f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	}	
}

static bool credits_open = false;
static int theme = 0;
static std::string szPath;

#define SetPosElementX(s) ImGui::SetCursorPosX(ImGui::GetCursorPosX() s);
#define SetPosElementY(s) ImGui::SetCursorPosY(ImGui::GetCursorPosY() s);

void cGui::GuiLoop()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	setColorTheme(theme);

	SIZE wndSz = GetWindowSize(hwndWindow);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 7));
	ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImU32(ImColor(colorAccent[0] , colorAccent[1], colorAccent[2], 0.35f)));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImU32(ImColor(colorAccent[0], colorAccent[1] , colorAccent[2], 0.80f)));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImU32(ImColor(colorAccent[0], colorAccent[1], colorAccent[2], 1.f)));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImU32(ImColor(colorAccent[0], colorAccent[1], colorAccent[2], 1.f)));
	ImGui::PushStyleColor(ImGuiCol_Button, ImU32(ImColor(colorAccent[0], colorAccent[1], colorAccent[2], 1.f)));

	static char buff[9999999] = { 0 };

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(u8"Файл"))
		{
			if (ImGui::MenuItem(u8"Открыть")) { igfd::ImGuiFileDialog::Instance()->OpenDialog("open", u8"Открыть", ".txt", "."); }
			if (ImGui::MenuItem(u8"Сохранить")) { if (!szPath.empty()) filesystem::write_to_file(szPath.c_str(), buff); }
			if (ImGui::MenuItem(u8"Сохранить как")) { igfd::ImGuiFileDialog::Instance()->OpenDialog("save_as", u8"Сохранить как", ".txt", "."); }
			if (ImGui::MenuItem(u8"Выход", u8"Alt+F4")) { ExitProcess(0); }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"Цвета"))
		{
			ImGui::ColorEdit4(u8"Цветовой акцент", colorAccent, ImGuiColorEditFlags_NoAlpha);
			const char* szThemeType[] = { u8"Светлая", u8"Темная" };
			ImGui::Combo(u8"Тема", &theme, szThemeType, IM_ARRAYSIZE(szThemeType));
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(u8"Справка"))
		{
			if (ImGui::MenuItem(u8"О программе")) { credits_open = true; }	
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::PopStyleVar();

	ImGui::SetNextWindowPos(ImVec2(0.f, 20.f), ImGuiCond_Always, ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(wndSz.cx - 16, wndSz.cy - 55));

	ImGuiWindowFlags WndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove 
		| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

	ImGui::Begin(WindowName, nullptr, WndFlags);
	{
		SetPosElementY(-15)

		ImGui::InputTextMultiline("##input", buff, 9999999, ImVec2(wndSz.cx - 16, wndSz.cy - 81));

		word_and_latters result = utils::calc_word_and_latters(std::string(buff));
		SetPosElementX(+5)
		ImGui::Text(u8"Слов: %d, Букв: %d", result.word, result.latters);

		ImGui::SameLine();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(7, 7));
			
		if (igfd::ImGuiFileDialog::Instance()->FileDialog("open"))
		{
			if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
			{
				std::string szFilePath = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
				szPath = szFilePath;
				filesystem::read_in_file(szFilePath.c_str(), buff);
			}
			igfd::ImGuiFileDialog::Instance()->CloseDialog("open");
		}

		if (igfd::ImGuiFileDialog::Instance()->FileDialog("save_as"))
		{
			if (igfd::ImGuiFileDialog::Instance()->IsOk == true)
			{
				std::string szFilePathAndName = igfd::ImGuiFileDialog::Instance()->GetFilePathName();
				szPath = szFilePathAndName;
				filesystem::write_to_file(szFilePathAndName.c_str(), buff);
			}
			igfd::ImGuiFileDialog::Instance()->CloseDialog("save_as");
		}

		ImGui::PopStyleVar();
	}
	ImGui::End();

	if (credits_open)
	{
		ImGuiWindowFlags TwoWndFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		ImGui::SetNextWindowPos(ImVec2((wndSz.cx - 16) / 2.f - 80, (wndSz.cy - 55) / 2.f - 50), ImGuiCond_Always, ImVec2(0.f, 0.f));
		ImGui::Begin(u8"О программе", &credits_open, ImVec2(180, 150), 1.0f, TwoWndFlags);

		SetPosElementY(+25)
		SetPosElementX(+50)
		ImGui::Text(u8"Блокнот, 2D20");
		SetPosElementX(+50)
		ImGui::Text(u8"Люблю Леру!!!");
		credits_open = ImGui::IsAnyWindowHovered();

		ImGui::End();
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::EndFrame();
}