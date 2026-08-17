include("Dependencies")

workspace("Vulframe")
architecture("x64")
startproject("Sandbox")

configurations({ "Debug", "Release" })

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include("Vulframe")
include("Sandbox")
