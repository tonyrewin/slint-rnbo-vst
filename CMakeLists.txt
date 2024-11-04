cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME "effect_vst")
project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0)

add_compile_definitions(RELEASE=1)

set(VST3_SDK_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/vst3sdk")

# Добавляем AudioUnit SDK
include(FetchContent)
FetchContent_Declare(
    AudioUnitSDK
    GIT_REPOSITORY https://github.com/apple/AudioUnitSDK.git
    GIT_TAG HEAD
)
FetchContent_MakeAvailable(AudioUnitSDK)
FetchContent_GetProperties(
    AudioUnitSDK
    SOURCE_DIR SMTG_AUDIOUNIT_SDK_PATH
)

# Отключаем ненужные компоненты
set(SMTG_ADD_VST3_HOSTING_SAMPLES OFF CACHE BOOL "Don't build hosting samples")
set(SMTG_ADD_VST3_PLUGINS_SAMPLES OFF CACHE BOOL "Don't build plug-in examples")
set(SMTG_ENABLE_VST3_HOSTING_EXAMPLES OFF CACHE BOOL "Don't build hosting examples")
set(SMTG_ENABLE_VST3_PLUGIN_EXAMPLES OFF CACHE BOOL "Don't build plug-in examples")
set(SMTG_RUN_VST_VALIDATOR OFF CACHE BOOL "Don't run validator")

# Включаем AU
set(SMTG_ENABLE_AUV2_BUILDS ON CACHE BOOL "Enable AUv2 wrapper")

# Отключаем дополнительные компоненты
set(SMTG_ENABLE_VSTGUI_SUPPORT OFF CACHE BOOL "No VSTGUI support")
set(SMTG_CREATE_PLUGIN_LINK ON CACHE BOOL "Create symlink for the plug-in")
# Включаем VST3 SDK
add_subdirectory(${VST3_SDK_ROOT} EXCLUDE_FROM_ALL)
smtg_enable_vst3_sdk()
# Создаем VST3 плагин
smtg_add_vst3plugin(${PROJECT_NAME}
    src/main.cpp
    src/processor.cpp
    src/controller.cpp
)

# Находим Slint
find_package(Slint QUIET)
if (NOT Slint_FOUND)
    message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
    include(FetchContent)
    FetchContent_Declare(
        Slint
        GIT_REPOSITORY https://github.com/slint-ui/slint.git
        GIT_TAG release/1
        SOURCE_SUBDIR api/cpp
    )
    FetchContent_MakeAvailable(Slint)
endif()
target_link_libraries(effect_vst
    PRIVATE
        sdk
        base
        pluginterfaces
        Slint::Slint
)

# Добавляем AU wrapper
if (SMTG_MAC AND XCODE AND SMTG_ENABLE_AUV2_BUILDS)
    list(APPEND CMAKE_MODULE_PATH "${VST3_SDK_ROOT}/cmake/modules")
    include(SMTG_AddVST3AuV2)
    smtg_target_add_auv2(${PROJECT_NAME}_au
        BUNDLE_NAME "Effect VST"
        BUNDLE_IDENTIFIER com.yourcompany.effectvst.audiounit
        INFO_PLIST_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/resource/au-info.plist
        VST3_PLUGIN_TARGET ${PROJECT_NAME})
endif()
