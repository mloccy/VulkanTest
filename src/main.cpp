#include <iostream>
#include "app.h"

int main(int argc, char* argv[])
{
    App app(1920, 1080, "My app");

    return app.Run();
}