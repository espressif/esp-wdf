set(CMAKE_C_COMPILER   clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_LINKER       wasm-ld)
set(CMAKE_AR           llvm-ar)
set(CMAKE_NM           llvm-nm)
set(CMAKE_OBJDUMP      llvm-dwarfdump)
set(CMAKE_RANLIB       llvm-ranlib)