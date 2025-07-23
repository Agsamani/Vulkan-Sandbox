project("Vulframe")
kind("StaticLib")
language("C++")
cppdialect("C++17")
staticruntime("off")

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

--pchheader "rktpch.h"
--pchsource "src/rktpch.cpp"

files({
	"src/**.h",
	"src/**.cpp",

	"vendor/glm/glm/**.hpp",
	"vendor/glm/glm/**.inl",
})

defines({
	"_CRT_SECURE_NO_WARNINGS",
	--"GLFW_INCLUDE_NONE",
	"GLFW_INCLUDE_VULKAN",
})

includedirs({
	"src",
	"%{IncludeDir.GLFW}",
	"%{IncludeDir.glm}",
	"%{IncludeDir.Vulkan}",
})

libdirs({
	"%{wks.location}/Vulframe/vendor/GLFW/lib-vc2022",
	"%{vlk_env_var}/Lib",
})
links({
	"glfw3.lib",
	"vulkan-1.lib",
})

filter("system:windows")
systemversion("latest")

filter("configurations:Debug")
defines("VLF_DEBUG")
runtime("Debug")
symbols("on")

filter("configurations:Release")
defines("VLF_RELEASE")
runtime("Release")
optimize("on")

filter("")
