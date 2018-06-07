
// Shaders
const GLchar* vertexShaderSource = "#version 330\n"
        "layout (location = 0) in vec3 position;\n"
        "layout (location = 1) in vec3 color;\n"
        "out vec3 ourColor;\n"
        "uniform mat4 transform;\n"
        "void main()\n"
        "{\n"
        "gl_Position = transform * vec4(position, 1.0f);\n"
        "ourColor = color;"
        "}\0";

const GLchar* colorShaderSource = "#version 330\n"
        "in vec3 ourColor;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(ourColor, 1.0);\n"
        "}\0";


void compileShader(GLint name, const GLchar* data) {

    GLint success;
    GLchar infoLog[512];

    glShaderSource(name, 1, &data, NULL);
    glCompileShader(name);

    // Check for compile time errors
    glGetShaderiv(name, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(name, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

GLuint linkProgram(GLuint vertex_sh, GLuint fragment_sh) {
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertex_sh);
    glAttachShader(shaderProgram, fragment_sh);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        throw;
    }

    return shaderProgram;
}

void shadersInit(GLint& shader) {

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        throw;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShader, vertexShaderSource);

    GLuint colorShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(colorShader, colorShaderSource);

    shader = linkProgram(vertexShader, colorShader);

    glDeleteShader(vertexShader);
    glDeleteShader(colorShader);
}
