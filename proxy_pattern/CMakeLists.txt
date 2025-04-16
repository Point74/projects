cmake_minimum_required(VERSION 3.27)
project("Pattern Proxy" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# Указываем путь к папке с SFML
set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML)

# Указываем путь к заголовочным файлам SFML
include_directories(
        ${SFML_DIR}/include
        ${CMAKE_SOURCE_DIR}/include
)

# Указываем путь к библиотекам SFML (.a)
link_directories(${SFML_DIR}/lib)

set(SOURCES
        src/main.cpp
        src/Image.cpp
        src/ProxyImage.cpp
        src/MouseController.cpp
)

# Добавляем исполняемый файл
add_executable(PatternProxy ${SOURCES})


# Линкуем SFML библиотеки
target_link_libraries(PatternProxy
        sfml-graphics
        sfml-window
        sfml-system
)

# Путь к папке с .dll файлами
set(SFML_BIN_DIR ${SFML_DIR}/bin)

# Копируем все .dll в папку с exe после сборки
add_custom_command(TARGET PatternProxy POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SFML_BIN_DIR} $<TARGET_FILE_DIR:PatternProxy>
)
