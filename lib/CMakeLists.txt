# cache_ build system -- lib root

set(LIBLIST
  rrip
  ideal_cache
)

foreach(LIB ${LIBLIST})
  add_subdirectory(${LIB})
endforeach()

set(LIBLIST "${LIBLIST}" PARENT_SCOPE)