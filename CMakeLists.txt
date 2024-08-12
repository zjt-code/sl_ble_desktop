cmake_minimum_required(VERSION 3.5)
set(Qt5_DIR "D:/Qt/Qt5.12.9/5.12.9/msvc2017/lib/cmake/Qt5")


project(sl_ble_desktop LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt5 COMPONENTS Charts )

# Configure common source files
set(
    SRC_SIMPLEBLE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/Adapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/Peripheral.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/Exceptions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/AdapterBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/PeripheralBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/AdapterSafe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/PeripheralSafe.cpp
)

set(
    SRC_SIMPLEBLE_C_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src_c/simpleble.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src_c/adapter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src_c/peripheral.cpp
)


set(
          SRC_SIMPLEBLE_FILES
          ${SRC_SIMPLEBLE_FILES}
          ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/windows/AdapterBase.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/windows/PeripheralBase.cpp
          ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/windows/Utils.cpp
      )

  set(EXTRA_INCLUDES
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/include
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/simpleble
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/backends/common
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/backends/windows
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/external
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src/builders
                      ${CMAKE_CURRENT_SOURCE_DIR}/simpleble/src)

# set(TS_FILES sl_ble_desktop_zh_CN.ts)

if(ANDROID)
  add_library(sl_ble_desktop SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    # ${TS_FILES}
  )
else()
  add_executable(sl_ble_desktop
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    connectthread.cpp
    connectthread.h
    # ${TS_FILES}
    ${SRC_SIMPLEBLE_FILES}
  )
endif()

target_link_libraries(sl_ble_desktop PRIVATE Qt5::Widgets Qt5::Charts)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})


include_directories(simpleble/include/)
include_directories(simpleble/src/simpleble)
include_directories(simpleble/src/backends/common)
include_directories(simpleble/src/backends/windows)
include_directories(simpleble/src/external)
include_directories(simpleble/src/builders)
include_directories(simpleble/src/windows)
include_directories(simpleble/src)

