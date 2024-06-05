cmake_minimum_required(VERSION 3.14)

project(alienfx-cli LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

# Adicionar a busca pela biblioteca libusb-1.0
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

# Incluir diretórios de cabeçalho
include_directories(${LIBUSB_INCLUDE_DIRS})

add_executable(alienfx-cli
  main.cpp
  LightFX.h

  USBDeviceHandler.h
  PayloadAgregation.h
  AlienFx_SDK.h
  mainwindow.h mainwindow.cpp mainwindow.ui
)

# Linkar a biblioteca libusb-1.0
target_link_libraries(alienfx-cli Qt${QT_VERSION_MAJOR}::Core ${LIBUSB_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS alienfx-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
