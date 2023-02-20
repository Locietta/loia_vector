set_project("Loia's vector demo")

add_rules("mode.debug", "mode.release")
set_languages("cxxlatest")

-- use clang as default compiler on windows
if is_os("windows") then
    set_toolchains("clang-cl")
    set_toolset("ld", "lld-link.exe")
    set_toolset("sh", "lld-link.exe")
    set_toolset("ar", "lld-link.exe")
    -- ignore MS `xxx_s` "safe" functions
    add_defines("_CRT_SECURE_NO_WARNINGS")
end

-- include subprojects
includes("*/xmake.lua")