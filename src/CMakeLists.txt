project(kqtquickcharts)

include(KDE4Defaults)
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

include_directories(${QT_INCLUDE} ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(kqtquickcharts_SRCS
    dimension.cpp
    chartplugin.cpp
    chartcore.cpp
    chartmodel.cpp
    barchartcore.cpp
    barchartsegment.cpp
    linechartcore.cpp
    linechartbackgroundpainter.cpp
    linechartpainter.cpp
    linechartpoint.cpp
    chartforegroundpainter.cpp
    record.cpp
    )

automoc4_add_library(kqtquickcharts SHARED ${kqtquickcharts_SRCS})
target_link_libraries(kqtquickcharts ${KDE4_PLASMA_LIBS} ${QT_QTSCRIPT_LIBRARY} ${QT_QTDECLARATIVE_LIBRARY} ${KDECLARATIVE_LIBRARIES})

install(TARGETS kqtquickcharts DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/charts)

set(kqtquickcharts_files
    qml/qmldir

    qml/BarChart.qml
    qml/LineChart.qml
    qml/LegendItem.qml
    qml/LineLabel.qml
    qml/Label.qml
)

install(FILES ${kqtquickcharts_files} DESTINATION ${IMPORTS_INSTALL_DIR}/org/kde/charts)
