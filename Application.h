namespace rgb_matrix
{
    class Canvas;
}

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
