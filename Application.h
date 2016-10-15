namespace rgb_matrix
{
    class Canvas;
}

class Application
{
private 
    Canvas * mCanvas;
public:
    Application();
    ~Application();
    
    bool Init(int argc, char *argv[]);
    void Run();

    int ExitCode();
};
