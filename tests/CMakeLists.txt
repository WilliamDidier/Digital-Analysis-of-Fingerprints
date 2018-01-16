add_executable(test_1 test_1.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${CMAKE_SOURCE_DIR}/src/headers )

find_package(OpenCV REQUIRED)

#target_link_libraries(test_1 PUBLIC libFingerPrint)
#target_link_libraries(test_1  ${OpenCV_LIBS})
message("LIBS opencv" "${OpenCV_LIBS}")
add_test (NAME test_1
		COMMAND test_1
	 )

target_link_libraries(test_1 
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)
