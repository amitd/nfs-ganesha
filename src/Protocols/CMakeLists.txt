include_directories(
  ${LIBTIRPC_INCLUDE_DIR}
)

add_subdirectory(NFS)
add_subdirectory(XDR)
add_subdirectory(NLM)
add_subdirectory(RQUOTA)

if(USE_9P)
  add_subdirectory(9P)
endif(USE_9P)

if(USE_DBUS)
  add_subdirectory(DBUS)
endif(USE_DBUS)

########### install files ###############
