include("Dependencies")

workspace("Vulframe")
architecture("x64")
startproject("Vulframe")

configurations({ "Debug", "Release" })

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include("Vulframe")
