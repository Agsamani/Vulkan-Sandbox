IncludeDir = {}
vlk_env_var = os.getenv("VULKAN_SDK")
IncludeDir["GLFW"] = "%{wks.location}/Vulframe/vendor/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/Vulframe/vendor/glm"
IncludeDir["Vulkan"] = "%{vlk_env_var}/Include"
