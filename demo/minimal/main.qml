/*
 * Copyright 2014  Sebastian Gottfried <sebastiangottfried@web.de>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
            Value {value: 0.1}
            Value {value: 0.2}
        }
        Record {
            Value {value: 0.25}
            Value {value: 0.3}
        }
        Record {
            Value {value: 0.5}
            Value {value: 0.5}
        }
        Record {
            Value {value: 1.0}
            Value {value: 0.75}
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
