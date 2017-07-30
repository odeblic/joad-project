add_definitions(-std=c99)

add_executable(stealth_example stealth_example.c)
add_executable(zombie_factory_example zombie_factory.c zombie_factory_example.c)

target_link_libraries(zombie_factory_example pthread)
