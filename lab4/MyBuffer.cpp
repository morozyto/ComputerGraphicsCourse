#include <OpenGL/OpenGL.h>
#include "MyBuffer.h"
#include "Bresenhem.h"

using namespace std;

MyBuffer::MyBuffer(int height, int width) {
    buffer = new GLfloat[width*height*3];
    this->height = height;
    this->width = width;
    Refresh();
}

MyBuffer::~MyBuffer() {
    delete[] buffer;
}

GLfloat MyBuffer::GetPixel(int height, int width, COLOR_TYPE colour) {
    if (height < 0 || height >= this->height || width < 0 || width > this->width) {
        if (colour == RED) return BoardRed;
        if (colour == GREEN) return BoardGreen;
        else return BoardBlue;
    }
    return buffer[height*(this->width)*3 + width*3 + colour];
}

void MyBuffer::SetPixel(int height, int width, COLOR_TYPE colour, GLfloat value) {
    buffer[height*(this->width)*3 + width*3 + colour] = value;
}

void MyBuffer::Resize(int height, int width) {
    this->height = height;
    this->width = width;
    delete[] buffer;
    buffer = new GLfloat[width*height*3];
    Refresh();
}

void MyBuffer::Refresh() {
    for (int i = 0; i < width*height; i++) {
        buffer[i*3] = 0.0;
        buffer[i*3 + 1] = 0.0;
        buffer[i*3 + 2] = 0.0;
    }
    points.clear();
}

GLfloat* MyBuffer::GetPixels() {
    return buffer;
}

void MyBuffer::ColorBoardPixel(int x, int y) {
    SetPixel(y, x, RED, BoardRed);
    SetPixel(y, x, GREEN, BoardGreen);
    SetPixel(y, x, BLUE, BoardBlue);
}

bool MyBuffer::checkPixelNotBoard(int x, int y)
{
    if (GetPixel(y, x, RED) != BoardRed || GetPixel(y, x, GREEN) != BoardGreen ||
        GetPixel(y, x, BLUE) != BoardBlue) return true;
    return false;
}

void MyBuffer::coloring(int x0, int y0) {
    vector<Pixel> stack;
    stack.emplace_back(x0, y0);
    while (!stack.empty()) {
        Pixel a = stack[stack.size() - 1];
        int x = a.GetX(), y = a.GetY();
        stack.pop_back();
        ColorBoardPixel(x, y);

        int temp_x = x;
        x++;
        while (checkPixelNotBoard(x, y)) {
            ColorBoardPixel(x, y);
            x++;
        }
        int x_right = x - 1;
        x = temp_x;
        x--;
        while (checkPixelNotBoard(x, y)) {
            ColorBoardPixel(x, y);
            x--;
        }
        int x_left = x + 1;

        x = x_left;
        y += 1;
        while (x <= x_right) {
            bool flag = false;

            while (checkPixelNotBoard(x, y) && (x < x_right)) {
                if (!flag) flag = true;
                x += 1;
            }


            if (flag) {
                if (x == x_right && checkPixelNotBoard(x, y)) {
                    stack.emplace_back(x, y);
                } else {
                    stack.emplace_back(x - 1, y);
                }
                flag = false;
            }

            int x_enter = x;
            while (!checkPixelNotBoard(x, y) && (x < x_right)) {
                x += 1;
            }
            if (x == x_enter) x++;
        }

        if (checkPixelNotBoard(x_right, y)) stack.emplace_back(x_right, y);
        if (checkPixelNotBoard(x_left, y)) stack.emplace_back(x_left, y);

        x = x_left;
        y -= 2;

        while (x <= x_right) {
            bool flag = false;

            while (checkPixelNotBoard(x, y) && (x < x_right)) {
                if (!flag) flag = true;
                x += 1;
            }

            if (flag) {
                if (x == x_right && checkPixelNotBoard(x, y)) {
                    stack.emplace_back(x, y);
                } else {
                    stack.emplace_back(x - 1, y);
                }
                flag = false;
            }

            int x_enter = x;
            while (!checkPixelNotBoard(x, y) && (x < x_right)) {
                x += 1;
            }
            if (x == x_enter) x++;
        }
        if (checkPixelNotBoard(x_right, y)) stack.emplace_back(x_right, y);
        if (checkPixelNotBoard(x_left, y)) stack.emplace_back(x_left, y);
    }
}

void MyBuffer::draw_line(int start, int end) {
    auto g = Bresenham(points[start], points[end]);

    for (auto &it : g) {
        ColorBoardPixel(it.GetX(), it.GetY());
    }
}

void MyBuffer::addPoint(std::vector<int>& b) {
    points.push_back(b);
}

void MyBuffer::draw_line_with_previous() {
    if (points.size() > 1) {
        draw_line(points.size() - 2, points.size() - 1);
    }
}

void MyBuffer::draw_last_line() {
    if (points.size() > 2) {
        draw_line(points.size() - 1, 0);
    }
}
