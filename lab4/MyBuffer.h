#include <OpenGL/OpenGL.h>
#include <vector>


enum COLOR_TYPE {
    RED, GREEN, BLUE
};

class MyBuffer {
private:
    GLfloat *buffer;
    int width, height;
    GLfloat BoardRed = 1.0, BoardGreen = 1.0, BoardBlue = 1.0;
    std::vector<std::vector<int> > points;  //точки для отрисовки

    void draw_line(int start, int end);  // соединяет точки из массива points с индексами start и end

public:
    MyBuffer(int height, int width);

    void ColorBoardPixel(int x, int y);

    bool checkPixelNotBoard(int x, int y);

    GLfloat GetPixel(int height, int width, COLOR_TYPE colour);

    GLfloat* GetPixels();  // возвращает указатель на массив с пикселями для glDrawBuffers()

    void SetPixel(int height, int width, COLOR_TYPE colour, GLfloat value);

    void Refresh();

    void Resize(int height, int width);

    void coloring(int x0, int y0);  //  затравляет область с затравочным пикселем (x0, y0)

    void addPoint(std::vector<int>& b);

    void draw_line_with_previous();

    void draw_last_line();

    ~MyBuffer();
};

