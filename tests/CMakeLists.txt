add_executable(Test_geom test_geom.cpp)
add_executable(Test_geom_advanced test_geom_advanced.cpp)
add_executable(Demo_main1 demo_main1.cpp)
add_executable(test_1 test_1.cpp)
add_executable(test_convol_fft test_convol_fft.cpp)
add_executable(test_convol_shifted test_convol_shifted.cpp)
add_executable(test_convol test_convol.cpp)
add_executable(test_FFT_img test_FFT_img.cpp)
add_executable(test_IFFT_img test_IFFT_img.cpp)
add_executable(test_complexite test_complexite.cpp)
add_executable(test_rotation test_rotation.cpp)



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
add_test (NAME test_convol_fft
		COMMAND test_convol_fft
	 )
add_test (NAME test_convol
		COMMAND test_convol
	 )

add_test (NAME test_convol_shifted
		COMMAND test_convol_shifted
	 )
add_test (NAME test_FFT_img
		COMMAND test_FFT_img
	 )
add_test (NAME test_IFFT_img
		COMMAND test_IFFT_img
	 )
add_test (NAME test_complexite
		COMMAND test_complexite
	 )


add_test (NAME test_rotation
		COMMAND test_rotation
	 )
target_link_libraries(test_1
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

target_link_libraries(test_convol
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

target_link_libraries(test_convol_fft
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

target_link_libraries(test_convol_shifted
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

target_link_libraries(test_FFT_img
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
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
target_link_libraries(test_IFFT_img
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

target_link_libraries(test_complexite
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

target_link_libraries(test_rotation
    PUBLIC
    libFingerPrint
    ${OpenCV_LIBS}
)

