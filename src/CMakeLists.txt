project(kqmlgraphplugin)

include(KDE4Defaults)
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

include_directories(${QT_INCLUDE} ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(kqmlgraphplugin_SRCS
    dimension.cpp
    graphplugin.cpp
    graphcore.cpp
    bargraphcore.cpp
    bargraphsegment.cpp
    linegraphcore.cpp
    linegraphbackgroundpainter.cpp
    linegraphpainter.cpp
    linegraphpoint.cpp
    graphforegroundpainter.cpp
    )

automoc4_add_library(kqmlgraphplugin SHARED ${kqmlgraphplugin_SRCS})
target_link_libraries(kqmlgraphplugin ${KDE4_PLASMA_LIBS} ${QT_QTSCRIPT_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${KDECLARATIVE_LIBRARIES})

install(TARGETS kqmlgraphplugin DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/graphs)

set(kqmlgraphplugin_files
    qml/qmldir

    qml/BarGraph.qml
    qml/LineGraph.qml
    qml/LegendItem.qml
    qml/LineLabel.qml
    qml/Label.qml
)

install(FILES ${kqmlgraphplugin_files} DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/graphs)
