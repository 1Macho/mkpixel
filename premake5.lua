require("mingw64")

workspace "WS_mkpixel"
    configurations { "Debug", "Release" }
    platforms { "l64" }
    filter { "platforms:l64" }
        system "linux"
        architecture "x64"

project "mkpixel"
    kind "ConsoleApp"
    --kind "WindowedApp"
    --kind "SharedLib"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    --targetdir "lib/nxpixel"
    --links { "allegro", "allegro_ttf", "allegro_font", "allegro_color", "allegro_primitives" }
    links { "GL", "glfw", "m"}
    --links { "glfw" }

    --files { "./src/**.h", "./src/**.c" }
    files { "./src/**.h", "./src/**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        --warnings "Extra"
        enablewarnings { "all" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
