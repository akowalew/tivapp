# FindTivaWare.cmake
# - Try to find TivaWare
# Once done this will define
# 	TIVAWARE_FOUND - System has TivaWare
# 	TIVAWARE_INCLUDE_DIRS - The TivaWare include directories
# Author: akowalew

set(TivaWare_FOUND TRUE)

find_path(_TIVAWARE_INCLUDE_DIR inc PATH_SUFFIXES tivaware)
if(_TIVAWARE_INCLUDE_DIR)
	list(APPEND _TIVAWARE_INCLUDE_DIRS ${_TIVAWARE_INCLUDE_DIR})
else()
	set(TivaWare_FOUND FALSE)
	message(FATAL_ERROR "Could not find: _TIVAWARE_INCLUDE_DIR")
endif()

if("driverlib" IN_LIST TivaWare_FIND_COMPONENTS)
	find_path(_TIVAWARE_DRIVERLIB_INCLUDE_DIR driverlib PATH_SUFFIXES tivaware)
	if(_TIVAWARE_DRIVERLIB_INCLUDE_DIR)
		list(APPEND _TIVAWARE_INCLUDE_DIRS ${_TIVAWARE_INCLUDE_DIR})
	else()
		set(TivaWare_FOUND FALSE)
		message(FATAL_ERROR "Could not find: _TIVAWARE_DRIVERLIB_INCLUDE_DIR")
	endif()

	find_library(_TIVAWARE_DRIVERLIB_LIBRARY driver PATH_SUFFIXES tivaware)
	if(_TIVAWARE_DRIVERLIB_LIBRARY)
		list(APPEND _TIVAWARE_LIBRARIES ${_TIVAWARE_DRIVERLIB_LIBRARY})
	else()
		set(TivaWare_FOUND FALSE)
		message(FATAL_ERROR "Could not find: _TIVAWARE_DRIVERLIB_LIBRARY")
	endif()
endif()

if("utils" IN_LIST TivaWare_FIND_COMPONENTS)
	find_path(_TIVAWARE_UTILS_INCLUDE_DIR utils PATH_SUFFIXES tivaware)
	if(_TIVAWARE_UTILS_INCLUDE_DIR)
		list(APPEND _TIVAWARE_INCLUDE_DIRS ${_TIVAWARE_UTILS_INCLUDE_DIR})
	else()
		set(TivaWare_FOUND FALSE)
		message(FATAL_ERROR "Could not find: _TIVAWARE_UTILS_INCLUDE_DIR")
	endif()

	find_library(_TIVAWARE_UTILS_LIBRARY utils PATH_SUFFIXES tivaware)
	if(_TIVAWARE_UTILS_LIBRARY)
		list(APPEND _TIVAWARE_LIBRARIES ${_TIVAWARE_UTILS_LIBRARY})
	else()
		set(TivaWare_FOUND FALSE)
		message(FATAL_ERROR "Could not find: _TIVAWARE_UTILS_LIBRARY")
	endif()
endif()

mark_as_advanced(
	_TIVAWARE_INCLUDE_DIR
	_TIVAWARE_DRIVERLIB_INCLUDE_DIR 
	_TIVAWARE_DRIVERLIB_LIBRARY
	_TIVAWARE_UTILS_INCLUDE_DIR
	_TIVAWARE_UTILS_LIBRARY
)

if(TivaWare_FOUND)
	set(TivaWare_LIBRARIES ${_TIVAWARE_LIBRARIES})
	set(TivaWare_INCLUDE_DIRS ${_TIVAWARE_INCLUDE_DIRS})
endif()
