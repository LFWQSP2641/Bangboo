cmake_minimum_required(VERSION 3.16)

# 设置项目名称和版本
project(Bangboo VERSION 0.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt Core
find_package(Qt6 REQUIRED COMPONENTS Core)

# Qt Quick
find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

# 设置源文件和头文件
set(SOURCES
    BangbooTranslater.cpp
    QMLUtils.cpp
    main.cpp
)

set(HEADERS
    BangbooTranslater.h
    QMLUtils.h
)

set(RESOURCES
    Bangboo.qrc
)

set(ANDROID_SOURCES
    android/AndroidManifest.xml
    android/build.gradle
    android/res/values/libs.xml
    android/res/xml/qtprovider_paths.xml
    android/gradle/wrapper/gradle-wrapper.jar
    android/gradle/wrapper/gradle-wrapper.properties
    android/gradle.properties
    android/gradlew
    android/gradlew.bat
)

# 添加资源文件
qt_add_resources(RESOURCES_ADDED ${RESOURCES})

# 添加可执行文件
qt_add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES_ADDED} ${ANDROID_SOURCES})

# 链接 Qt 库
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick)


# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
# 设置安装目录
if(!ANDROID)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
    )
endif()

# Android相关设置
if(ANDROID)
    set(ANDROID_VERSION_NAME "0.5")
    set(ANDROID_VERSION_CODE 5)

    # 添加Android资源文件
    set(QT_ANDROID_PACKAGE_SOURCE_DIR android)
endif()
