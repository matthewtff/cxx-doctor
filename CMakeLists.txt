cmake_minimum_required ( VERSION 2.6 )
project (doctor)

subdirs (
	external/koohar
	external/oodb
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

	SET (warnings "-Wall -Wextra -Woverloaded-virtual")

	SET (common_flags "-std=c++0x -stdlib=libc++ -fPIC")

	SET (CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} ${warnings} ${common_flags}"
	)

	SET (CMAKE_CXX_FLAGS_DEBUG
		"${CMAKE_CXX_FLAGS_DEBUG} ${warnings} ${comon_flags} -g -ggdb"
	)

	SET (CMAKE_CXX_FLAGS_RELEASE
		"${CMAKE_CXX_FLAGS_RELEASE} ${warnings} ${common_flags} -O2"
	)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories (
	/opt/local/include
)

link_directories (
	/opt/local/lib
)

endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set (external_libs
	koohar
	oodb
)

set (doctor_libs
	${external_libs}
	pthread
	ssl
	boost_system-mt
)

include_directories (
	external/koohar/src
	external/oodb/src
)

link_directories (${CMAKE_SOURCE_DIR}/lib)

set ( doctor_src
	src/crypting.cc
	src/device.cc
	src/disease.cc
	src/doctor.cc
	src/inmate.cc
	src/insurance.cc
	src/machine.cc
	src/md5.cc
	src/medic.cc
	src/patient.cc
	src/user.cc
	src/servey.cc
	src/settings.cc
	src/visit.cc
	src/handler.cc
	src/main.cc
)

add_executable ( doctor ${doctor_src} )
target_link_libraries ( doctor ${doctor_libs} )

