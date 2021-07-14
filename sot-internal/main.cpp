#pragma once
#include "main.h"

void Remove() {
	kiero::shutdown();
	logger.~Logger();
}

void UpdateRainbow() {
	rainbow += 0.0005f;
	if (rainbow > 1.f) rainbow = 0.f;
}

ImVec4 FromHSB(float hue, float saturation, float brightness) {
	float h = hue == 1.0f ? 0 : hue * 6.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1) {
		return ImVec4(brightness, t, p, 1.f);
	}
	else if (h < 2) {
		return ImVec4(q, brightness, p, 1.f);
	}
	else if (h < 3) {
		return ImVec4(p, brightness, t, 1.f);
	}
	else if (h < 4) {
		return ImVec4(p, q, brightness, 1.f);
	}
	else if (h < 5) {
		return ImVec4(t, p, brightness, 1.f);
	}
	else {
		return ImVec4(brightness, p, q, 1.f);
	}
}

ImVec4 GetRainbowColor() {
	return FromHSB(rainbow, 1.f, 1.f);
}

void Text(const char* text, const FVector2D& pos, const ImVec4& color, const bool outlined, const bool centered) {
	if (!text) return;

	auto ImScreen = *reinterpret_cast<const ImVec2*>(&pos);

	if (centered) {
		auto size = ImGui::CalcTextSize(text);
		ImScreen.x -= size.x * 0.5f;
		ImScreen.y -= size.y;
	}
	auto window = ImGui::GetCurrentWindow();

	if (outlined) {
		window->DrawList->AddText(nullptr, 0.f, ImVec2(ImScreen.x - 1.f, ImScreen.y + 1.f), ImGui::GetColorU32(IM_COL32_BLACK), text);
	}

	window->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text);
}

void Draw() {
	std::string text("SoT internal 1.0.0 - Coded by Purps");
	auto textSize = ImGui::CalcTextSize(text.c_str());
	Text(text.c_str(), FVector2D(0.f, ImGui::GetCurrentWindow()->Size[1] - textSize[1] - 1.f), GetRainbowColor(), true, false);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

inline HRESULT WINAPI PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
	if (!device) {
		ID3D11Texture2D* surface = nullptr;

		if (SUCCEEDED(swapChain->GetBuffer(0, __uuidof(surface), reinterpret_cast<PVOID*>(&surface))) &&
			SUCCEEDED(swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device))) &&
			SUCCEEDED(device->CreateRenderTargetView(surface, nullptr, &renderTargetView))) {
			surface->Release();
			surface = nullptr;

			device->GetImmediateContext(&context);

			ImGui::CreateContext();

			{
				ImGuiIO& io = ImGui::GetIO();
				ImFontConfig config;
				config.GlyphRanges = io.Fonts->GetGlyphRangesCyrillic();
				config.RasterizerMultiply = 1.125f;
				io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f, &config);
				io.IniFilename = nullptr;
			}

			DXGI_SWAP_CHAIN_DESC desc;
			swapChain->GetDesc(&desc);
			auto& window = desc.OutputWindow;
			gameWindow = window;

			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(device, context);
			ImGui_ImplDX11_CreateDeviceObjects();
		}
		else {
			Remove();
			if (surface) surface->Release();
			return oPresent(swapChain, syncInterval, flags);
		}
	}

	UpdateRainbow();
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	ImGui::Begin("#1", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
	auto& io = ImGui::GetIO();
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

	UpdateRainbow();
	Draw();

	ImGui::End();
	ImGui::Render();

	context->OMSetRenderTargets(1, &renderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(swapChain, syncInterval, flags);
}

inline HRESULT WINAPI ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	if (renderTargetView) {
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();
		renderTargetView->Release();
		renderTargetView = nullptr;
	}

	if (context) {
		context->Release();
		context = nullptr;
	}

	if (device) {
		device->Release();
		device = nullptr;
	}

	return oResize(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}

void Initialize() {
	auto gNamesBaseAddress = memory.FindPattern("48 8B 1D ? ? ? ? 48 85 DB 75 ? B9 08 04 00 00");
	auto gNamesOffset = *reinterpret_cast<uint32_t*>(gNamesBaseAddress + 3);
	auto gNamesAddress = reinterpret_cast<uint64_t*>(gNamesBaseAddress + gNamesOffset + 7);
	FName::GNames = reinterpret_cast<decltype(FName::GNames)>(*gNamesAddress);

	auto gObjectsBaseAddress = memory.FindPattern("89 0D ? ? ? ? 48 8B DF 48 89 5C 24");
	auto gObjectsOffset = *reinterpret_cast<uint32_t*>(gObjectsBaseAddress + 2);
	UObject::GObjects = reinterpret_cast<decltype(UObject::GObjects)>(gObjectsBaseAddress + gObjectsOffset + 6);

	logger.Log("GNames: %p\n", FName::GNames);
	logger.Log("GObjects: %p\n", UObject::GObjects);

	//for (int i = 0; i < FName::GetGlobalNames().Num(); i++) {
	//	auto name = FName::GetGlobalNames()[i];
	//	if (name) {
	//		logger.Log("%s\n", name->GetAnsiName());
	//	}
	//}

	//for (int i = 0; i < UObject::GetGlobalObjects().Num(); i++) {
	//	auto object = UObject::GetGlobalObjects().GetByIndex(i);
	//	if (object) {
	//		logger.Log("%s\n", object->GetFullName());
	//	}
	//}
	//
	//AthenaGameViewportClient = UObject::FindObject<UAthenaGameViewportClient>("AthenaGameViewportClient Transient.AthenaGameEngine_1.AthenaGameViewportClient_1");
	//logger.Log("%p\n", AthenaGameViewportClient);
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
	bool init_hook = false;

	Initialize();

	do {
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success) {
			// Table with method indices: https://github.com/Rebzzel/kiero/blob/master/METHODSTABLE.txt
			if (kiero::bind(8, (void**)&oPresent, PresentHook) != kiero::Status::Success) {
				return FALSE;
			}

			if (kiero::bind(13, (void**)&oResize, ResizeHook) != kiero::Status::Success) {
				return FALSE;
			}

			init_hook = TRUE;
		}
	} while (!init_hook);

	return TRUE;
}

bool ClearingThread() {
	while (true) {
		if (GetAsyncKeyState(VK_END) & 1) {
			Remove();
		}

		Sleep(20);
	}

	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved) {
	switch (dwReason) {
	case DLL_PROCESS_ATTACH: {
		DisableThreadLibraryCalls(hinstDLL);

		if (!K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &gBaseMod, sizeof(MODULEINFO))) {
			return FALSE;
		}

		HANDLE thread1 = CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
		HANDLE thread2 = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ClearingThread), nullptr, 0, nullptr);

		break;
	}
	case DLL_PROCESS_DETACH: {
		break;
	}
	}

	return TRUE;
}