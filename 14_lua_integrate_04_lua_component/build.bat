set CONAN_EXE=conan.exe

set BUILD_TYPE=Release

%CONAN_EXE% profile detect --force 

%CONAN_EXE% install ./win32_conanfile.txt --build=missing  --settings:all=compiler.cppstd=17 --settings:all=build_type=%BUILD_TYPE% --options=rttr/0.9.6:with_rtti=True --options=rttr/0.9.6:shared=True 
cmake --preset conan-default
cd build/
cmake --build . --config %BUILD_TYPE% -j 8
cmake --install .
cd ..
xcopy  .\src\Example\lua .\bin\lua /E /I /Y
xcopy  .\src\Lua\ .\bin\lua /E /I /Y