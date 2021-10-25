workspace "AVEngine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

flags {
	"MultiProcessorCompile"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["AVEngine"] = "AVEngine/include"
IncludeDir["GLFW"] = "AVEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "AVEngine/vendor/Glad/include"
IncludeDir["stb"] = "AVEngine/vendor/stb"
IncludeDir["GLM"] = "AVEngine/vendor/GLM"

include "AVEngine/vendor/GLFW"
include "AVEngine/vendor/Glad"
include "AVEngine/vendor/stb"
include "AVEngine/vendor/GLM"

project "AVEngine"
	location "AVEngine"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/include/Renderer.h",
		"%{prj.name}/include/IndexBuffer.h",
		"%{prj.name}/include/Shader.h",
		"%{prj.name}/include/Texture.h",
		"%{prj.name}/include/VertexArray.h",
		"%{prj.name}/include/VertexBuffer.h",
		"%{prj.name}/include/VertexBufferLayout.h",
		"%{prj.name}/src/IndexBuffer.cpp",
		"%{prj.name}/src/Main.cpp",
		"%{prj.name}/src/Renderer.cpp",
		"%{prj.name}/src/Shader.cpp",
		"%{prj.name}/src/Texture.cpp",
		"%{prj.name}/src/VertexArray.cpp",
		"%{prj.name}/src/VertexBuffer.cpp"
	}

	includedirs {
		"%{IncludeDir.AVEngine}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.GLM}"
	}

	links {
		"GLFW",
		"Glad",
		"opengl32.lib",
		"stb",
		"GLM"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "DIST"
		buildoptions "/MD"
		optimize "On"

-- project "Hazel"
-- 	location "Hazel"
-- 	kind "SharedLib"
-- 	language "C++"

-- 	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
-- 	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

-- 	pchheader "hzpch.h"
-- 	pchsource "Hazel/src/hzpch.cpp"

-- 	files
-- 	{
-- 		"%{prj.name}/src/**.h",
-- 		"%{prj.name}/src/**.cpp"
-- 	}

-- 	includedirs
-- 	{
-- 		"%{prj.name}/src",
-- 		"%{prj.name}/vendor/spdlog/include",
-- 		"%{IncludeDir.GLFW}",
-- 		"%{IncludeDir.Glad}"
-- 	}

-- 	links 
-- 	{ 
-- 		"GLFW",
-- 		"Glad",
-- 		"opengl32.lib"
-- 	}

-- 	filter "system:windows"
-- 		cppdialect "C++17"
-- 		staticruntime "On"
-- 		systemversion "latest"

-- 		defines
-- 		{
-- 			"HZ_PLATFORM_WINDOWS",
-- 			"HZ_BUILD_DLL",
-- 			"GLFW_INCLUDE_NONE"
-- 		}

-- 		postbuildcommands
-- 		{
-- 			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
-- 		}

-- 	filter "configurations:Debug"
-- 		defines "HZ_DEBUG"
-- 		buildoptions "/MDd"
-- 		symbols "On"

-- 	filter "configurations:Release"
-- 		defines "HZ_RELEASE"
-- 		buildoptions "/MD"
-- 		optimize "On"

-- 	filter "configurations:Dist"
-- 		defines "HZ_DIST"
-- 		buildoptions "/MD"
-- 		optimize "On"