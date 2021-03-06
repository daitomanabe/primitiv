# test definitions

if(PRIMITIV_GTEST_SOURCE_DIR)
  include(ExternalProject)
  ExternalProject_Add(
    GTest
    SOURCE_DIR ${PRIMITIV_GTEST_SOURCE_DIR}
    INSTALL_COMMAND ""
  )
  ExternalProject_Get_Property(GTest binary_dir)
  add_library(gtest STATIC IMPORTED)
  set_property(
    TARGET gtest
    PROPERTY IMPORTED_LOCATION ${binary_dir}/libgtest.a
  )
  add_library(gtest_main STATIC IMPORTED)
  set_property(
    TARGET gtest_main
    PROPERTY IMPORTED_LOCATION ${binary_dir}/libgtest_main.a
  )
  set(GTEST_BOTH_LIBRARIES gtest gtest_main)
else()
  find_package(GTest REQUIRED)
endif()

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GTEST_INCLUDE_DIRS}
)

add_library(test_utils_OBJS OBJECT test_utils.h test_utils.cc)

function(primitiv_test name)
  add_executable(${name}_test
    test_utils.h ${name}_test.cc $<TARGET_OBJECTS:test_utils_OBJS>)
  if(PRIMITIV_GTEST_SOURCE_DIR)
    add_dependencies(${name}_test GTest)
  endif()
  target_link_libraries(${name}_test primitiv ${GTEST_BOTH_LIBRARIES} pthread)
  add_test(
    NAME ${name}_test
    COMMAND ${name}_test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endfunction()

primitiv_test(device)
primitiv_test(graph)
primitiv_test(initializer_impl)
primitiv_test(mixins)
primitiv_test(model)
primitiv_test(msgpack_objects)
primitiv_test(msgpack_reader)
primitiv_test(msgpack_writer)
primitiv_test(naive_device)
primitiv_test(node)
primitiv_test(numeric_utils)
primitiv_test(operator_impl)
primitiv_test(optimizer)
primitiv_test(optimizer_impl)
primitiv_test(parameter)
primitiv_test(random)
primitiv_test(shape)
primitiv_test(shape_ops)
primitiv_test(string_utils)
primitiv_test(tensor)
primitiv_test(tensor_backward)
primitiv_test(tensor_forward)

if(PRIMITIV_USE_EIGEN)
  primitiv_test(eigen_device)
endif()

if(PRIMITIV_USE_CUDA)
  primitiv_test(cuda_device)
  primitiv_test(cuda_memory_pool)
endif()

if(PRIMITIV_USE_OPENCL)
  primitiv_test(opencl_device)
endif()

if(PRIMITIV_BUILD_C_API)
  function(primitiv_c_test name)
    add_executable(c_${name}_test
        test_utils.h c/${name}_test.cc $<TARGET_OBJECTS:test_utils_OBJS>)
    if(PRIMITIV_GTEST_SOURCE_DIR)
      add_dependencies(c_${name}_test GTest)
    endif()
    target_link_libraries(c_${name}_test primitiv_c
        ${GTEST_BOTH_LIBRARIES} pthread)
    add_test(
        NAME c_${name}_test
        COMMAND c_${name}_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
  endfunction()

  primitiv_c_test(shape)
endif()
