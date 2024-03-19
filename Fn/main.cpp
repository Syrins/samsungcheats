#include "win_utils.h"
#include "d3d9_x.h"
#include "xor.hpp"
#include <dwmapi.h>
#include <vector>
#include "skStr.h"
#include <string>
#include <iostream>
#include "skStr.h"
#include <Windows.h>
#include <string>
#include <fstream>
#include "offsets.h"
#include <cstdint>
#include <filesystem>
#include <Mmsystem.h>
#include <mciapi.h>
#include <shobjidl_core.h>
#include <direct.h>
#include <urlmon.h>
#include <random>
#include <tlhelp32.h>
#include <winioctl.h>
#include <msxml.h>    
#include <atomic>
#include <mutex>
#include "FVector.h"
#include "driver.h"
#include "drawings.h"
#include "sdk.h"
#include <lmcons.h>
#include "features.h"
#include "overlay.h"
#include "x.hpp"
#include "auth.hpp"
#include "menuitems.h"
#include "lazyimp.hpp"
#define vk_9 0x39

bool ShowMenu = true;



D3DPRESENT_PARAMETERS d3dpp;
using namespace KeyAuth;

std::string name = "Samsung Main"; // application name. right above the blurred text aka the secret on the licenses tab among other tabs
std::string ownerid = "HAuG4eV3Vp"; // ownerid, found in account settings. click your profile picture on top right of dashboard and then account settings.
std::string secret = "f9c0f091e4dac6d51017816adcdbde041c1a0e11f121d9d59f7320a066aa0aeb"; // app secret, the blurred text on licenses tab and other tabs
std::string version = "1.1"; // leave alone unless you've changed version on website
std::string url = "https://keyauth.win/api/1.2/"; // change if you're self-hosting


api KeyAuthApp(name, ownerid, secret, version, url);

int CurrentActorId;



//static void xCreateWindow();
static void xInitD3d();
void actorloop();
static void xMainLoop();
static void xShutdown();
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);



IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;



std::uintptr_t process_find(const std::string& name)
{
	const auto snap = LI_FN(CreateToolhelp32Snapshot).safe()(TH32CS_SNAPPROCESS, 0);
	if (snap == INVALID_HANDLE_VALUE) {
		return 0;
	}

	PROCESSENTRY32 proc_entry{};
	proc_entry.dwSize = sizeof proc_entry;

	auto found_process = false;
	if (!!LI_FN(Process32First).safe()(snap, &proc_entry)) {
		do {
			if (name == proc_entry.szExeFile) {
				found_process = true;
				break;
			}
		} while (!!LI_FN(Process32Next).safe()(snap, &proc_entry));
	}

	LI_FN(CloseHandle).safe()(snap);
	return found_process
		? proc_entry.th32ProcessID
		: 0;
}


HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
int num = 5, num2 = 3;

const char* SetRed()
{
	SetConsoleTextAttribute(h, 9);
	return "";
}

const char* SetGreen()
{
	SetConsoleTextAttribute(h, 3);
	return "";
}

const char* SetGold()
{
	SetConsoleTextAttribute(h, 6);
	return "";
}

const char* SetWhite()
{
	SetConsoleTextAttribute(h, 7);
	return "";
}

void Log3(const char* text)
{
	SetWhite();
	std::cout << skCrypt("    [");
	SetRed();
	std::cout << skCrypt("/");
	SetWhite();
	std::cout << skCrypt("] : ");
	std::cout << text;
}

void SaveLicense(std::string key)
{
	std::ofstream outfile(skCrypt("C:\\Windows\\soarwazhere.soar"));
	outfile << key;
	outfile.close();
}


void LoadDriver()
{
	system("cls");
	std::cout << std::endl;
	Log3("Attempting To Load Driver.\n\n");

	BlockInput(true);
	system(skCrypt("curl https://cdn.discordapp.com/attachments/1137043459560194110/1138077636938170500/kdmapper.exe --output C:/Windows/System32/gainlol.exe >nul 2>&1"));
	system(skCrypt("curl https://cdn.discordapp.com/attachments/1133116250906710210/1133715947765645312/soar.rw.sys --output C:/Windows/Fonts/arial.sys >nul 2>&1"));
	system(skCrypt("C:/Windows/System32/gainlol.exe C:/Windows/Fonts/arial.sys"));
	DeleteFileA(skCrypt("C:/Windows/System32/gainlol.exe"));
	DeleteFileA(skCrypt("C:/Windows/Fonts/arial.sys"));
	BlockInput(false);
	std::cout << std::endl;
	Log3("Successfully Loaded.\n\n");
	Sleep(5000);
	return;
}

