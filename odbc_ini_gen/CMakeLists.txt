get_filename_component(EXEC_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME)

#######
# CLI #
#######

set(Cli_Header_Files "odbc_ini_gen_stdbool.h")
set(Cli_Source_Files "main.c")
source_group("${EXEC_NAME} Source Files" FILES "${Source_Files}")

add_executable("${EXEC_NAME}" "${Cli_Source_Files}")

include(GNUInstallDirs)
target_include_directories(
        "${EXEC_NAME}"
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        # "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_target_properties("${EXEC_NAME}" PROPERTIES LINKER_LANGUAGE C)

#################
# Install rules #
#################

include(GNUInstallDirs)

install(TARGETS "${EXEC_NAME}"
        DESTINATION "${CMAKE_INSTALL_BINDIR}")

install(FILES ${Cli_Header_Files}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
