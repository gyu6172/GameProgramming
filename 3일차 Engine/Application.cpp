#include "stdafx.h"
#include "Application.h"

LPDIRECT3D9 pd3d;
D3DPRESENT_PARAMETERS d3dpp;
LPDIRECT3DDEVICE9 pd3dDevice;
HWND hWnd;
LPD3DXSPRITE pd3dSprite;
SceneManager* sceneManager;
TextureManager* textureManager;
inputManager* inputmanager;


Application::Application() {
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&Frequency);
}

Application::~Application() {
	
}

void Application::InitD3D(HWND hWnd) {
	pd3d = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pd3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		& pd3dDevice);

		//���� �� ����
	D3DXCreateSprite(pd3dDevice, &pd3dSprite);
}

void Application::InitWindow(HINSTANCE hInstance) {
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH
		);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = PROGRAM_NAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);
}

void Application::InitManager() {
	sceneManager = new SceneManager();
	textureManager = new TextureManager();
	inputmanager = new inputManager();
}

void Application::InitDeltaTime() {
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceFrequency(&Frequency);
}

LRESULT CALLBACK Application::WndProc(HWND hWnd,
	UINT iMessage, WPARAM wParam, LPARAM lparam) {
	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam
		, lparam);
}

HWND Application::FloatWindow(HINSTANCE hInstance,
	int cmdShow) {
	hWnd = CreateWindow(PROGRAM_NAME, PROGRAM_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, cmdShow);
	return hWnd;
}

int Application::DoMainLoop(Scene* firstScene) {
	InitDeltaTime();
	InitManager();

	sceneManager->ChangeScene(firstScene);

	MSG Message = { 0, };

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,BG_COLOR, 1.0f, 0);
		pd3dDevice->BeginScene();

		pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
		sceneManager->Render();
		pd3dSprite->End();

		pd3dDevice->EndScene();
		pd3dDevice->Present(0, 0, 0, 0);

		inputmanager->UpdateKeyState();
		sceneManager->Update(getDeltaTime());
	}

	DeleteManager();
	ReleaseD3D();

	return (int)Message.wParam;
}

void Application::DeleteManager() {
	SAFE_DELETE(sceneManager);
	SAFE_DELETE(textureManager);
	SAFE_DELETE(inputmanager);
}

void Application::ReleaseD3D() {
	SAFE_RELEASE(pd3dSprite);
	SAFE_RELEASE(pd3dDevice);
	SAFE_RELEASE(pd3d);
}

float Application::getDeltaTime() {
	QueryPerformanceFrequency(&currentInterval);
	LONGLONG interval = (currentInterval.QuadPart
		- beforeInterval.QuadPart);
	float dTime = (float)interval / (float)Frequency.QuadPart;
	beforeInterval = currentInterval;
	return dTime;
}