int main(int argc, const char* argv[])
{
	Log3("Connecting to auth servers...\n\n");
	Sleep(1400);
	KeyAuthApp.init();
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}
	system("cls");
	Log3("Success you are using the latest update of Samsung.\n\n");
	Sleep(2000);
		
	system("cls");
	std::string lols = __DATE__;
	std::string date = "Samsung Free | Build : " + lols;
	SetConsoleTitle(date.c_str());
	std::string lol2;


login:
	system("cls");
	//login
	std::cout << std::endl;
	Log3("Select an Listed Option.\n");
	Log3("1) Login\n");
	Log3("2) Register\n");
	Log3("3) Extend\n");

	std::cout << std::endl;
	Log3("Input -> ");
	int option;
	std::string username;
	std::string password;
	std::string key;

	std::cin >> option;
	switch (option)
	{
	case 1:
		system("color b");
		system("cls");
		Log3("Enter username: ");
		// std::cout << skCrypt("\n\n Enter username: "); // <- Old login
		std::cin >> username;
		// std::cout << skCrypt("\n Enter password: "); // <- Old login
		Log3("Enter password: ");
		std::cin >> password; 
		KeyAuthApp.login(username, password);
		break;
	case 2:
		system("color b");
		system("cls");
		Log3("Enter username: ");
		// std::cout << skCrypt("\n\n Enter username: "); // <- Old login
		std::cin >> username;
		// std::cout << skCrypt("\n Enter password: "); // <- Old login
		Log3("Enter password: ");
		std::cin >> password;
		//std::cout << skCrypt("\n Enter license: "); // <- Old login
		Log3("Enter license: ");
		std::cin >> key;

		KeyAuthApp.regstr(username, password, key);
		break;
	case 3:
		system("color b");
		system("cls");
		//std::cout << skCrypt("\n\n Enter username: "); // <- Old login
		Log3("Enter username: ");
		std::cin >> username;
		//std::cout << skCrypt("\n Enter license: "); // <- Old login
		Log3("Enter license: ");
		std::cin >> key;
		KeyAuthApp.upgrade(username, key);
		break;
	default:
		std::cout << skCrypt("\n\n Status: Failure: Invalid Selection");
		Sleep(3000);
		exit(0);
	}

	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}



	////check license
	//std::ifstream file("C:\\Windows\\soarwazhere.soar");
	//if (file.is_open())
	//{
	//	std::ifstream MyReadFile(skCrypt("C:\\Windows\\soarwazhere.soar"));
	//	std::string user;
	//	MyReadFile >> user;
	//	MyReadFile.close();
	//	if (user == "ilovesoar")
	//	{
	//		goto menu;
	//	}
	//	else
	//	{
	//		remove("C:\\Windows\\soarwazhere.soar");
	//	}
	//}



	//login
	system("cls");
	std::cout << std::endl;

	//Log3("License -> ");
	//std::cin >> lol2;
	//if (lol2 != "SamsungFree")
	//{
	//	std::cout << std::endl;
	//	Log3("Invalid License.");
	//	Sleep(3500);
	//	main(argc, argv);
	//}
	//KeyAuthApp.log("License Approved, Logged.");
	//SaveLicense(lol2);


	menu:
	system("cls");
	//menu
	std::cout << std::endl;
	Log3("Select an Listed Option.\n");
	Log3("1) Load Driver\n");
	Log3("2) Load Fortnite\n");
	Log3("3) Website\n");

	std::cout << std::endl;
	Log3("Input -> ");
	std::string lol;
	std::cin >> lol;
	if (lol == "1")
	{
		LoadDriver();
		goto menu;
	}
	if (lol == "3")
	{
		system("start https://samsungcheats.com/");
		goto menu;
	}
	if (lol != "3" && lol != "1" && lol != "2")
	{
		goto menu;
	}
		// start fn cheeto

