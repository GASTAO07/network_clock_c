# Add all the source files to a variable
set(SOURCES
    config.c
    console.c
    network_clock.c
    security.c
    server.c
    time_setup.c
    main_setime.c
)

# Add an executable target for your main program
add_executable(clock_server ${SOURCES})

# Include the "include" directory for header files
target_include_directories(clock_server PRIVATE ../include)
