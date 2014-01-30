/*
 *  Copyright 2014  Sebastian Gottfried <sebastiangottfried@web.de>
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

import QtQuick 1.1
import org.kde.plasma.components 0.1 as PlasmaComponents

/**
 * An interactive bar chart.
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
     * type:real
     * The horizontal space used for each record in pixels.
     *
     * Default value is 50.0.
     */
    property alias pitch: core.pitch

    /**
     * type:int
     * The role to query text from the model for data indices
     *
     * If set there will be text labels with the data fetched with the
     * specified role next to the bar elements.
     *
     * Default value is -1 (unset).
     */
    property alias textRole: core.textRole

    /**
     * type:color
     * The background color used for the chart.
     *
     * @warn colors with an non-zero alpha component aren't supported yet
     * and result in an visual defiencies.
     *
     * Default value is the theme's background color.
     */
    property alias backgroundColor: bg.color

    /**
     * type:color
     * The text color used for the chart
     *
     * Used for pitch line and date element labels.
     *
     * Default value is the theme's text color.
     */
    property color textColor: theme.textColor

    /**
     * The amount of space between the outline of the chart background
     * and the chart contents.
     *
     * Default value 0.0.
     */
    property real padding: 0.0

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
        color: theme.backgroundColor
    }

    BarChartCore {
        id: core

        anchors {
            fill: parent
            margins: root.padding
        }

        ListView {
            id: list
            anchors.fill: parent
            clip: true

            model: core.model
            orientation: ListView.Horizontal

            header: Item {
                width: Math.floor(core.pitch / 2)
                height: list.height
            }

            footer: Item {
                width: Math.ceil(core.pitch / 2)
                height: list.height
            }

            delegate: Item {
                id: segmentContainer
                property int row: index

                width: core.pitch
                height: parent.height

                Repeater {
                    anchors.fill: parent
                    model: core.dimensions.length

                    delegate: BarChartSegment {
                        id: segment
                        barChartCore: core
                        dimension: index
                        row: segmentContainer.row

                        width: core.barWidth
                        height: parent.height
                        x: (dimension + 0.5) * width

                        Rectangle {
                            property Dimension dimension: core.dimensions[segment.dimension]
                            anchors.bottom: parent.bottom
                            color: dimension.color
                            width: core.barWidth
                            height: segment.barHeight

                            Label {
                                anchors.bottom: parent.bottom
                                anchors.horizontalCenter: parent.horizontalCenter
                                backgroundItem: bg
                                text: segment.text
                            }

                            MouseArea {
                                anchors.fill: parent
                                hoverEnabled: true
                                onClicked: root.elemClicked(parent.dimension, segment.row, parent)
                                onEntered: root.elemEntered(parent.dimension, segment.row, parent)
                                onExited: root.elemExited(parent.dimension, segment.row, parent)
                            }
                        }
                    }
                }
            }
        }

        ChartForegroundPainter {
            anchors.fill: parent
            chartCore: core
            backgroundColor: bg.color
        }

        LineLabel {
            anchors {
                top: parent.top
                left: parent.left
                topMargin: 2
            }
            backgroundItem: bg
            color: root.textColor
            dimension: core.dimensions.length > 0? core.dimensions[0]: null
            valueFactor: 1
        }

        LineLabel {
            anchors {
                top: parent.top
                left: parent.left
                topMargin: (core.height - 4) / 2 + 2
            }
            backgroundItem: bg
            color: root.textColor
            dimension: core.dimensions.length > 0? core.dimensions[0]: null
            valueFactor: 0.5
        }

        LineLabel {
            anchors {
                top: parent.top
                right: parent.right
                topMargin: 2
            }
            backgroundItem: bg
            color: root.textColor
            dimension: core.dimensions.length > 1? core.dimensions[1]: null
            valueFactor: 1
        }

        LineLabel {
            anchors {
                top: parent.top
                right: parent.right
                topMargin: (core.height - 4) / 2 + 2
            }
            backgroundItem: bg
            color: root.textColor
            dimension: core.dimensions.length > 1? core.dimensions[1]: null
            valueFactor: 0.5
        }
    }
}
