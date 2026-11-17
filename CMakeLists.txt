cmake_minimum_required(VERSION 3.21)
project(SeguimientoAcademico VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Test)

add_library(academico_core
    src/model/Actividad.cpp
    src/model/ActividadFactory.cpp
    src/model/RepositorioActividades.cpp
    src/model/CsvLegacySource.cpp
    src/model/CsvRepositorioAdapter.cpp
    src/controller/ActividadController.cpp
)
target_include_directories(academico_core PUBLIC src)
target_link_libraries(academico_core PUBLIC Qt6::Core)

add_executable(seguimiento_academico
    src/main.cpp
    src/view/MainWindow.cpp
)
target_link_libraries(seguimiento_academico PRIVATE academico_core Qt6::Widgets)

enable_testing()
add_executable(academico_tests tests/test_model_controller.cpp)
target_link_libraries(academico_tests PRIVATE academico_core Qt6::Test)
add_test(NAME academico_tests COMMAND academico_tests)

install(TARGETS seguimiento_academico)
