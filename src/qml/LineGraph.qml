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

Item {
    id: root

    property alias model: core.model
    property alias dimensions: core.dimensions
    property alias pitch: core.pitch
    property alias pointRadius: core.pointRadius
    property alias textRole: core.textRole

    property alias backgroundColor: bg.color
    property color textColor: theme.textColor
    property real padding: 0.0


    signal elemClicked(int row, variant elem)
    signal elemEntered(int row, variant elem)
    signal elemExited(int row, variant elem)

    Rectangle {
        id: bg
        anchors.fill: parent
        color: theme.backgroundColor
    }

    LineGraphCore {
        id: core

        anchors {
            fill: parent
            margins: root.padding
        }

        Flickable {
            id: flickable
            anchors.fill: parent

            clip: true

            contentHeight: height
            contentWidth: lineBg.width

            property real lastWidth: -1

            onContentWidthChanged: {
                if (contentWidth > width) {
                    contentX = contentWidth - width
                }
            }

            onWidthChanged: {
                if (lastWidth != -1 && contentWidth > width) {
                    contentX = contentX + lastWidth - width

                }
                lastWidth = width
            }

            LineGraphBackgroundPainter {
                id: lineBg
                lineGraphCore: core
                height: parent.height
            }

            Repeater {
                id: dimensionsRepeater

                model: core.dimensions.length

                delegate: LineGraphPainter {
                    id: line
                    lineGraphCore: core
                    backgroundPainter: lineBg
                    dimension: index
                    height: parent.height

                    Repeater {
                        model: core.model
                        delegate: LineGraphPoint {
                            id: point
                            lineGraphCore: core
                            backgroundPainter: lineBg
                            dimension: line.dimension
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
                                onClicked: root.elemClicked(parent.row, parent)
                                onEntered: root.elemEntered(parent.row, parent)
                                onExited: root.elemExited(parent.row, parent)
                            }
                        }
                    }
                }
            }
        }

        GraphForegroundPainter {
            anchors.fill: parent
            graphCore: core
            backgroundColor: bg.color
        }
        LineLabel {
            anchors {
                top: parent.top
                left: parent.left
                topMargin: core.pointRadius + 2
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
                topMargin: core.pointRadius + (core.height - 2 * core.pointRadius - 4) / 2 + 2
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
                topMargin: core.pointRadius + 2
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
                topMargin: core.pointRadius + (core.height - 2 * core.pointRadius) / 2 + 2
            }
            backgroundItem: bg
            color: root.textColor
            dimension: core.dimensions.length > 1? core.dimensions[1]: null
            valueFactor: 0.5
        }
    }
}
