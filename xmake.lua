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
    "glm 0.9.9+8",
    "nlohmann_json 3.11.3"
)

target("preloader")
    set_kind("static")
    add_files("preloader-android/src/**.cpp")
    add_headerfiles("preloader-android/src/**.h")
    add_packages("fmt", "glm", "nlohmann_json")
    add_includedirs("preloader-android/src", {public = true})

target("OffhandMod")
    set_kind("shared")
    add_files("src/**.cpp")
    add_headerfiles("src/**.hpp")
    add_includedirs(
        "src",
        "preloader-android/src",
        {public = true}
    )
    add_deps("preloader")
    add_packages("fmt", "glm", "nlohmann_json")
    add_links("log")