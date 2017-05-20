
file(GLOB SRC_FILES
	"*.cpp"
	"*.h"
)
	
file(GLOB SRC_ENTITIES
	"entities/*.cpp"
	"entities/*.h"
)

file(GLOB SRC_ENTITIES_HANDPATERN
	"entities/handPatern/*.cpp"
	"entities/handPatern/*.h"
)

file(GLOB SRC_GRAPHICS
	"graphics/*.cpp"
	"graphics/*.h"
)

file(GLOB SRC_GRAPHICS_RENDERER
	"graphics/renderers/*.cpp"
	"graphics/renderers/*.h"
)

file(GLOB SRC_PHYSICS
	"physics/*.cpp"
	"physics/*.h"
)

file(GLOB SRC_UI
	"ui/*.cpp"
	"ui/*.h"
)

add_executable(Mario ${SRC_FILES}
					${SRC_ENTITIES}
					${SRC_ENTITIES_HANDPATERN}
					${SRC_GRAPHICS}
					${SRC_GRAPHICS_RENDERER}
					${SRC_PHYSICS}
					${SRC_UI}
)

source_group(Common					FILES ${SRC_FILES})
source_group(Entities				FILES ${SRC_ENTITIES})
source_group(Entities\\HandPatern	FILES ${SRC_ENTITIES_HANDPATERN})
source_group(Graphics				FILES ${SRC_GRAPHICS})
source_group(Graphics\\Renderers	FILES ${SRC_GRAPHICS_RENDERER})
source_group(Physics				FILES ${SRC_PHYSICS})
source_group(UI						FILES ${SRC_UI})

target_link_libraries(Mario "SDL2" "SDL2main" "SDL2_ttf" "SDL2_image" "libxml2" "fmodL")

set_target_properties(Mario
    PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY_RELEASE 			"${CMAKE_SOURCE_DIR}/Binary"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO 	"${CMAKE_SOURCE_DIR}/Binary"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG 				"${CMAKE_SOURCE_DIR}/Binary"
)
