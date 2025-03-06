import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12

ApplicationWindow {
    visible: true
    width: Screen.width
    height: Screen.height

    property bool loggedIn: false

    flags: Qt.FramelessWindowHint

    Loader {
        id: pageLoader
        anchors.fill: parent
        source: loggedIn ? "Dashboard.qml" : "Login.qml" // Only active when loggedIn is changed.
        onLoaded: {
            if (loggedIn) {
                pageLoader.item.logOutRequested.connect(() => {
                    loggedIn = false; // Log out and return to Login.qml
                });
            }
        }
    }

    Connections {
        target: loginHandlerQML
        onLoggedIn: (success) => {
            loggedIn = success;
        }
    }
}

