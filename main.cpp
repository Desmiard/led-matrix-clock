#include "Application.h"

int main(int argc, char *argv[])
{
    Application app;
    if (app.Init(argc, argv)) {
        app.Run();
    }
    return app.ExitCode();
}
