#include <iostream>
#include "app.h"
#if defined(_WIN64)
#include <Windows.h>

INT wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, INT nCmdShow)
#else
int main(int argc, char* argv[])
#endif

{
    App app(1920, 1080, "My app", "Shaders");

    return app.Run();
}