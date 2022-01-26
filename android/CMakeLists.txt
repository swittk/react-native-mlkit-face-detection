cmake_minimum_required(VERSION 3.4.1)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)

set (PACKAGE_NAME "SKRNMLKitFaceDetection")
set (RN_SO_DIR ${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/jni/first-party/react/jni)
set (FBJNI_HEADERS_DIR ${RN_SO_DIR}/../../fbjni/headers)

if(${REACT_NATIVE_VERSION} LESS 66)
set (
    INCLUDE_JSI_CPP
    "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/jsi.cpp"
)
#  set (
#          INCLUDE_JSIDYNAMIC_CPP
#          "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi/jsi/JSIDynamic.cpp"
#  )
endif()


# if(${HAS_RN_NATIVE_VIDEO})
# message(STATUS "CMAKE : RN MLKit Face Detection :: Linking with RN Native Video")
# # set (
# #     IMPORT_NATIVE_VIDEO_COMMON_CPP
# #     "${NODE_MODULES_DIR}/react-native-native-video/cpp/react-native-native-video.cpp"
# # )
# # set(
# #     IMPORT_NATIVE_VIDEO_ANDROID_CPP
# #     "${NODE_MODULES_DIR}/react-native-native-video/android/SKAndroidNativeVideoCPP.cpp"
# # )

# # finds the library with the name specified in the second parameter, and assigns the path to the name specified in the first parameter
# find_package(
#     reactnativenativevideo
# )
# target_link_libraries( 
#     ${PACKAGE_NAME}
#     reactnativenativevideo
# )
# endif()

add_library(${PACKAGE_NAME}
            SHARED
            ${INCLUDE_JSI_CPP}
            ${INCLUDE_JSIDYNAMIC_CPP}
            ../cpp/react-native-mlkit-face-detection.cpp
            cpp-adapter.cpp
            SKRNMLKitAndroidFaceDetectionCPP.cpp
            ${IMPORT_NATIVE_VIDEO_COMMON_CPP}
            ${IMPORT_NATIVE_VIDEO_ANDROID_CPP}
)

# Specifies a path to native header files.
include_directories(
            ../cpp
            .
            "${FBJNI_HEADERS_DIR}"
            "${NODE_MODULES_DIR}/react-native/React"
            "${NODE_MODULES_DIR}/react-native/React/Base"
            "${NODE_MODULES_DIR}/react-native/ReactCommon"
            "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
            "${NODE_MODULES_DIR}/react-native/ReactCommon/callinvoker"
            "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/java/com/facebook/react/turbomodule/core/jni/ReactCommon"
            # ../node_modules/react-native/ReactAndroid/src/main/jni/react/jni/JavaScriptExecutorHolder.h
            # ../node_modules/react-native/ReactAndroid/src/main/jni/react/jni
            "${NODE_MODULES_DIR}/react-native/ReactAndroid/src/main/jni/react"
            "${NODE_MODULES_DIR}/react-native/ReactCommon/turbomodule/core"
            "${NODE_MODULES_DIR}/react-native/ReactCommon/turbomodule"
            "${NODE_MODULES_DIR}/react-native/React"
            "${NODE_MODULES_DIR}/react-native/React/Base"
            "${NODE_MODULES_DIR}/react-native/ReactCommon/jsi"
            "${NODE_MODULES_DIR}/react-native-native-video/cpp"
            "${NODE_MODULES_DIR}/react-native-native-video/android"
)

if(${HAS_RN_NATIVE_VIDEO})
message(WARNING "CMAKE : RN MLKit Face Detection :: Linking with RN Native Video")
# set(reactnativenativevideo_DIR
# "${NODE_MODULES_DIR}/react-native-native-video/android"
# )
set (BUILD_DIR ${CMAKE_SOURCE_DIR}/build)
find_package(
    RN_NATIVE_VIDEO_LIB
    reactnativenativevideo
    PATHS "${NODE_MODULES_DIR}/react-native-native-video/android"
    NO_CMAKE_FIND_ROOT_PATH
)
message(WARNING "RN MLKit Face Detection :: ${RN_NATIVE_VIDEO_LIB} linked")


target_link_libraries( 
    ${PACKAGE_NAME}
    ${RN_NATIVE_VIDEO_LIB}
)
endif()