drivercheck:
		system("cls");
		externalcheck:
	std::cout << "" << std::endl;
	Log3("Waiting For Fortnite...\n");
	while (hwnd == NULL)
	{

		XorS(wind, "Fortnite  ");
		hwnd = FindWindowA(0, wind.decrypt());
		Sleep(100);
	}

	Log3("Press F2 In Lobby...\n\n");
	while (true)
	{
		if (GetAsyncKeyState(VK_F2))
		{
			break;
			Beep(300, 300);
		}
	}
	driver->process_id = process_find("FortniteClient-Win64-Shipping.exe");
	driver->Init(FALSE);

	driver->Attach(driver->process_id);
	if (!driver->process_id) {
		Log3("Process Error Occured Contact Support.\n");
		Sleep(2000);
		return 0;
	}
	Log3("PID -> ");
	Sleep(500);
	std::cout << driver->process_id << std::endl;

	base_address = driver->GetModuleBase(L"FortniteClient-Win64-Shipping.exe");
	Sleep(500);
	Log3("Successfully Attached...\n");
	Sleep(500);
	Log3("Base Address -> 0x");
	std::cout << (void*)base_address << std::endl;

	Sleep(2500);
	xCreateWindow();
	xInitD3d();

	xMainLoop();
	xShutdown();

	return 0;
}



void xInitD3d()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;
	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime;
	(void)io;
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\arial.ttf", 15);
	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);
	p_Object->Release();
}

void aimbot(float x, float y)
{
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	int AimSpeed = base::smoothing * 2;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

	return;
}

bool isVisible(uint64_t mesh)
{
	float bing = read<float>(mesh + 0x360);
	float bong = read<float>(mesh + 0x368);
	const float tick = 0.06f;
	return bong + tick >= bing;
}

void AimAt(DWORD_PTR entity)
{
	uint64_t currentactormesh = read<uint64_t>(entity + offsets::Mesh);
	auto rootHead = GetBoneWithRotation(currentactormesh, 67);
	Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

	if (rootHeadOut.y != 0 || rootHeadOut.y != 0)
	{
		aimbot(rootHeadOut.x, rootHeadOut.y);
	}
}

RGBA FovColor = Col.purple;
RGBA SnapLineColor = Col.blue;
RGBA BoxColor = Col.red;
float FovThickness = 25;


#define PI (3.141592653589793f)


