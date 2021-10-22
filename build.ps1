$builddir="build"

Remove-Item -Path $builddir -Recurse -ErrorAction Ignore
New-Item -Path $builddir -Type Directory 

cmake -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake -S . -B $builddir
cmake --build $builddir
