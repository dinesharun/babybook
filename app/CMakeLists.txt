# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
            cGameViewLib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/utils/misc.cpp
             src/main/cpp/utils/matrix.cpp
             src/main/cpp/utils/gameCommon.cpp
             src/main/cpp/scribbleApp/scribbleApp.cpp
             src/main/cpp/rippleApp/rippleApp.cpp
             src/main/cpp/cGameView.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              openglesv2-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              GLESv2 )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       cGameViewLib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       ${openglesv2-lib} )