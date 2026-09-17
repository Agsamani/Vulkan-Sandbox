#pragma once
#include "vulkan/vulkan_core.h"
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class HelloTriangleApplication
{
  public:
	void run();

  private:
	void initWindow();
	void initVulkan();
	void mainLoop();
	void cleanup();

	void *window = nullptr;

	VkInstance m_Instance;
	VkSurfaceKHR m_Surface;
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;

	const std::vector<const char *> deviceExtentions{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME};

	void createInstance();
	void createSurface();
	void pickPhysicalDevice();
	bool extensionsSuported(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamily(VkPhysicalDevice device);
	void createLogicalDevice();
};
