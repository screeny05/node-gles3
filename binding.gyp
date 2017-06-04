{
    "targets": [
        {
            "target_name": "glfw",
            "sources": [
                "src/native/glfw.cc",
                "src/native/glad.c"
            ],
            "include_dirs": [
                "src/native/deps/include",
                "<!@(pkg-config glfw3 --cflags-only-I | sed s/-I//g)"
            ],
            "libraries": [
                "<!@(pkg-config --libs glfw3)",
            ],
            "library_dirs": [
                "/usr/local/lib"
            ]
        }
    ]
}