void DrawSkeleton(DWORD_PTR CurrentActorMesh, bool visible)
{
	if (!visible)
	{
		Vector3 vHip = GetBoneWithRotation(CurrentActorMesh, 2);
		Vector3 vNeck = GetBoneWithRotation(CurrentActorMesh, 67);
		Vector3 vUpperArmLeft = GetBoneWithRotation(CurrentActorMesh, 9);
		Vector3 vUpperArmRight = GetBoneWithRotation(CurrentActorMesh, 38);
		Vector3 vLeftHand = GetBoneWithRotation(CurrentActorMesh, 10);
		Vector3 vRightHand = GetBoneWithRotation(CurrentActorMesh, 39);
		Vector3 vLeftHand1 = GetBoneWithRotation(CurrentActorMesh, 30);
		Vector3 vRightHand1 = GetBoneWithRotation(CurrentActorMesh, 59);
		Vector3 vRightThigh = GetBoneWithRotation(CurrentActorMesh, 78);
		Vector3 vLeftThigh = GetBoneWithRotation(CurrentActorMesh, 71);
		Vector3 vRightCalf = GetBoneWithRotation(CurrentActorMesh, 79);
		Vector3 vLeftCalf = GetBoneWithRotation(CurrentActorMesh, 72);
		Vector3 vLeftFoot = GetBoneWithRotation(CurrentActorMesh, 73);
		Vector3 vRightFoot = GetBoneWithRotation(CurrentActorMesh, 80);
		Vector3 vPelvisOut = GetBoneWithRotation(CurrentActorMesh, 8);
		Vector3 vPelvis = ProjectWorldToScreen(vPelvisOut);
		Vector3 vHipOut = ProjectWorldToScreen(vHip);
		Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
		Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
		Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
		Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
		Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
		Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
		Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
		Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
		Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
		Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
		Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
		Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
		Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
		DrawLine(vHipOut.x, vHipOut.y, vNeckOut.x, vNeckOut.y, &Col.orange, 0.6f);
		DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.orange, 0.6f);
		DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.orange, 0.6f);
		DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.orange, 0.6f);
		DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.orange, 0.6f);
		DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, &Col.orange, 0.6f);
		DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, &Col.orange, 0.6f);
		DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, &Col.orange, 0.6f);
		DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, &Col.orange, 0.6f);
		DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.orange, 0.6f);
		DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.orange, 0.6f);
		DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.orange, 0.6f);
		DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.orange, 0.6f);
	}
	if (visible)
	{
		Vector3 vHeadBone = GetBoneWithRotation(CurrentActorMesh, 106);
		Vector3 vHip = GetBoneWithRotation(CurrentActorMesh, 2);
		Vector3 vNeck = GetBoneWithRotation(CurrentActorMesh, 67);
		Vector3 vUpperArmLeft = GetBoneWithRotation(CurrentActorMesh, 9);
		Vector3 vUpperArmRight = GetBoneWithRotation(CurrentActorMesh, 38);
		Vector3 vLeftHand = GetBoneWithRotation(CurrentActorMesh, 10);
		Vector3 vRightHand = GetBoneWithRotation(CurrentActorMesh, 39);
		Vector3 vLeftHand1 = GetBoneWithRotation(CurrentActorMesh, 30);
		Vector3 vRightHand1 = GetBoneWithRotation(CurrentActorMesh, 59);
		Vector3 vRightThigh = GetBoneWithRotation(CurrentActorMesh, 78);
		Vector3 vLeftThigh = GetBoneWithRotation(CurrentActorMesh, 71);
		Vector3 vRightCalf = GetBoneWithRotation(CurrentActorMesh, 79);
		Vector3 vLeftCalf = GetBoneWithRotation(CurrentActorMesh, 72);
		Vector3 vLeftFoot = GetBoneWithRotation(CurrentActorMesh, 73);
		Vector3 vRightFoot = GetBoneWithRotation(CurrentActorMesh, 80);
		Vector3 vPelvisOut = GetBoneWithRotation(CurrentActorMesh, 8);
		Vector3 vHead = ProjectWorldToScreen(vHeadBone);
		Vector3 vPelvis = ProjectWorldToScreen(vPelvisOut);
		Vector3 vHipOut = ProjectWorldToScreen(vHip);
		Vector3 vNeckOut = ProjectWorldToScreen(vNeck);
		Vector3 vUpperArmLeftOut = ProjectWorldToScreen(vUpperArmLeft);
		Vector3 vUpperArmRightOut = ProjectWorldToScreen(vUpperArmRight);
		Vector3 vLeftHandOut = ProjectWorldToScreen(vLeftHand);
		Vector3 vRightHandOut = ProjectWorldToScreen(vRightHand);
		Vector3 vLeftHandOut1 = ProjectWorldToScreen(vLeftHand1);
		Vector3 vRightHandOut1 = ProjectWorldToScreen(vRightHand1);
		Vector3 vRightThighOut = ProjectWorldToScreen(vRightThigh);
		Vector3 vLeftThighOut = ProjectWorldToScreen(vLeftThigh);
		Vector3 vRightCalfOut = ProjectWorldToScreen(vRightCalf);
		Vector3 vLeftCalfOut = ProjectWorldToScreen(vLeftCalf);
		Vector3 vLeftFootOut = ProjectWorldToScreen(vLeftFoot);
		Vector3 vRightFootOut = ProjectWorldToScreen(vRightFoot);
		DrawLine(vHead.x, vHead.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
		DrawLine(vHipOut.x, vHipOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
		DrawLine(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
		DrawLine(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, &Col.white, 0.6f);
		DrawLine(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, &Col.white, 0.6f);
		DrawLine(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, &Col.white, 0.6f);
		DrawLine(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, &Col.white, 0.6f);
		DrawLine(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, &Col.white, 0.6f);
		DrawLine(vLeftThighOut.x, vLeftThighOut.y, vHipOut.x, vHipOut.y, &Col.white, 0.6f);
		DrawLine(vRightThighOut.x, vRightThighOut.y, vHipOut.x, vHipOut.y, &Col.white, 0.6f);
		DrawLine(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, &Col.white, 0.6f);
		DrawLine(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, &Col.white, 0.6f);
		DrawLine(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, &Col.white, 0.6f);
		DrawLine(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, &Col.white, 0.6f);
	}
}

void DrawCorneredTriangle(int x, int y, int w, int h, ImColor color, int thickness) {
	ImDrawList* Drawlist = ImGui::GetOverlayDrawList();
	float half_w = w / 2;
	Drawlist->AddLine(ImVec2(x, y + h), ImVec2(x + half_w, y), color, thickness);
	Drawlist->AddLine(ImVec2(x + half_w, y), ImVec2(x + w, y + h), color, thickness);
	Drawlist->AddLine(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thickness);
}

bool IsInScreen(Vector3 pos, int over = 40) {
	if (pos.x > -over && pos.x < Width + over && pos.y > -over && pos.y < Height + over) {
		return true;
	}
	else {
		return false;
	}
}
bool debug = false;

void worldloop()
{
	samsung::Uworld = read<DWORD_PTR>(base_address + OFFSET_UWORLD);
	samsung::GameInstance = read<DWORD_PTR>(samsung::Uworld + offsets::Gameinstance);
	samsung::LocalPlayers = read<DWORD_PTR>(samsung::GameInstance + offsets::LocalPlayers);
	samsung::Localplayer = read<DWORD_PTR>(samsung::LocalPlayers);
	samsung::PlayerController = read<DWORD_PTR>(samsung::Localplayer + offsets::PlayerController);
	samsung::LocalPawn = read<DWORD_PTR>(samsung::PlayerController + offsets::LocalPawn);
	samsung::PlayerState = read<DWORD_PTR>(samsung::LocalPawn + offsets::PlayerState);
	samsung::Rootcomp = read<DWORD_PTR>(samsung::LocalPawn + offsets::RootComponet);
	samsung::Persistentlevel = read<DWORD_PTR>(samsung::Uworld + offsets::PersistentLevel);
	samsung::ActorCount = read<DWORD>(samsung::Persistentlevel + offsets::ActorCount);
	samsung::AActors = read<DWORD_PTR>(samsung::Persistentlevel + offsets::AActor);


	if (debug)
	{
		std::cout << "Gworld -> " << (void*)samsung::Uworld << std::endl;
		std::cout << "ginstance -> " << (void*)samsung::GameInstance << std::endl;
		std::cout << "lplayers -> " << (void*)samsung::LocalPlayers << std::endl;
		std::cout << "lplayer -> " << (void*)samsung::Localplayer << std::endl;
		std::cout << "pcontroller -> " << (void*)samsung::PlayerController << std::endl;
		std::cout << "lpawn -> " << (void*)samsung::LocalPawn << std::endl;
		std::cout << "pstate -> " << (void*)samsung::PlayerState << std::endl;
		std::cout << "rcomponent -> " << (void*)samsung::Rootcomp << std::endl;
		std::cout << "perlevel -> " << (void*)samsung::Persistentlevel << std::endl;
		std::cout << "acount -> " << samsung::ActorCount << std::endl;
		std::cout << "aactor -> " << (void*)samsung::AActors << std::endl;
	}
}

void actorloop() 
{


	auto entityListCopy = entityList;
	float closestDistance = 280;
	DWORD_PTR closestPawn = NULL;
	std::vector<FNlEntity> tmpList;

	worldloop();
	if (samsung::LocalPawn)
	{
		for (int i = 0; i < samsung::ActorCount; i++)
		{
			uint64_t CurrentActor = read<uint64_t>(samsung::AActors + i * offsets::CurrentActor);
			uint64_t CurrentActorMesh = read<uint64_t>(CurrentActor + offsets::Mesh);
			//uintptr_t CurrentWeapon = read<uintptr_t>(samsung::LocalPawn + 0x948);
			bool isDBNO = (read<BYTE>(CurrentActor + 0x4BC) >> 4) & 1;
			//bool bIsReloadingWeapon = read<bool>(CurrentWeapon + 0x331);
			if (read<float>(CurrentActor + offsets::Revivefromdbnotime) != 10) continue;
			int MyTeamId = read<int>(samsung::PlayerState + offsets::TeamId);
			DWORD64 otherPlayerState = read<uint64_t>(CurrentActor + offsets::PlayerState);
			int ActorTeamId = read<int>(otherPlayerState + offsets::ActorTeamId);
			if (MyTeamId == ActorTeamId) continue;
			if (CurrentActor == samsung::LocalPawn) continue;
				Vector3 Headpos = GetBoneWithRotation(CurrentActorMesh, 106);
			samsung::localactorpos = read<Vector3>(samsung::Rootcomp + offsets::LocalActorPos);
			float distance = samsung::localactorpos.Distance(Headpos) / 100.f;
			Vector3 bone0 = GetBoneWithRotation(CurrentActorMesh, 0);
			Vector3 bottom = ProjectWorldToScreen(bone0);
			Vector3 Headbox = ProjectWorldToScreen(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));
			Vector3 w2shead = ProjectWorldToScreen(Headpos);
			if (!IsInScreen(bottom)) continue;


			float BoxHeight = (float)(Headbox.y - bottom.y);
			float BoxWidth = BoxHeight * 0.75f;

			float LeftX = (float)Headbox.x - (BoxWidth / 1);
			float LeftY = (float)bottom.y;

			float CornerHeight = abs(Headbox.y - bottom.y);
			float CornerWidth = CornerHeight * 0.50;

			if (distance < base::visdistance)
			{
				if (base::boxes)
				{
					if (isVisible(CurrentActorMesh) && base::vischeck)
						DrawBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, &Col.lightblue);
					else
						DrawBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, &Col.red);
				}
				if (base::cornerbox)
				{
					if (isVisible(CurrentActorMesh) && base::vischeck)
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, &Col.lightblue, 0.3);
					else
						DrawCorneredBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, &Col.red, 0.3);
				}
				if (base::skeleton)
				{
					if (isVisible(CurrentActorMesh) && base::vischeck)
						DrawSkeleton(CurrentActorMesh, true);
					else 
						DrawSkeleton(CurrentActorMesh, false);
				}
				if (base::snaplines)
				{
					DrawLine(Width / 2, 0, Headbox.x, Headbox.y, &Col.lightblue, 1.0);
				}

			}
			if (base::fovchanger)
			{
				uintptr_t PlayerCameraManager = read<uintptr_t>(samsung::PlayerController + 0x348);
				write<float>(PlayerCameraManager + 0x2A4 + 0x4, 130);
			}
			if (base::norecoil)
			{
				if (GetAsyncKeyState(VK_LBUTTON))
				{
					write<float>(samsung::PlayerController + 0x64, -1); //CustomTimeDilation Offset
				}
				else
				{
					write<float>(samsung::PlayerController + 0x64, -1); //CustomTimeDilation Offset
				}
			}

			if (base::legitaim)
				base::smoothing = 5;
			else if (!base::legitaim)
				base::smoothing = 1.5;



			auto dx = w2shead.x - (Width / 2);
			auto dy = w2shead.y - (Height / 2);
			auto dist = sqrtf(dx * dx + dy * dy);
			if (dist < base::fovsize && dist < closestDistance && isVisible(CurrentActorMesh))
			{
				closestDistance = dist;
				closestPawn = CurrentActor;
			}
			if (base::aimbot && closestPawn && isVisible(CurrentActorMesh) && !isDBNO && GetAsyncKeyState(VK_RBUTTON) < 0)
			{
				AimAt(closestPawn);
			}
		}

	}
}

