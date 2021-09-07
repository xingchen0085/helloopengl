#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;

void framebuff_size_callback(GLFWwindow *pWwindow, const int width, const int height);

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


    //3.主循环
    while (!glfwWindowShouldClose(window))
    {


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //4.关闭
    glfwTerminate();
    return 0;
}

void framebuff_size_callback(GLFWwindow *pWwindow, const int width, const int height) {
    glViewport(0,0,width,height);
}