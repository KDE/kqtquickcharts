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

Rectangle {
    color: "white"
    width: 800
    height: 400

    ChartModel {
        id: chartModel
        columns: 4

        Record { values: [ 0,  3] }
        Record { values: [ 1,  8,  6.5, 2] }
        Record { values: [ 2,  5,  NaN, 3] }
        Record { values: [ 3,  10, NaN, 4] }
        Record { values: [ 4,  8,  NaN, 5] }
        Record { values: [ 5,  4,  5.5, 6] }
        Record { values: [ 6,  3] }
        Record { values: [ 7,  0] }
        Record { values: [ 8,  7,  5.5] }
        Record { values: [ 9,  6] }
        Record { values: [ 10, 10] }
    }

    XYChart {
        model: chartModel
        anchors.fill: parent
        textColor: "black"
        anchors.margins: 20
        dimensions: [
            Dimension {
                color: "#ff0000"
                dataColumn: 1
                label: "A"
                markerStyle: Dimension.MarkerStyleNone
            },
            Dimension {
                color: "#0000FF"
                dataColumn: 2
                lineStyle: Dimension.LineStyleNone
                markerStyle: Dimension.MarkerStyleCross
            },
            Dimension {
                color: "#00FF00"
                dataColumn: 3
                label: "B"
            }
        ]

        xAxis: Dimension {
            dataColumn: 0
            minimumValue: 0
            maximumValue: 10
            label: "X Label"
            precision: 0
            unit:"cm"
        }

        yAxis: Dimension {
            dataColumn: 0
            minimumValue: 0
            maximumValue: 10
            label: "Y Label"
            precision: 0
            unit:"hz"
        }
    }
}
