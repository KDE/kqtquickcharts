cmake_minimum_required(VERSION 3.5)

project(KQtQuickCharts)

# Dependencies
find_package(ECM 1.1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} )


# Includes
include(FeatureSummary)
include(GenerateExportHeader)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(CMakePackageConfigHelpers)
include(ECMQueryQt)

set(REQUIRED_QT_VERSION "5.2.0")
set(KF_MIN_VERSION "5.1.0") # handled by release scripts ### TODO
set(KF_DEP_VERSION "5.1.0") # handled by release scripts ### TODO


if (QT_MAJOR_VERSION STREQUAL "6")
    set(QT_REQUIRED_VERSION "6.4.0")
    set(KF_MIN_VERSION "5.240.0")
    set(KF_MAJOR_VERSION "6")
else()
    set(KF_MAJOR_VERSION "5")
endif()

find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} NO_MODULE REQUIRED Qml Quick Gui)
include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings)
include(KDECMakeSettings)

#########################################################################

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0)

#add_definitions(-Wno-deprecated)
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)

remove_definitions(-DQT_NO_CAST_FROM_ASCII -DQT_STRICT_ITERATORS -DQT_NO_CAST_FROM_BYTEARRAY -DQT_NO_KEYWORDS)




# ECM setup
ecm_setup_version(
  ${KF_MIN_VERSION}
  VARIABLE_PREFIX KQTQUICKCHARTS
  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kqtquickcharts_version.h"
  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsVersion.cmake"
  SOVERSION 1)

#add_subdirectory(autotests)

add_subdirectory(src)

# if(KF${KF_MAJOR_VERSION}Config_FOUND AND KF${KF_MAJOR_VERSION}I18n_FOUND AND KF${KF_MAJOR_VERSION}IconThemes_FOUND AND KF${KF_MAJOR_VERSION}KIO_FOUND)
#     add_subdirectory(tests)
# endif()

# Create a Config.cmake and a ConfigVersion.cmake file and install them
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KQtQuickCharts")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KQtQuickChartsConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsConfig.cmake"
  INSTALL_DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
)

install(FILES
 "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KQtQuickChartsVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

# install(EXPORT
#   KQtQuickChartsTargets
#   DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
#   FILE KQtQuickChartsTargets.cmake
#   NAMESPACE KF${KF_MAJOR_VERSION}::
#   COMPONENT Devel
# )

if (QT_MAJOR_VERSION STREQUAL "5") ### TODO
  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/kqtquickcharts_version.h"
    DESTINATION "${KDE_INSTALL_INCLUDEDIR_KF5}"
    COMPONENT Devel
  )
endif()

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_CURRENT_BINARY_DIR}")
  feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
endif()
