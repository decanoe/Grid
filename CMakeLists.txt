cmake_minimum_required(VERSION 3.0.0)
project(Grid VERSION 0.1.0)

# include(CTest)
# enable_testing()


# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)


set(SRCS
    main.cpp
    Functions/Compute.cpp
    Functions/InputOutput.cpp
    Class/Grid.cpp
    Class/PartialSolution.cpp
    )
    
    set(HEADERS
    Functions/Compute.h
    Functions/InputOutput.h
    Class/Grid.h
    Class/PartialSolution.h
    )
    
add_executable(Grid ${SRCS} ${HEADERS})
add_compile_options(-Wall)