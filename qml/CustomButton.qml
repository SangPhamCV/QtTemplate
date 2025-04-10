import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: btn
    property color normalColor: "#3498db"
    property color hoverColor: "#2980b9"    
    property color borderColor: "#1c6ea4"
    property color glowColor: "#4CAF50"
    property color textColor: "white"
    
    property real glowSize: 30
    property int borderWidth: 2
    property int cornerRadius: 10
    
    property bool isRound: false
    property bool hasGlow: false
    property alias isOn: glowEffect.isOn

    font.bold: true

    Item {
        id: glowEffect
        anchors.centerIn: bg
        width: bg.width + glowSize
        height: bg.height + glowSize
        property bool isOn: false
        visible: hasGlow && isOn

        Rectangle {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            radius: isRound ? width / 2 : cornerRadius
            color: btn.glowColor
            opacity: 0.2
        }
        Rectangle {
            anchors.centerIn: parent
            width: parent.width * 0.85
            height: parent.height * 0.85
            radius: isRound ? width / 2 : cornerRadius
            color: btn.glowColor
            opacity: 0.4
        }
    }

    background: Rectangle {
        id: bg
        radius: isRound ? width / 2 : cornerRadius
        color: normalColor
        border.color: borderColor
        border.width: borderWidth
        Behavior on color { ColorAnimation { duration: 200 } }
    }

    contentItem: Text {
        text: parent.text
        color: textColor
        font: parent.font
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.Wrap
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onEntered: bg.color = hoverColor
        onExited: bg.color = normalColor

        onPressed: btn.scale = 0.9
        onReleased: btn.scale = 1.0
        onClicked: {
            if (btn.clicked) btn.clicked();  // ✅ Call `onClicked` only if defined
        }
    }

    Behavior on scale { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }
}
