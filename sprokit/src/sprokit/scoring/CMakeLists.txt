project(sprokit_scoring)

set(scoring_srcs
  statistics.cxx)

set(scoring_headers
  scoring-config.h
  statistics.h)

sprokit_add_library(sprokit_scoring
  ${scoring_srcs}
  ${scoring_headers})
set_target_properties(sprokit_scoring
  PROPERTIES
    VERSION       ${KWIVER_VERSION}
    SOVERSION     0
    DEFINE_SYMBOL MAKE_SPROKIT_SCORING_LIB)

sprokit_install_headers(sprokit/scoring ${scoring_headers})

sprokit_configure_pkgconfig(sprokit-scoring)
