cmake_minimum_required(VERSION 3.5)

project(KQtQuickCharts)

# Dependencies
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} )

set(REQUIRED_QT_VERSION "6.5.0")
set(KF_MIN_VERSION "6.0.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Qml Quick Gui)

#########################################################################

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)

#add_definitions(-Wno-deprecated)
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

remove_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_STRICT_ITERATORS -DQT_NO_CAST_FROM_BYTEARRAY -DQT_NO_KEYWORDS)



# Includes
include(FeatureSummary)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)

# ECM setup
ecm_setup_version(
  ${KF_MIN_VERSION}
  VARIABLE_PREFIX KQTQUICKCHARTS
  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kqtquickcharts_version.h"
  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsConfigVersion.cmake"
  SOVERSION 1)

add_subdirectory(src)

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KQtQuickCharts")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KQtQuickChartsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsConfig.cmake"
  INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

# install(EXPORT
#   KQtQuickChartsTargets
#   DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
#   FILE KQtQuickChartsTargets.cmake
#   NAMESPACE KF5::
#   COMPONENT Devel
# )

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/kqtquickcharts_version.h"
  DESTINATION "${KDE_INSTALL_INCLUDEDIR_KF}"
  COMPONENT Devel
)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()
