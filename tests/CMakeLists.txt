add_executable(Test_geom test_geom.cpp)
add_executable(Test_geom_advanced test_geom_advanced.cpp)
add_executable(Demo_main1 demo_main1.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories( ${CMAKE_SOURCE_DIR}/src/headers )

find_package(OpenCV REQUIRED)


message("LIBS opencv" "${OpenCV_LIBS}")
add_test (NAME Test_geom
		COMMAND Test_geom
	 )
add_test (NAME Test_geom_advanced
		COMMAND Test_geom_advanced
	 )
add_test (NAME Demo_main1
		COMMAND Demo_main1
	 )

target_link_libraries(Test_geom 
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)
target_link_libraries(Test_geom_advanced 
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)
target_link_libraries(Demo_main1
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)
