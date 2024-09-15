export CONAN_EXE=conan
export BUILD_TYPE=Release
$CONAN_EXE profile detect --force 
$CONAN_EXE install ./mac_conanfile.py --build=missing  --settings:all=compiler.cppstd=17 --settings:all=build_type=${BUILD_TYPE}  --options=rttr/0.9.6:shared=True --options=rttr/0.9.6:with_rtti=True
cmake --preset conan-$(echo ${BUILD_TYPE} | tr A-Z a-z)
cd build/${BUILD_TYPE}
cmake ../..  -DCMAKE_TOOLCHAIN_FILE=$(pwd)/generators/conan_toolchain.cmake  -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
cmake --build .
rm -rf ../../bin
cmake --install .
cd ../..
cp -r ./src/Example/lua ./bin
cp -r ./src/Lua ./bin