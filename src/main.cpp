#include <iostream>

#define GLFW_INCLUDE_NONE
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"

static int width, height;
static int window_width, window_height;
static double retinaScale = 1.0;
static bool window_drag_active = 0;
double cursorX, cursorY;
double deltaX, deltaY;
static double zoom = 1;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f,
};

static const GLuint g_element_buffer_data[] = {
    0, 1, 2, 2, 3, 0,
};

static void glfw_error_callback(int error_code, const char* description) {
  std::cerr << description << std::endl;
}

static void glfw_framebuffer_size_callback(GLFWwindow* window, int fwidth, int fheight) {
  width = fwidth;
  height = fheight;
  std::cout << "width: " << width << " height: " << height << std::endl;
  glViewport(0, 0, width, height);
}

static void glfw_mouse_callback(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    window_drag_active = 1;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    cursorX = x;
    cursorY = y;
  }

  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    static double aspect = (double)width / (double)height;
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    deltaX += aspect * ((cursorX - x) / width * zoom * retinaScale);
    deltaY += (y - cursorY) / height * zoom * retinaScale;
    window_drag_active = 0;
  }
}

static void glfw_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
  static double aspect = (double)width / (double)height;

  if (window_drag_active) {
    deltaX += aspect * ((cursorX - xpos) / width * zoom * retinaScale);
    deltaY += (ypos - cursorY) / height * zoom * retinaScale;
    cursorX = xpos;
    cursorY = ypos;
  }
}

static void glfw_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  if (yoffset > 0) {
    zoom *= 1.1;
  } else {
    zoom /= 1.1;
  }
}

int main(void) {
  GLFWwindow* window;

  glfwSetErrorCallback(glfw_error_callback);

  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

#ifdef __APPLE__
  // We need to explicitly ask for a 3.3 context on macOS
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  // Create a GLFW window
  window = glfwCreateWindow(1280, 720, "Mandelbrot", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create a GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
  glfwSetMouseButtonCallback(window, glfw_mouse_callback);
  glfwSetCursorPosCallback(window, glfw_cursor_pos_callback);
  glfwSetScrollCallback(window, glfw_scroll_callback);

  // Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwGetWindowSize(window, &window_width, &window_height);
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  retinaScale = (double)width / (double)window_width;

  GLuint VAO, VBO, EBO;
  Shader* shader = new Shader();

  // Vertex Array
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Vertex Buffer
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  // Element Buffer
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_element_buffer_data), g_element_buffer_data,
               GL_STATIC_DRAW);

  // Setup the Shader
  shader->init();
  shader->load(GL_VERTEX_SHADER, "VertexShader.vert");
  shader->load(GL_FRAGMENT_SHADER, "FragmentShader.frag");
  shader->link();

  while (!glfwWindowShouldClose(window)) {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
    glDisableVertexAttribArray(0);

    shader->attach();
    shader->setUniform("iterations", 32);
    shader->setUniform("resolution", (GLfloat)width, (GLfloat)height);
    shader->setUniform("offset", (GLfloat)deltaX, (GLfloat)deltaY);
    shader->setUniform("zoom", (GLfloat)zoom);

    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
