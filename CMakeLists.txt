cmake_minimum_required (VERSION 2.6)
project (smartptr_cast_study)

try_compile(AT_LEAST_GCC_4_4 ${smartptr_cast_study_BINARY_DIR} ${smartptr_cast_study_SOURCE_DIR}/gcc_4_4_test.cpp)

include_directories (${smart_ptr_cast_SOURCE_DIR} ${smart_ptr_cast_BINARY_DIR})

if (AT_LEAST_GCC_4_4)
	set_source_files_properties ( 
		unique_ptr_cast.cpp PROPERTIES COMPILE_FLAGS "-std=gnu++0x"
	)
	add_executable (unique_ptr_cast unique_ptr_cast.cpp)
else (AT_LEAST_GCC_4_4)
	message(STATUS, "Need at least GCC 4.4 to build unique_ptr_cast.cpp")
endif (AT_LEAST_GCC_4_4)

find_package (Boost 1.34)
if (Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(boost_unique_ptr_cast boost_unique_ptr_cast.cpp)
else (Boost_FOUND)
	message(STATUS, "Need boost library available to build boost_unique_ptr_cast.cpp")	
endif (Boost_FOUND)

add_executable (auto_ptr_cast auto_ptr_cast.cpp)
add_executable (shared_ptr_cast shared_ptr_cast.cpp)
