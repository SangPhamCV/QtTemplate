import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: btn
    property color normalColor: "#3498db"   // Màu nền mặc định
    property color hoverColor: "#2980b9"    // Màu khi di chuột vào
    property color borderColor: "#1c6ea4"   // Màu viền
    property int cornerRadius: 10           // Bo góc

    font.bold: true

    background: Rectangle {
        id: bg
        radius: cornerRadius
        color: normalColor
        border.color: borderColor
        border.width: 2
        Behavior on color { ColorAnimation { duration: 200 } }
    }

    contentItem: Text {
        text: parent.text
        color: "white"
        font: parent.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: bg.color = hoverColor
        onExited: bg.color = normalColor

        onPressed: {
            btn.scale = 0.9 
        }
        onReleased: {
            btn.scale = 1.0
        }

        onClicked: btn.clicked() 
    }

    Behavior on scale { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }
}
