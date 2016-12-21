# Android Studio + OpenCV3 + NDK
Template for OpenCV 3 project

## To Setup from Scratch

### Step 1 : OpenCV 3
- Download [OpenCV 3.1 for Android](http://opencv.org/downloads.html)
- Extract the package, for example `C:\OpenCV-android-sdk`

### Step 2 : Android Studio 2.2
- Download and Install [Android Studio](https://developer.android.com/studio/index.html)
- Make sure you have NDK and CMake installed
  - File > Settings > Appearance & Behavior > System Settings > Android SDK, Under SDK Tools tab to find CMake and NDK

### Step 3 : Create New Project
- Create new project, be sure to check "Include C++ support"
   - The rest of options are up to you.

### Step 4 : Import OpenCV moudle
- File > New > Import Module
  - Source directory set to `C:\OpenCV-android-sdk\sdk\java`
- File > Project Structure
  - Modules > app, Dependencies Tab,
  - Click the green add button, add 3. Module Dependencies
  - Select openCVLibrary310

### Step 5 : Setup OpenCV Gradle Scripts
- Go to project explorer and find `Gradle Scripts` section
  - Find build.gradle (Moudle openCVLibrary310) and modify it like below

```
compileSdkVersion 25
buildToolsVersion "25.0.0"

defaultConfig {
  minSdkVersion 23
  targetSdkVersion 25
}
```
### Step 6 : Copy OpenCV libs
- File > New > Folder > JNI Folder
  - check `Change Folder Location`
  - set new folder location to `src/main/jniLibs`
- Go to `C:\OpenCV-android-sdk\sdk\native\libs`
  - press Ctral + A to select all and press Ctrl + C to copy
  - back to Android Studio select `app` in the project explorer and press Ctrl + V
  - Choose `...\app\src\main\jniLibs` as your destination directory

### Step 7 : Copy OpenCV Include
- Go to `C:\OpenCV-android-sdk\sdk\native\jni\`
  - select `include` folder and press Ctral + C to Copy
  - back to Android Studio select `cpp` section under `app` and press Ctrl + V

### Step 8 : Setup CMake
- Go to project explorer and find `External Build Files` section
  - Open CMakeLists.txt and modify it like below

```
cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)
set(libs "${CMAKE_SOURCE_DIR}/src/main/jniLibs")
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/include)

# OpenCV Libs
add_library(libopencv_java3 SHARED IMPORTED )
set_target_properties(libopencv_java3 PROPERTIES
    IMPORTED_LOCATION "${libs}/${ANDROID_ABI}/libopencv_java3.so")

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries( # Specifies the target library.
                       native-lib
                       libopencv_java3
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )
```

## FAQ
__Q. If you deploy this template onto your phone and see nothing display on screen ?__  
A. Go to your phone's Settings > Apps > 'Name of your app' > Permissions and toggle Camera
