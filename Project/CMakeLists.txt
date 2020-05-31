cmake_minimum_required(VERSION 3.15)
project(TourMateApp)

set(CMAKE_CXX_STANDARD 14)

IF (WIN32)
	link_libraries(ws2_32 wsock32)
ELSE()
	# set stuff for other systems
ENDIF()

include_directories(src
                    maps
		    		lib)

add_executable(TourMateApp
        src/Graph.cpp
        src/Graph.h
		src/helperfunctions.cpp
		src/helperfunctions.h
		src/main.cpp
        src/Menu.cpp
        src/Menu.h
		src/MutablePriorityQueue.h
        src/POITypes.h
        src/States.h
		lib/connection.cpp
		lib/graphviewer.cpp src/Menu.h)
