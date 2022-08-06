set(BENCHMARK_SOURCES
  src/benchmark.cc
)

add_executable(benchmark ${BENCHMARK_SOURCES})
target_link_libraries(benchmark throttle)
if(Boost_FOUND)
  target_link_libraries(benchmark Boost::program_options)
endif()

install(TARGETS benchmark DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(BASH_PROGRAM)
  add_test(NAME test.benchmark COMMAND ${BASH_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/test.sh "$<TARGET_FILE:benchmark>" ${CMAKE_CURRENT_SOURCE_DIR})
endif()