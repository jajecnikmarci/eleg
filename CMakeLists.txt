cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Add your source files here
set(SOURCES
        clients.cpp
        contracts.cpp
        date.cpp
        memtrace.cpp
        MVM.cpp
        Test.cpp
        )

# Add your header files here
set(HEADERS
        clients.h
        contracts.h
        date.h
        memtrace.h
        MVM.h
        myvektor.hpp
        )

# Add your data files here
#set(DATA_FILES
#        console_forras.txt
#        En_1.txt
#        save_0.txt
#        save_1.txt
#       )

# Add any additional dependencies if required
# find_package(YourDependency)

# Create an executable
add_executable(YourProjectName ${SOURCES} ${HEADERS})

# Copy data files to the build directory
foreach(data_file ${DATA_FILES})
    configure_file(${CMAKE_SOURCE_DIR}/${data_file} ${CMAKE_BINARY_DIR}/${data_file} COPYONLY)
endforeach()
