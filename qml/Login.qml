import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    color: "#f0f0f0" // Màu nền nhẹ cho toàn bộ giao diện

    Column {
        width: parent.width * 0.28
        anchors.centerIn: parent
        spacing: parent.height * 0.01 

        Label {
            width: parent.width
            id: statusText
            text: loginHandlerQML.statusMessage
            color: "red"
            horizontalAlignment: Label.AlignHCenter
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

        CustomButton {
            id: loginButton
            text: "Login"
            width: parent.width
            height: parent.height * 0.25

            normalColor: "#2196F3"
            hoverColor: "#1976D2"
            borderColor: "#1565C0"

            onClicked: {
                loginHandlerQML.login(usernameField.text, passwordField.text)
            }
            Keys.onReturnPressed: {
                loginButton.clicked()
            }
        }
    }

    CustomButton {
        id: closeButton
        text: "CLOSE APPLICATION"
        width: parent.width * 0.2 
        height: parent.height * 0.08 

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: parent.height * 0.03

        normalColor: "#D32F2F"
        hoverColor: "#B71C1C"
        borderColor: "#9A1919"

        onClicked: Qt.quit()
    }
}