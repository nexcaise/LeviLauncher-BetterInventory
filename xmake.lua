set_project("OffhandMod")
set_version("1.0.0")

set_languages("c99", "cxx23")

add_rules("mode.release")

add_cxflags(
    "-O2",
    "-fvisibility=hidden",
    "-ffunction-sections",
    "-fdata-sections",
    "-w"
)

add_cflags(
    "-O2",
    "-fvisibility=hidden",
    "-ffunction-sections",
    "-fdata-sections",
    "-w"
)

add_ldflags(
    "-Wl,--gc-sections",
    "-Wl,--strip-all",
    "-s",
    {force = true}
)

add_repositories("xmake-repo https://github.com/xmake-io/xmake-repo.git")

add_requires(
    "fmt 10.2.1",
    "glm 0.9.9+8"
)

target("BetterInventory")
    set_kind("shared")
    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp", "preloader/src/**.h")
    add_includedirs(
        "src",
        "preloader/src",
        {public = true}
    )
    add_linkdirs("preloader/lib")
    add_packages("fmt", "glm")
    add_links("log", "preloader")