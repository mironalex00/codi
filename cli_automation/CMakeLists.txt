# CMakeList.txt: proyecto de CMake para cli_automation, incluya el origen y defina
# la lógica específica del proyecto aquí.
#

# Agregue un origen al ejecutable de este proyecto.
add_executable (cli_automation "cli_automation.cpp" "cli_automation.h" "cli_api.cpp"   "cli_api.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cli_automation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
target_compile_definitions(cli_automation PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<PLATFORM_ID:Windows>:UNICODE>
    $<$<PLATFORM_ID:Windows>:_UNICODE>
)