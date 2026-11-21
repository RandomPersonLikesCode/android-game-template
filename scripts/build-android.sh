#!/bin/env sh

set -eu

# Variables
sdk_path="$ANDROID_HOME/platforms/android-$TARGET_SDK/android.jar"
android_path="app/android"
lib_name="libmain.so"

set -x

# Create necessary directories
rm -rf build/bin
mkdir -p build/bin build/res

# Setup CMaks
cmake -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_ROOT/build/cmake/android.toolchain.cmake \
  -DANDROID_ABI=$ARCH \
  -DANDROID_PLATFORM=android-$MIN_SDK \
  -B build \
  -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# Build the native library
cmake --build build/ -j$CORES

# Build the dex only once
if [ "$FIRST_BUILD" = "1" ]; then
  find app/android/src/java -name "*.java" > build/java_src.txt
  cp build/_deps/sdl3-build/SDL3-3.4.18.jar SDL3.jar

  javac --release 17 -cp $sdk_path:SDL3.jar -d build/obj \
      @build/java_src.txt
  d8 --min-api $MIN_SDK --lib $sdk_path \
    --output build/obj `find build/obj -name "*.class"` SDL3.jar

  rm SDL3.jar
fi

# Copy the native library
rm -rf build/lib
mkdir -p build/lib/$ARCH
cp build/app/src/$lib_name build/lib/$ARCH

# Setup and compile the resources
aapt2 compile -o build/res --dir $android_path/res
aapt2 link -I $sdk_path \
    --manifest $android_path/AndroidManifest.xml \
    -o build/bin/app-unsigned.apk \
    build/res/*.flat

# Zip the necessary files/folders
ln -s ./build/lib ./lib
ln -s ./build/obj/classes.dex ./classes.dex
ln -s ./app/assets/ ./assets
zip -0 -qur build/bin/app-unsigned.apk lib
zip -0 -qur build/bin/app-unsigned.apk classes.dex
zip -0 -qur build/bin/app-unsigned.apk assets
rm ./assets
rm ./classes.dex
rm ./lib

# Align the APK
zipalign 4 build/bin/app-unsigned.apk build/bin/app-aligned.apk
