
cmake_minimum_required (VERSION 3.5)

project (MainTest)

add_definitions("-fpermissive")
add_definitions("-std=c++11")

set(Files
    ${PROJECT_SOURCE_DIR}/MainTest.cpp
)

if (CMAKE_HOST_WIN32)
    find_package(MechEyeApi REQUIRED CONFIG PATHS "$ENV{MECHEYE_DIR}/API")

    include_directories(${MECHEYEAPI_INCLUDE_DIRS} ./include)

    link_directories(${MECHEYEAPI_LIBRARY_DIRS})

    add_executable (${PROJECT_NAME}  ${Files})
    target_link_libraries(${PROJECT_NAME} ${MECHEYEAPI_LIBRARIES})

elseif (CMAKE_HOST_UNIX)
    include(FindPkgConfig)
    pkg_check_modules(PKGS REQUIRED MechEyeApi)
    include_directories(${PKGS_INCLUDE_DIRS} ./include)
    link_directories(${PKGS_LIBRARY_DIRS})

    add_executable (${PROJECT_NAME}  ${Files})
    target_link_libraries(${PROJECT_NAME} MechEyeApi)
endif ()
