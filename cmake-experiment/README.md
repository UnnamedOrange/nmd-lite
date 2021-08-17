# cmake-experiment

Other config you need to append.

```json
    "cmake.configureEnvironment": 
    {
        "VCPKG_ROOT": "C:/Program Files/vcpkg", // Substitute your path.
    },
    "cmake.configureSettings": 
    {
        "CMAKE_TOOLCHAIN_FILE": "${env:VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake",
    },
```

