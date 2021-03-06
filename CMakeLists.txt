cmake_minimum_required(VERSION 3.5)
project(Mario)

option (ENABLE_32_BITS "Enable 32 bits compilation" OFF)

include_directories("src" "SDL/include/" "FMOD/inc/" "libxml2/include")

if(WIN32)
	if(CMAKE_GENERATOR MATCHES "Win64")
		if(ENABLE_32_BITS)
			message( FATAL_ERROR "Win64 compiler incompatible with 32 bits option." )
		else()
			link_directories("SDL/lib/x64/" "FMOD/lib/x64" "libxml2/lib/x64")
		endif()
	else()
		link_directories("SDL/lib/Win32/" "FMOD/lib/Win32" "libxml2/lib/Win32")
		if(NOT ENABLE_32_BITS)
			message( STATUS "Win32 compiler chosen, enabling 32 bits.")
		endif()
	endif()
	add_definitions(-DWIN32_LEAN_AND_MEAN)
else()
    link_directories("FMOD/lib/")
endif ()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set(CPP11_FLAG "/EHsc")
else()
	include(CheckCXXCompilerFlag)
	check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
	check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
	check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX14)
		set(CPP11_FLAG "-std=c++14")
	elseif(COMPILER_SUPPORTS_CXX11)
		set(CPP11_FLAG "-std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
		set(CPP11_FLAG "-std=c++0x")
	else()
		MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. This can result in build failure.")
	endif()
endif()

add_subdirectory(src)

