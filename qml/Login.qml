import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    color: "#f0f0f0" // Màu nền nhẹ cho toàn bộ giao diện

    Column {
        width: parent.width * 0.28
        anchors.centerIn: parent
        spacing: parent.height * 0.01 

        Text {
            width: parent.width
            id: statusText
            text: loginHandlerQML.statusMessage
            color: "red"
            font.pixelSize: parent.height * 0.05
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            width: parent.width
            height: parent.height * 0.28
            radius: 12
            border.color: "#cccccc"
            border.width: 1
            color: "white"

            TextField {
                id: usernameField
                width: parent.width * 0.9
                height: parent.height
                anchors.centerIn: parent
                placeholderText: "Username"
                font.pixelSize: parent.height * 0.5
                background: null
            }
        }

        Rectangle {
            width: parent.width
            height: parent.height * 0.28
            radius: 12
            border.color: "#cccccc"
            border.width: 1
            color: "white"

            TextField {
                id: passwordField
                width: parent.width * 0.9
                height: parent.height
                anchors.centerIn: parent
                placeholderText: "Password"
                echoMode: TextInput.Password
                font.pixelSize: parent.height * 0.5
                background: null
            }
        }

        Button {
            id: loginButton
            text: "Login"
            width: parent.width
            height: parent.height * 0.25
            font.pixelSize: parent.height * 0.06

            background: Rectangle {
                radius: 10
                color: loginButton.pressed ? "#1976D2" : "#2196F3"
                border.color: "#1565C0"
                border.width: 1
            }

            onClicked: {
                loginHandlerQML.login(usernameField.text, passwordField.text)
            }
            Keys.onReturnPressed: {
                loginButton.clicked()
            }
        }
    }

    Button {
        id: closeButton
        text: "Close Application"
        width: parent.width * 0.2 
        height: parent.height * 0.08 
        font.pixelSize: parent.height * 0.04 
        padding: parent.height * 0.01
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: parent.height * 0.03

        background: Rectangle {
            radius: 12
            color: closeButton.pressed ? "#B71C1C" : "#D32F2F"
            border.color: "#F44336"
            border.width: 2
        }

        onClicked: Qt.quit()
    }
}