/*
 *  Copyright 2015  Jesper Hellesø Hansen <jesperhh@gmail.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) version 3, or any
 *  later version accepted by the membership of KDE e.V. (or its
 *  successor approved by the membership of KDE e.V.), which shall
 *  act as a proxy defined in Section 6 of version 3 of the license.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 */

import QtQuick 2.2
import org.kde.charts 0.1

/**
 * An interactive xy chart.
 *
 * At the minimum, set the 'model' and 'dimensions' properties to use
 * this component.
 */
Item {
    id: root

    /**
     * type:QAbstractTableModel
     * The source model the data for the chart is taken from.
     *
     * One row represents a record in the chart. Use the 'dimensions'
     * property to define which columns carry the relevant data.
     */
    property alias model: core.model

    /**
     * type:list<Dimension>
     * The list of dimensions for the graph.
     *
     * Each dimension defines the appearance of the data from one
     * column in the source model. See the documentation for Dimension
     * for details.
     */
    property alias dimensions: core.dimensions

    /**
     * type:Dimension
     * The x axis description for the graph.
     *
     * Defines the dimension used for the x axis. The x axis is shared between
     * all dimensions (for now). See the documentation for Dimension
     * for details.
     */
    property alias xAxis: core.xAxis

    /**
     * type:Dimension
     * The y axis description for the graph.
     *
     * Defines the dimension used for the y axis. The y axis is shared between
     * all dimensions (for now). See the documentation for Dimension
     * for details.
     */
    property alias yAxis: core.yAxis

    /**
     * type:int
     * The role to query text from the model for data indices.
     *
     * If set there will be text labels with the data fetched with the
     * specified role next to the point elements.
     *
     * Default value is -1 (unset).
     */
    property alias textRole: core.textRole

    /**
     * type:color
     * The background color used for the chart.
     *
     * @warn colors with an non-zero alpha component aren't supported yet
     * and result in an visual deficiencies.
     *
     * Default value is white.
     */
    property alias backgroundColor: bg.color

    /**
     * type:color
     * The text color used for the chart
     *
     * Used for pitch lines and date element labels.
     *
     * Default value is black.
     */
    property alias textColor: core.textColor

    /**
     * type:real
     * The size of markers on the lines
     *
     * Default value is 5.0.
     */
    property alias pointRadius: core.pointRadius

    /**
     * type:real
     * The width of the lines between data points as well as axis and
     * grid lines.
     *
     * Default value is 2.0.
     */
    property alias lineWidth: core.lineWidth

    /**
     * Fires when the user has clicked on a data element.
     *
     * @param dimension The dimension the data element belongs to.
     * @param row The row in the source model the data element represents.
     * @param elem The QML item for data element itself.
     */
    signal elemClicked(variant dimension, int row, variant elem)


    /**
     * Fires when the mouse cursor touches a data element.
     *
     * @param dimension The dimension the data element belongs to.
     * @param row The row in the source model the data element represents.
     * @param elem The QML item for data element itself.
     */
    signal elemEntered(variant dimension, int row, variant elem)

    /**
     * Fires when the mouse cursor leaves a data element.
     *
     * @param dimension The dimension the data element belongs to.
     * @param row The row in the source model the data element represents.
     * @param elem The QML item for data element itself.
     */
    signal elemExited(variant dimension, int row, variant elem)

    Rectangle {
        id: bg
        anchors.fill: parent
        color: "transparent"
    }

    Text {
        id: yLabel
        font: core.font
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        horizontalAlignment: Text.AlignHCenter
        text: core.yAxis.label + "\n(" + core.yAxis.unit + ")"
        color: core.textColor
    }

    Text {
        id: xLabel
        font: core.font
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        text: core.xAxis.label + " (" + core.xAxis.unit + ")"
        color: core.textColor
    }

    XYChartCore {
        id: core

        anchors.left: yLabel.right
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: xLabel.top

        XYChartBackgroundPainter {
            id: xyBg
            xyChartCore: core
            anchors.fill: parent
        }

        Repeater {
            id: dimensionsRepeater

            model: core.dimensions.length

            delegate: XYChartPainter {
                id: xyChart
                xyChartCore: core
                backgroundPainter: xyBg
                dimension: index
                anchors.fill: parent

                Repeater {
                    model: core.model
                    delegate: XYChartPoint {
                        id: point
                        xyChartCore: core
                        backgroundPainter: xyBg
                        dimension: xyChart.dimension
                        row: index

                        Label {
                            anchors.top: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            backgroundItem: bg
                            text: parent.text
                        }

                        MouseArea {
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked: root.elemClicked(core.dimensions[xyChart.dimension], parent.row, parent)
                            onEntered: root.elemEntered(core.dimensions[xyChart.dimension], parent.row, parent)
                            onExited: root.elemExited(core.dimensions[xyChart.dimension], parent.row, parent)
                        }
                    }
                }
            }
        }
    }
}
