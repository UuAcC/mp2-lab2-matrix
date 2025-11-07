set(target "VM_includes")

file(GLOB hdrs "*.h*" "${MP2_INCLUDE}/*.h*")

add_library(${target} STATIC ${srcs} ${hdrs})
set_target_properties(${target} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${target} ${LIBRARY_DEPS})