SET (CMAKE_C_COMPILER   clang)
SET (CMAKE_CXX_COMPILER clang++)

SET (CMAKE_LINKER       wasm-ld)
SET (CMAKE_AR           llvm-ar)
SET (CMAKE_NM           llvm-nm)
SET (CMAKE_OBJDUMP      llvm-dwarfdump)
SET (CMAKE_RANLIB       llvm-ranlib)

SET (CMAKE_C_FLAGS      "-nostdlib -z stack-size=4096 -O3 -Wno-unused-command-line-argument"   CACHE INTERNAL "")
SET (CMAKE_CXX_FLAGS    "-nostdlib -z stack-size=4096 -O3 -Wno-unused-command-line-argument"   CACHE INTERNAL "")

SET (CMAKE_EXE_LINKER_FLAGS
    "-Wl,--initial-memory=65536,--no-entry,--allow-undefined,--strip-all,--export=main" CACHE INTERNAL "")