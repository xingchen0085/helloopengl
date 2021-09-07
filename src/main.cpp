#include <iostream>
#include "main.h"

using namespace std;

const char* VERTEX_SHADER = "#version 330 core\n"
                            "attribute vec4 a_position;\n"
                            "void main(){\n"
                            "    gl_Position = vec4(a_position.x,a_position.y,a_position.z,1.0f);\n"
                            "    gl_PointSize = 10.0f;\n"
                            "}";
const char* FRAGMENT_SHADER = "#version 330 core\n"
                              "uniform u_color\n"
                              "void main(){\n"
                              "    framgColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
                              "}";

int main()
{
    //1、初始化GLFW
    if (!glfwInit()) {
        cout << "glfw init is failed!" << endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//opengl3.3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //2.创建一个窗口
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"OpenGL3",NULL,NULL);
    if (nullptr == window) {
        cout << "create window is failed!" << endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    //2.1将指针交给GLAD管理
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "glad load glfw pointer failed!" << endl;
        return -1;
    }

    //2.2初始化视口和绑定窗口大小发生改变时监听
    framebuff_size_callback(window,WINDOW_WIDTH,WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window,framebuff_size_callback);

    int program = getProgram(window, VERTEX_SHADER, FRAGMENT_SHADER);

    float positions[] = {
            0.5f, 0.5f, 0.0f,
            -0.5f,-0.5f,0.0f,
            0.5f, -0.5f, 0.0f,
    };

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);


    //3.主循环
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0 , 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //4.关闭
    glfwTerminate();
    return 0;
}

void framebuff_size_callback(GLFWwindow *pWwindow, const int width, const int height) {
    glViewport(0, 0, width, height);
}


int getProgram(GLFWwindow *pWwindow, const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VERTEX_SHADER, NULL);
    glCompileShader(vertexShader);

    unsigned  int fragemnetShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragemnetShader, 1, &FRAGMENT_SHADER, NULL);
    glCompileShader(fragemnetShader);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragemnetShader);
    glLinkProgram(program);

    return program;
}
