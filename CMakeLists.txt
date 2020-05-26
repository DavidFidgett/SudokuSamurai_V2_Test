cmake_minimum_required(VERSION 3.13)
project(SudokuSamurai_V2_0 C)

set(CMAKE_C_STANDARD 99)

add_executable(SudokuSamurai_V2_0 main.c)

INCLUDE_DIRECTORIES(C:/Users/david/allegro-mingw-4.2.3/include)
LINK_DIRECTORIES( C:/Users/david/allegro-mingw-4.2.3/lib )

TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/libaldat.a")
TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/liballd.a")
TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/liballd_s.a")
TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/liballeg.a")
TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/liballeg_s.a")
TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/liballp.a")
TARGET_LINK_LIBRARIES(SudokuSamurai_V2_0 "C:/Users/david/allegro-mingw-4.2.3/lib/liballp_s.a")