ImVec2 p;
int tab;

namespace Render
{
	struct vec_2
	{
		int x, y;
	};

	struct Colors
	{
		ImColor red = { 255, 0, 0, 255 };
		ImColor green = { 0, 255, 0, 255 };
		ImColor blue = { 0, 136, 255, 255 };
		ImColor aqua_blue = { 0, 255, 255, 255 };
		ImColor cyan = { 0, 210, 210, 255 };
		ImColor royal_purple = { 102, 0, 255, 255 };
		ImColor dark_pink = { 255, 0, 174, 255 };
		ImColor black = { 0, 0, 0, 255 };
		ImColor white = { 255, 255, 255, 255 };
		ImColor purple = { 255, 0, 255, 255 };
		ImColor yellow = { 255, 255, 0, 255 };
		ImColor orange = { 255, 140, 0, 255 };
		ImColor gold = { 234, 255, 0, 255 };
		ImColor royal_blue = { 0, 30, 255, 255 };
		ImColor dark_red = { 150, 5, 5, 255 };
		ImColor dark_green = { 5, 150, 5, 255 };
		ImColor dark_blue = { 100, 100, 255, 255 };
		ImColor navy_blue = { 0, 73, 168, 255 };
		ImColor light_gray = { 200, 200, 200, 255 };
		ImColor dark_gray = { 150, 150, 150, 255 };
	};
	Colors color;

