
set(merging_unit_example_SRCS
  merging_unit.c
)

IF(WIN32)

set_source_files_properties(${merging_unit_example_SRCS}
                                       PROPERTIES LANGUAGE CXX)
add_executable( merging_unit
  ${merging_unit_example_SRCS}
)

target_link_libraries( merging_unit
    iec61850
)

ELSE(WIN32)

add_executable( merging_unit
  ${merging_unit_example_SRCS}
)

target_link_libraries( merging_unit
    iec61850
)

ENDIF(WIN32)


