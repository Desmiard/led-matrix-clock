#ifndef __APPLICATION_H
#define __APPLICATION_H

//
// Forward declarations
//
namespace rgb_matrix
{
    class Canvas;
}

//
// Application
//
class Application
{
private: 
    rgb_matrix::Canvas * mCanvas;

    void DrawFrame();
public:
    Application();
    ~Application();
    
    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};

#endif
