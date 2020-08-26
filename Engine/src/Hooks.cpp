#include "Hooks.h"
#include <Minhook.h>
#include "Renderer.h"

#include <tchar.h>



template <typename T>
inline MH_STATUS MH_CreateHookApiEx(LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, T** ppOriginal)
{
	return MH_CreateHookApi(pszModule, pszProcName, pDetour, reinterpret_cast<LPVOID*>(ppOriginal));
}

RenderHook Hooks::render = RenderHook::None;

void Hooks::Init(RenderHook renderer)
{
	render = renderer;

	if (MH_Initialize() != MH_OK) {
		std::cout << "Failed to initialize hooks\n";
		system("pause");
		exit(-1);
	}

	if (renderer == RenderHook::OpenGL)
	{
		if (MH_CreateHookApiEx(L"opengl32.dll", "wglSwapBuffers", &hwglSwapBuffers, &owglSwapBuffers) != MH_OK) {
			std::cout << "Failed to hook OpenGL wglSwapBuffers\n";
			system("pause");
			exit(-1);
		}
		printf("Successfully hooked OpenGL\n");
	}
	else if (renderer == RenderHook::DirectX)
	{
		std::cout << "DirectX is not supported for now!\n";
		system("pause");
		exit(-1);
	}


	if (MH_EnableHook(MH_ALL_HOOKS)) {
		std::cout << "Failed to enable hooks\n";
		system("pause");
		exit(-1);
	}
}

void Hooks::Remove()
{



    bool uninit = MH_Uninitialize();
    assert(uninit == MH_OK && "Failed to uninitialize minhook!");
}
