# cmake-experiment

Other config you need to append (They should be global).

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

## Dependencies

CMake will run the command for you. You just need to install vcpkg and add the config above.

```powershell
vcpkg --feature-flags="versions" install
```
