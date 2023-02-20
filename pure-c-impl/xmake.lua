add_requires("fmt")

target("hello")
    set_kind("binary")
    add_files("src/*.c")
    add_includedirs("include")