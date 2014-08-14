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
import QtQuick.Controls 1.2

Rectangle {
    color: "#ddd"
    id: root
    property real value: 0.0
    property bool editing: false
    property real internalPadding: 3

    Text {
        anchors {
            left: parent.left
            right: parent.right
            leftMargin: internalPadding
            rightMargin: internalPadding
            verticalCenter: parent.verticalCenter
        }

        verticalAlignment: Text.Center
        text: value
        visible: !editing
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            editing = true
            if (loader.item) {
                loader.item.forceActiveFocus()
            }
            else {
                loader.sourceComponent = editorComponent
            }
        }
    }

    Loader {
        id: loader
        anchors.fill: parent
    }

    Component {
        id: editorComponent
        TextField {
            anchors.fill: parent
            opacity: root.editing? 1: 0
            text: root.value
            Component.onCompleted: {
                forceActiveFocus()
            }
            onTextChanged: {
                var value = parseFloat(text)
                if (!isNaN(value)) {
                    root.value = value
                }
            }
            onActiveFocusChanged: {
                if (!activeFocus) {
                    root.editing = false
                }
            }
            onAccepted: {
                root.editing = false
            }
        }
    }
}
