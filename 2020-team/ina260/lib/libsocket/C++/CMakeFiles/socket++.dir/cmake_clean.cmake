file(REMOVE_RECURSE
  "libsocket++.dylib"
  "libsocket++.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/socket++.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
