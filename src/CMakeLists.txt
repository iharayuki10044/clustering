add_library(Clustering
  SHARED
    clustering.cpp
  )
target_include_directories(Clustering
  PUBLIC ${PROJECT_SOURCE_DIR}/include/clustering
  )

add_executable(clusuring clustering.cpp)
target_link_libraries(clusuring Clustering)