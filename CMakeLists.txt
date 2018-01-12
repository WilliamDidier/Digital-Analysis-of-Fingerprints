cmake_minimum_required(VERSION 2.6)

                

#Configuration du projet

project(Digital_analysis)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

#Génération de la liste des fichiers sources

file(

        GLOB_RECURSE

        source_files

        sources/*

)

file(

        GLOB_RECURSE

        source_files_tests

        tests/*

)


#Déclaration de l'exécutable

add_executable(

        Digital_analysis

        ${source_files}

)

add_executable(

        Test_1

        ${source_files_tests}

)


target_link_libraries( Digital_analysis ${OpenCV_LIBS} )
target_link_libraries( Test_1 ${OpenCV_LIBS} )
