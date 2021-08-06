cmake_minimum_required(VERSION 3.15)

project(vulkan)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(vulkan-triangle
	main.c)

if(UNIX AND NOT APPLE)
	#[[
		Build for linux, basically you don't need to do anything,
		but if you ONLY BUILD glfw or vulkanSDK
		without install it into '/usr' directory, you should

			1. add extra 'target_include_directories' option
			2. modify the 'target_link_libraries' option

		based on your build directories
	]]
	target_link_libraries(vulkan-triangle
		/usr/lib/libvulkan.so
		/usr/lib/libglfw.so)
elseif(WIN32)
	#[[
		Build for windows, PLEASE USE MinGW,
		DO NOT USE visual c++ beacuse it doesn't fully support c99
		especially 'Variable Length Array' feature

		Before build, you should

			1. modify the 'target_include_directories' option
				if it's different from the path provided below.

			2. modify the 'target_link_libraries' option
				if it's different from the library file provided below.

		based on your install directories
	]]
	target_include_directories(vulkan-triangle PRIVATE
		C:/VulkanSDK/1.2.176.1/Include
		C:/glfw/include)

	target_link_libraries(vulkan-triangle
		C:/VulkanSDK/1.2.176.1/Lib/vulkan-1.lib
		C:/glfw/lib-mingw-w64/libglfw3dll.a)

	target_link_options(vulkan-triangle PRIVATE
		-mwindows)
endif()

add_custom_target(vert.spv
	COMMAND glslangValidator --quiet -V ${CMAKE_SOURCE_DIR}/shader.vert -o ${CMAKE_BINARY_DIR}/vert.spv)

add_custom_target(frag.spv
	COMMAND glslangValidator --quiet -V ${CMAKE_SOURCE_DIR}/shader.frag -o ${CMAKE_BINARY_DIR}/frag.spv)

if(UNIX AND NOT APPLE)
	add_dependencies(vulkan-triangle
		vert.spv
		frag.spv)
elseif(WIN32)
	#[[
		Windows need glfw3.dll to run this program,
		modify the path to source dll to your own path
	]]
	add_custom_target(glfw3.dll
		COMMAND ${CMAKE_COMMAND} -E copy C:/glfw/lib-mingw-w64/glfw3.dll ${CMAKE_BINARY_DIR}/)

	add_dependencies(vulkan-triangle
		vert.spv
		frag.spv
		glfw3.dll)
endif()
