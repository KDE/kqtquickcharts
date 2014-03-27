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
import org.kde.charts 0.1

Rectangle {
    color: "white"
    width: 800
    height: 400

    ChartModel {
        id: chartModel
        columns: 2

        Record {
            values: [0.1, 0.2]
        }
        Record {
            values: [0.25, 0.3]
        }
        Record {
            values: [0.5, 0.5]
        }
        Record {
            values: [1.0, 0.75]
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        LineChart {
            model: chartModel
            width: parent.width
            height: parent.height - legend.height - parent.spacing
            pitch: 180
            dimensions: [
                Dimension {
                    id: funDimension
                    color: "#ffd500"
                    dataColumn: 0
                    minimumValue: 0.0
                    maximumValue: 1.0
                    label: "Fun"
                    precision: 0
                    unit:" %"
                    unitFactor: 100.0
                },
                Dimension {
                    id: profitDimension
                    color: "#ff0000"
                    dataColumn: 1
                    minimumValue: 0.0
                    maximumValue: 1.0
                    label: "Profit"
                    precision: 0
                    unit:" %"
                    unitFactor: 100.0
                }
            ]
        }

        Row {
            id: legend
            spacing: 30
            anchors.horizontalCenter: parent.horizontalCenter

            LegendItem {
                dimension: funDimension
            }
            LegendItem {
                dimension: profitDimension
            }
        }
    }
}
