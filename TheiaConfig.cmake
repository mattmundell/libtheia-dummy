add_library(libtheia INTERFACE)
add_library(Theia::Theia ALIAS libtheia)

#message (STATUS "theia: curr src dir: ${CMAKE_CURRENT_SOURCE_DIR}/")
#message (STATUS "theia: curr list dir: ${CMAKE_CURRENT_LIST_DIR}/")

set_target_properties(libtheia PROPERTIES 
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/"
    INTERFACE_LINK_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/libtheia.o")
