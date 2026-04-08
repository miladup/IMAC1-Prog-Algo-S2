cmake_minimum_required(VERSION 3.24)
project("IMAC_TD3")

# 1. Où vont les exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 2. Dossier des headers
include_directories(include)

# 3. Chemin vers fichier de tri
set(SORT_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/sorts.cpp")

# Exercice 1
add_executable(exo1 src/exo1/main.cpp ${SORT_SOURCE})
target_compile_features(exo1 PRIVATE cxx_std_17)

# Exercice 2
add_executable(exo2 src/exo2/main.cpp ${SORT_SOURCE})
target_compile_features(exo2 PRIVATE cxx_std_17)

# Exercice 3
add_executable(exo3 src/exo3/main.cpp ${SORT_SOURCE})
target_compile_features(exo3 PRIVATE cxx_std_17)

# Exercice 4
add_executable(exo4 src/exo4/main.cpp ${SORT_SOURCE})
target_compile_features(exo4 PRIVATE cxx_std_17)