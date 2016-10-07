cmake_minimum_required(VERSION 3.5)
project(Mario)

option (ENABLE_32_BITS "Enable 32 bits compilation" OFF)

include_directories("SDL/include/" "FMOD/inc/" "libxml2/include")

if(WIN32)
	if(CMAKE_GENERATOR MATCHES "Win64")
		if(ENABLE_32_BITS)
			message( FATAL_ERROR "Win64 compiler incompatible with 32 bits option." )
		else()
			link_directories("SDL/lib/x64/" "FMOD/lib/" "libxml2/lib/x64")
		endif()
	else()
		link_directories("SDL/lib/Win32/" "FMOD/lib/" "libxml2/lib/Win32")
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

set(HEADER_FILES
	common.h
	editor.h
	filetool.h
	gfxInterface.h
	input.h
	level.h
	mario.h
	math.h
	menu.h
	path.h
	rectangle.h
	sound.h
	stringUtility.h
	timer.h
	vector.h
	worldEntities.h
	XMLWriter.h
	entities/block.h
	entities/ECS.h
	entities/enemy.h
	entities/entitiesHandler.h
	entities/entitiesHeader.h
	entities/entityTypes.h
	entities/item.h
	entities/object.h
	entities/player.h
	entities/projectile.h
	entities/trigger.h
	entities/handPatern/hand.h
	entities/handPatern/handPattern.h
	graphics/animation.h
	graphics/background.h
	graphics/color.h
	graphics/gfxParameters.h
	graphics/graphics.h
	graphics/renderDatas.h
	graphics/surface.h
	graphics/texture.h
	graphics/textureSet.h
	graphics/viewport.h
	graphics/writing.h
	graphics/renderers/renderCoin.h
	graphics/renderers/renderDialog.h
	graphics/renderers/renderEditor.h
	graphics/renderers/renderEntity.h
	physics/collisionHandler.h
	physics/physics.h
	physics/phyStack.h
	physics/sweepAndPrune.h
	ui/button.h
	ui/dialog.h)

set(SOURCE_FILES
	editor.cpp
	filetool.cpp
	gfxInterface.cpp
	input.cpp
	level.cpp
	mario.cpp
	math.cpp
	menu.cpp
	path.cpp
	rectangle.cpp
	sound.cpp
	stringUtility.cpp
	timer.cpp
	vector.cpp
	worldEntities.cpp
	XMLWriter.cpp
	entities/block.cpp
	entities/ECS.cpp
	entities/enemy.cpp
	entities/entitiesHandler.cpp
	entities/entityTypes.cpp
	entities/item.cpp
	entities/object.cpp
	entities/player.cpp
	entities/projectile.cpp
	entities/trigger.cpp
	entities/handPatern/hand.cpp
	entities/handPatern/handPattern.cpp
	graphics/animation.cpp
	graphics/background.cpp
	graphics/color.cpp
	graphics/gfxParameters.cpp
	graphics/graphics.cpp
	graphics/surface.cpp
	graphics/texture.cpp
	graphics/textureSet.cpp
	graphics/viewport.cpp
	graphics/writing.cpp
	graphics/renderers/renderCoin.cpp
	graphics/renderers/renderDialog.cpp
	graphics/renderers/renderEditor.cpp
	graphics/renderers/renderEntity.cpp
	physics/collisionHandler.cpp
	physics/physics.cpp
	physics/phyStack.cpp
	physics/sweepAndPrune.cpp
	ui/button.cpp
	ui/dialog.cpp)

add_executable(Mario ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(Mario "SDL2" "SDL2main" "SDL2_ttf" "SDL2_image" "libxml2")

if(WIN32)
	if(ENABLE_32_BITS)
		target_link_libraries(Mario "fmodL_vc")
	else()
		target_link_libraries(Mario "fmodL64_vc")
	endif()
elseif (APPLE)
else()
	target_link_libraries(Mario "fmodL")
endif ()

