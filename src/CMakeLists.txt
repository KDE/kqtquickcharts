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
    xychartcore.cpp
    xychartbackgroundpainter.cpp
    xychartpainter.cpp
    xychartpoint.cpp
    )

add_library(kqtquickcharts SHARED ${kqtquickcharts_SRCS})


target_link_libraries(kqtquickcharts
    Qt5::Core
    Qt5::Quick
    Qt5::Qml
    Qt5::Gui
)

install(TARGETS kqtquickcharts DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/charts)

set(kqtquickcharts_files
    qml/qmldir

    qml/BarChart.qml
    qml/LineChart.qml
    qml/LegendItem.qml
    qml/LineLabel.qml
    qml/Label.qml
    qml/XYChart.qml
)

install(FILES ${kqtquickcharts_files} DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/charts)
