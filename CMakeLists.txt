cmake_minimum_required(VERSION 3.19)
project(gomoku)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 REQUIRED COMPONENTS audio graphics window system)

include_directories(
${PROJECT_SOURCE_DIR}/includes
)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

add_executable(gomoku
sources/main.cpp
sources/utils.cpp
sources/gomoku.cpp
sources/rules.cpp
sources/defaultRules.cpp
sources/proRules.cpp
sources/longProRules.cpp
sources/swapRules.cpp
sources/swapTwoRules.cpp
sources/player.cpp
sources/randomPlayer.cpp
sources/humanPlayer.cpp
sources/assistedHumanPlayer.cpp
sources/noobIA.cpp
sources/interface.cpp
sources/boardIterator.cpp
sources/minMaxDynamicPlayer.cpp
sources/heuristicBoard.cpp
sources/menu.cpp
)

target_link_libraries(gomoku PRIVATE sfml-audio sfml-graphics sfml-window sfml-system Threads::Threads)
