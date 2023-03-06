find_path(CryptoPP_INCLUDE_DIR cryptopp)
find_library(CryptoPP_LIBRARY cryptopp)

set(CryptoPP_LIBRARIES ${CryptoPP_LIBRARY})
set(CryptoPP_INCLUDE_DIRS ${CryptoPP_INCLUDE_DIR})

if(CryptoPP_INCLUDE_DIRS AND CryptoPP_LIBRARIES)
    set(CryptoPP_FOUND TRUE)
endif()

if(CryptoPP_FOUND)
    if(NOT CryptoPP_FIND_QUIETLY)
        message(STATUS "Found Crypto++: ${CryptoPP_LIBRARIES}")
    endif()
else()
    if(CryptoPP_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find Crypto++ library")
    endif()
endif()

mark_as_advanced(CryptoPP_INCLUDE_DIRS CryptoPP_LIBRARIES)