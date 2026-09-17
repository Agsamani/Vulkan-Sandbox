#include "HelloTriangleApplication.h"

#include <GLFW/glfw3.h> // Will automatically include Vulkan headers

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

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

  createInstance();
  pickPhysicalDevice();
  createLogicalDevice();
}

void HelloTriangleApplication::mainLoop() {
  while (!glfwWindowShouldClose(static_cast<GLFWwindow *>(window))) {
    glfwPollEvents();
  }
}

void HelloTriangleApplication::cleanup() {
  vkDestroyDevice(m_Device, nullptr);
  vkDestroyInstance(m_Instance, nullptr);
  glfwDestroyWindow(static_cast<GLFWwindow *>(window));

  glfwTerminate();

  window = nullptr;
}

void HelloTriangleApplication::createInstance() {
  VkApplicationInfo appinfo{};
  appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appinfo.pApplicationName = "Hello Triangle";
  appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appinfo.pEngineName = "No Engine";
  appinfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appinfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createinfo{};
  createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createinfo.pApplicationInfo = &appinfo;

  uint32_t glfwExtCount = 0;
  const char **glfwExts;

  glfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);

  createinfo.enabledExtensionCount = glfwExtCount;
  createinfo.ppEnabledExtensionNames = glfwExts;

  createinfo.enabledLayerCount = 0;

  if (vkCreateInstance(&createinfo, nullptr, &m_Instance) != VK_SUCCESS) {
    throw std::runtime_error("failed to create vulkan instance!");
  }
}

void HelloTriangleApplication::pickPhysicalDevice() {
  uint32_t deviceCount = 0;
  vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);

  if (deviceCount == 0) {
    throw std::runtime_error("failed to find GPUs!");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);
  vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

  for (const auto &device : devices) {
    if (isDeviceSuitable(device)) {
      m_PhysicalDevice = device;
      break;
    }
  }

  if (m_PhysicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("failed to find a suitable GPU!");
  }

  VkPhysicalDeviceProperties properties;
  vkGetPhysicalDeviceProperties(m_PhysicalDevice, &properties);

  std::cout << "GPU: " << properties.deviceName << '\n';
  std::cout << "Vendor ID: 0x" << std::hex << properties.vendorID << '\n';
  std::cout << "Device ID: 0x" << std::hex << properties.deviceID << '\n';
  std::cout << "API version: " << VK_VERSION_MAJOR(properties.apiVersion) << "."
            << VK_VERSION_MINOR(properties.apiVersion) << "."
            << VK_VERSION_PATCH(properties.apiVersion) << '\n';
}

bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device) {
  VkPhysicalDeviceProperties deviceProps;
  VkPhysicalDeviceFeatures deviceFeatures;
  vkGetPhysicalDeviceProperties(device, &deviceProps);
  vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

  QueueFamilyIndices indices = findQueueFamily(device);

  return deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
         indices.isComplete();
}

QueueFamilyIndices
HelloTriangleApplication::findQueueFamily(VkPhysicalDevice device) {
  QueueFamilyIndices indices;

  uint32_t familyCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);

  std::vector<VkQueueFamilyProperties> queueFamilies(familyCount);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount,
                                           queueFamilies.data());

  int i = 0;
  for (const auto &family : queueFamilies) {
    if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphicsFamily = i;
    }
    i++;
  }

  return indices;
}

void HelloTriangleApplication::createLogicalDevice() {
  QueueFamilyIndices indices = findQueueFamily(m_PhysicalDevice);

  VkDeviceQueueCreateInfo queueCreateinfo{};
  queueCreateinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateinfo.queueFamilyIndex = indices.graphicsFamily.value();
  queueCreateinfo.queueCount = 1;

  float queuePriority = 1.0f;
  queueCreateinfo.pQueuePriorities = &queuePriority;

  VkDeviceCreateInfo creatinfo{};
  creatinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  creatinfo.pQueueCreateInfos = &queueCreateinfo;
  creatinfo.queueCreateInfoCount = 1;

  VkPhysicalDeviceFeatures deviceFeatures{};
  creatinfo.pEnabledFeatures = &deviceFeatures;

  if (vkCreateDevice(m_PhysicalDevice, &creatinfo, nullptr, &m_Device) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device!");
  }

  vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0,
                   &m_GraphicsQueue);
}
