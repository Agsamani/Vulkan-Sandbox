IncludeDir = {}

local vulkanSDK = os.getenv("VULKAN_SDK")
assert(vulkanSDK, "VULKAN_SDK environment variable not found")

IncludeDir["GLFW"] = "%{wks.location}/Vulframe/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Vulframe/vendor/glm"
IncludeDir["Vulkan"] = vulkanSDK .. "/Include"

LibraryDir = {}
LibraryDir["Vulkan"] = vulkanSDK .. "/Lib"
