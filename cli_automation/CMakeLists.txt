# CMakeList.txt: proyecto de CMake para cli_automation, incluya el origen y defina
# la lógica específica del proyecto aquí.
#

# Agregue un origen al ejecutable de este proyecto.
add_executable (
    cli_automation 
    "cli_automation.cpp" 
    "cli_automation.h" 
    "cli_api.cpp" 
    "cli_api.h" 
    "lib/utils.h" 
    "lib/io/files/files.h" 
    "lib/io/files/files.cpp"
    "lib/io/std/std.h" 
    "lib/io/std/std.cpp" 
    "lib/json/json.h" 
    "lib/string/string.h" 
    "lib/string/string.cpp" 
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cli_automation PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
target_include_directories(cli_automation PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_definitions(cli_automation PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<PLATFORM_ID:Windows>:UNICODE>
    $<$<PLATFORM_ID:Windows>:_UNICODE>
)