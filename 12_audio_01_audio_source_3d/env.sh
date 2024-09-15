
source ./build/Release/generators/conanrun.sh
PWD=$(pwd) 
FMOD_LIB_PATH="$PWD/../resources/non_open_src_depends/fmod/api/core/lib/x64"
FMOD_STUDIO_LIB_PATH="$PWD/../resources/non_open_src_depends/fmod/api/studio/lib/x64"
export LD_LIBRARY_PATH="$FMOD_LIB_PATH:$FMOD_STUDIO_LIB_PATH:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="$FMOD_LIB_PATH:$FMOD_STUDIO_LIB_PATH:$DYLD_LIBRARY_PATH"