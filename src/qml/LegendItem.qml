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

import QtQuick 2.0
import org.kde.charts 0.1

/**
 * An item to compose the legend for a chart of.
 *
 * Displays the color and the label of one associated dimension.
 */
Item {
    /**
    * The dimension the legend item is associated to.
    */
    property Dimension dimension

    /**
    * The text color for the legend label.
    *
    * Default value is black.
    */
    property alias textColor: label.color

    implicitHeight: label.height
    implicitWidth: box.width + label.width + 5

    Rectangle {
        id: box
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
        }
        color: dimension? dimension.color: "#000000"
        width: height
        height: label.font.pixelSize
        radius: 4
    }

    Text {
        id: label
        anchors {
            top: parent.top
            right: parent.right
        }
        text: dimension? dimension.label: ""
    }
}
