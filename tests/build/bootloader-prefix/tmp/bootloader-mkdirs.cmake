# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/nicolasub/esp-idf/components/bootloader/subproject"
  "/home/nicolasub/Documents/CAP1298/tests/build/bootloader"
  "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix"
  "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix/tmp"
  "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix/src/bootloader-stamp"
  "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix/src"
  "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/nicolasub/Documents/CAP1298/tests/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
