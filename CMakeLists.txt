cmake_minimum_required(VERSION 3.10)

project(Deshroud)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_C_STANDARD 20)
# set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB deshroudSrc
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ds/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ds/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/ds/*.rc"
)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${deshroudSrc})
add_definitions(-DUNICODE)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE Msimg32)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)