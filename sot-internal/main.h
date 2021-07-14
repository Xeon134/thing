#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <cstdint>

#include <d3d11.h>
#include <dxgi.h>

#include "kiero.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "logger.h"
#include "memory.h"
#include "SDK.h"

using namespace CG;

typedef HRESULT(WINAPI* Present) (IDXGISwapChain*, UINT, UINT);
typedef HRESULT(WINAPI* Resize) (IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

ID3D11Device* device;
ID3D11DeviceContext* context;
ID3D11RenderTargetView* renderTargetView;

HWND gameWindow;
WNDPROC oWndProc;

Present oPresent;
Resize oResize;

MODULEINFO gBaseMod;
HINSTANCE hinstDLL;

Logger logger("log.txt");
Memory memory(&gBaseMod);

UAthenaGameViewportClient* AthenaGameViewportClient = nullptr;

float rainbow;