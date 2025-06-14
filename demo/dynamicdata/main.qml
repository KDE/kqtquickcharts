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
import QtQuick.Controls
import org.kde.charts 0.1

Column {
    width: 1000
    height: 500
    spacing: 15

    Component.onCompleted: {
        for (var i = 0; i < 25; i++) {
            appendRecord()
        }
    }

    function randomizeRecord(row) {
        for (var column = 0; column < chart.model.columns; column++) {
            var value = parseInt(100 * Math.random()) / 100
            chart.model.setValue(row, column, value)
        }
    }

    function appendRecord() {
        chart.model.appendRecord()
        randomizeRecord(chart.model.rows - 1)
        var row = chart.model.rows - 1
    }

    function insertRecord() {
        chart.model.insertRecord(0)
        randomizeRecord(0)
    }

    function removeRecord() {
        if (chart.model.rows > 0) {
            var row = chart.model.rows - 1
            chart.model.removeRecord(row)
        }
    }

    ToolBar {
        id: toolbar
        Row {
            spacing: 4
            ToolButton {
                anchors.verticalCenter: parent.verticalCenter
                //iconSource: "edit-table-insert-row-below"
                text: "Append record"
                onClicked: appendRecord()
            }
            ToolButton {
                anchors.verticalCenter: parent.verticalCenter
                //iconSource: "edit-table-insert-row-above"
                text: "Insert record"
                onClicked: insertRecord()
            }
            ToolButton {
                anchors.verticalCenter: parent.verticalCenter
                //iconSource: "edit-table-delete-row"
                text: "Remove record"
                onClicked: removeRecord()
            }
        }
    }

    Item {
        height: parent.height - toolbar.height - parent.spacing
        width: parent.width

        Row {
            anchors {
                fill: parent
                margins: 20
            }

            spacing: 40

            ChartTableView {
                id: tableView
                height: parent.height
                chart: chart
            }

            Rectangle {
                color: "white"
                width: parent.width - tableView.width - parent.spacing
                height: parent.height

                Chart {
                    id: chart
                    anchors.fill: parent
                    padding: 10
                }
            }
        }
    }
}
