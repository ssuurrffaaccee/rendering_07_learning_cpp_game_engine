
source ./build/Release/generators/conanrun.sh
PWD=$(pwd) 
FMOD_LIB_PATH="$PWD/../resources/non_open_src_depends/fmod/api/core/lib/x64"
FMOD_STUDIO_LIB_PATH="$PWD/../resources/non_open_src_depends/fmod/api/studio/lib/x64"
FBX_LIB_PATH="$PWD/../resources/non_open_src_depends/fbx_sdk_2020.2.1/mac/lib/clang/release"
export LD_LIBRARY_PATH="$FMOD_LIB_PATH:$FMOD_STUDIO_LIB_PATH:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="$FBX_LIB_PATH:$FMOD_LIB_PATH:$FMOD_STUDIO_LIB_PATH:$DYLD_LIBRARY_PATH"