	void Text(int posx, int posy, ImColor clr, const char* text)
	{
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx, posy), ImColor(clr), text);
	}

	void OutlinedText(int posx, int posy, ImColor clr, const char* text)
	{
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx + 1, posy + 1), ImColor(color.black), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx - 1, posy - 1), ImColor(color.black), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx + 1, posy + 1), ImColor(color.black), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx - 1, posy - 1), ImColor(color.black), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx, posy), ImColor(clr), text);
	}

	void ShadowText(int posx, int posy, ImColor clr, const char* text)
	{
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx + 1, posy + 2), ImColor(0, 0, 0, 200), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx + 1, posy + 2), ImColor(0, 0, 0, 200), text);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(posx, posy), ImColor(clr), text);
	}

	void Rect(int x, int y, int w, int h, ImColor color, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0, thickness);
	}

	void RectFilledGradient(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void RectFilled(int x, int y, int w, int h, ImColor color)
	{
		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color)), 0, 0);
	}

	void Checkbox(const char* v, bool* option, float x, float y, const char* title)
	{
		ImGui::SetCursorPos({ x, y });
		ImGui::Checkbox(v, option);

		p = ImGui::GetWindowPos();

		ImGui::SetCursorPos({ x + 2, y - 20 });
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(0, 245, 245)));
		ImGui::Text(title);
		ImGui::PopStyleColor();

		Render::RectFilled(p.x + x + 3, p.y + y + 3, 16, 16, ImColor(200, 200, 200));

		if (*option)
		{
			Render::RectFilled(p.x + x + 7, p.y + y + 7, 8, 8, ImColor(0, 0, 0, 255));
		}
	}

	void Slider(const char* v, float* option, float x, float y, float min, float max, const char* title)
	{
		ImGui::SetCursorPos({ x, y });
		ImGui::SliderFloat(v, option, min, max);

		ImGui::SetCursorPos({ x + 2, y - 20 });
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(0, 245, 245)));
		ImGui::Text(title);
		ImGui::PopStyleColor();
	}

	void SliderInt(const char* v, int* option, float x, float y, int min, int max, const char* title)
	{
		ImGui::SetCursorPos({ x, y });
		ImGui::SliderInt(v, option, min, max);

		ImGui::SetCursorPos({ x + 2, y - 20 });
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(0, 245, 245)));
		ImGui::Text(title);
		ImGui::PopStyleColor();
	}

	void Tab(const char* v, float size_x, float size_y, static int tab_name, int tab_next)
	{
		if (ImGui::Button(v, ImVec2{ size_x, size_y })) tab_name = tab_next;
	}
}

