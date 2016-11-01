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

import QtQuick 2.2
import org.kde.charts 0.1

Rectangle {
    id: root
    property Item chart

    width: chart.model.columns * (listView.cellWidth + listView.spacing) + listView.spacing

    color: "#fff"

    ListView {
        id: listView
        anchors {
            fill: parent
            leftMargin: spacing
            topMargin: spacing
            bottomMargin: spacing
        }
        clip: true
        model: root.chart.model.rows

        property real cellHeight: 30
        property real cellWidth: 4 * cellHeight
        spacing: 3

        header: Component {
            Row {
                spacing: 3
                height: childrenRect.height + listView.spacing
                Repeater {
                    model: root.chart.dimensions.length
                    Rectangle {
                        color: "#bbb"
                        height: listView.cellHeight
                        width: listView.cellWidth
                        LegendItem {
                            anchors.centerIn: parent
                            dimension: root.chart.dimensions[index]
                        }
                    }

                }
            }
        }

        delegate: Row {
            id: rowDelegate
            property int row: index
            height: childrenRect.height
            spacing: 3
            Repeater {
                model: chart.model.columns
                ValueEdit {
                    id: cell
                    property int column: index
                    height: listView.cellHeight
                    width: listView.cellWidth
                    value: root.chart.model.value(row, column)
                    onValueChanged: {
                        if (root.chart.model.value(row, column) != value) {
                            root.chart.model.setValue(row, column, value)
                        }
                    }
                    Connections {
                        target: root.chart.model
                        onRecordChanged: {
                            if (row == rowDelegate.row) {
                                cell.value = root.chart.model.value(row, column)
                            }
                        }
                    }
                }
            }
        }
    }
}
