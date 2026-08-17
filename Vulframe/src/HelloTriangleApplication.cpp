#include "HelloTriangleApplication.h"

#include <GLFW/glfw3.h> // Will automatically include Vulkan headers

#include <cstdlib>
#include <iostream>
#include <stdexcept>

void HelloTriangleApplication::run() {
  initWindow();
  initVulkan();
  mainLoop();
  cleanup();
}

void HelloTriangleApplication::initWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(800, 600, "Vulkan Window", nullptr, nullptr);
}

void HelloTriangleApplication::initVulkan() {
  uint32_t extensionCount = 0;

  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  std::cout << extensionCount << " Vulkan extensions supported." << std::endl;
}

void HelloTriangleApplication::mainLoop() {
  while (!glfwWindowShouldClose(static_cast<GLFWwindow *>(window))) {
    glfwPollEvents();
  }
}

void HelloTriangleApplication::cleanup() {
  glfwDestroyWindow(static_cast<GLFWwindow *>(window));

  glfwTerminate();

  window = nullptr;
}
