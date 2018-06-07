

static void PostFilter(MyBuffer* buffer, int window_width, int window_height, GLfloat* AccBuffer) {
    auto pixels = buffer->GetPixels();
    GLfloat middle, up, down, right, left, up_left, up_right, down_left, down_right;
    int lengthOfStringOfPixels = 3*window_width;

    for (COLOR_TYPE k = RED; k <= BLUE; k = (COLOR_TYPE)((int)k + 1)) {

        for (int i = 1; i < window_height - 1; i++) { //middle
            for (int j = 1; j < window_width - 1; j++) {
                int begin = lengthOfStringOfPixels * i;
                int middleIndex = begin + j*3 + k;

                middle = pixels[middleIndex];
                up = pixels[middleIndex + lengthOfStringOfPixels];
                down = pixels[middleIndex - lengthOfStringOfPixels];
                right = pixels[middleIndex + 3];
                left = pixels[middleIndex - 3];
                up_left = pixels[middleIndex + lengthOfStringOfPixels - 3];
                up_right = pixels[middleIndex + lengthOfStringOfPixels + 3];
                down_left = pixels[middleIndex - lengthOfStringOfPixels - 3];
                down_right = pixels[middleIndex - lengthOfStringOfPixels + 3];
                middle *= 4;
                middle += up_left + up_right + down_left + down_right + 2 * up + 2 * down + 2 * left + 2 * right;
                middle /= 16.0;
                AccBuffer[middleIndex] = middle;
            }
        }
    }

    glDrawPixels(window_width, window_height, GL_RGB, GL_FLOAT, AccBuffer);
}