std::string CheckTrue(bool main)
{
	if (main)
	{
		return "ON";
	}
	if (!main)
	{
		return "OFF";
	}
}
void render() 
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	actorloop();
	if (base::drawfov)
	{
		DrawCircle(ScreenCenterX, ScreenCenterY, base::fovsize, &Col.white, 150, 1);
	}
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		ShowMenu = !ShowMenu;
	}






	ImGui::GetOverlayDrawList()->AddText(ImVec2(20, 20), ImColor(0, 154, 255), "SamsungCheats", NULL);

	if (ShowMenu)
	{

		int x = 20;
		int y = 30;

		std::string TITLETEXT = ("                             Samsung");

		if (GetAsyncKeyState(VK_F1) & 1)
			base::aimbot = !base::aimbot;
		if (GetAsyncKeyState(VK_F2) & 1)
			base::drawfov = !base::drawfov;
		if (GetAsyncKeyState(VK_F3) & 1)
			base::legitaim = !base::legitaim;
		if (GetAsyncKeyState(VK_F4) & 1)
			base::vischeck = !base::vischeck;
		if (GetAsyncKeyState(VK_F5) & 1)
			base::boxes = !base::boxes;
		if (GetAsyncKeyState(VK_F6) & 1)
			base::cornerbox = !base::cornerbox;
		if (GetAsyncKeyState(VK_F7) & 1)
			base::skeleton = !base::skeleton;
		if (GetAsyncKeyState(VK_F8) & 1)
			base::snaplines = !base::snaplines;
		if (GetAsyncKeyState(VK_F9) & 1)
			base::norecoil = !base::norecoil;
		if (GetAsyncKeyState(VK_F10) & 1)
			base::fovchanger = !base::fovchanger;
		if (GetAsyncKeyState(VK_F2) & 1)
			base::spinbot = !base::spinbot;

		std::string aimbot = CheckTrue(base::aimbot);
		std::string cornerbox = CheckTrue(base::cornerbox);
		std::string drawfov = CheckTrue(base::drawfov);
		std::string box = CheckTrue(base::boxes);
		std::string aimfov = CheckTrue(base::vischeck);
		std::string smoothing = CheckTrue(base::legitaim);
		std::string lines = CheckTrue(base::snaplines);
		std::string recoil = CheckTrue(base::norecoil);
		std::string skeleton = CheckTrue(base::skeleton);
		std::string spinbot = CheckTrue(base::spinbot);
		std::string fovchange = CheckTrue(base::fovchanger);
		
		

		Draw::BackgroundFilled(x, y, 273, -2, &Draw::Color.lightblue);
		Draw::BackgroundFilled(x, y, 273, 270, &Draw::Color.lightblue);
		Draw::BackgroundFilled(x, y, -2, 270, &Draw::Color.lightblue);
		Draw::BackgroundFilled(x, y, 271, 268, &Draw::Color.black);
		Draw::RegularText(x + 4, y + 4, &Draw::Color.white, TITLETEXT.c_str());

		Draw::RegularText(x + 6, y + 45, &Draw::Color.white, ("F1 : Aimbot ")); Draw::RegularText(x + 234, y + 45, &Draw::Color.white, aimbot.c_str());
		Draw::RegularText(x + 6, y + 65, &Draw::Color.white, ("F2 : Draw FOV "));  Draw::RegularText(x + 234, y + 65, &Draw::Color.white, drawfov.c_str());
		Draw::RegularText(x + 6, y + 85, &Draw::Color.white, ("F3 : Legit Aimbot ")); Draw::RegularText(x + 234, y + 85, &Draw::Color.white, smoothing.c_str());
		Draw::RegularText(x + 6, y + 105, &Draw::Color.white, ("F4 : Visible Check ")); Draw::RegularText(x + 234, y + 105, &Draw::Color.white, aimfov.c_str());
		Draw::RegularText(x + 6, y + 125, &Draw::Color.white, ("F5 : Box "));  Draw::RegularText(x + 234, y + 125, &Draw::Color.white, box.c_str());
		Draw::RegularText(x + 6, y + 145, &Draw::Color.white, ("F6 : Corner Box "));  Draw::RegularText(x + 234, y + 145, &Draw::Color.white, cornerbox.c_str());
		Draw::RegularText(x + 6, y + 165, &Draw::Color.white, ("F7 : Skeleton "));  Draw::RegularText(x + 234, y + 165, &Draw::Color.white, skeleton.c_str());
		Draw::RegularText(x + 6, y + 185, &Draw::Color.white, ("F8 : Snaplines "));  Draw::RegularText(x + 234, y + 185, &Draw::Color.white, lines.c_str());
		Draw::RegularText(x + 6, y + 205, &Draw::Color.white, ("F9 : No Recoil ")); Draw::RegularText(x + 234, y + 205, &Draw::Color.white, recoil.c_str());
		Draw::RegularText(x + 6, y + 225, &Draw::Color.white, ("F10 : FOV 120 ")); Draw::RegularText(x + 234, y + 225, &Draw::Color.white, fovchange.c_str());
	}

	actorloop();

	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}


MSG Message = { NULL };

void xMainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		xShutdown();
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = D3dDevice->Reset(&d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

void xShutdown()
{
	TriBuf->Release();
	D3dDevice->Release();
	p_Object->Release();

	DestroyWindow(Window);
	UnregisterClass("AFX:03300000111", NULL);
}