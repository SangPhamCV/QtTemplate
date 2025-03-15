import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
 
Rectangle {
    id: dashboard
    anchors.centerIn: parent 
    color: "#F5F5F5" 

    signal logOutRequested()

    property var fileNames: []
    property var clickedPoints: []
    property var selectedPointIndex: -1

    property bool isCreatingPoint: true
    property bool isMovingPoint: false
    property bool isClearingLandmarkPoint: false

    property var parentMargin: parent.height * 0.01
    property var componentMargin: parent.height * 0.015

    property var mapResolution: None
    property var mapOrigin: []
    // property var robotPose: rosBridgeClientQML.topicData["/amcl_pose"]
    property var robotPose: viewModelQML.robotPose

    property var linearSpeed: 0
    property var angularSpeed: 0

    property real robotX: 0
    property real robotY: 0

    function updateRobotPose() {
        if (!mapOrigin || !mapResolution || !robotPose) return;

        let newX = (robotPose.position_x - mapOrigin[0]) / mapResolution;
        let newY = (robotPose.position_y - mapOrigin[1]) / mapResolution;

        let newXX = newX * (mapImage.width / mapImage.sourceSize.width);
        let newYY = mapImage.height - (newY * (mapImage.height / mapImage.sourceSize.height));

        robotX = newXX;
        robotY = newYY;

        if (dashboard.clickedPoints.length === 0) {
            hermiteCurveQML.addPoint(newXX, newYY);
            dashboard.clickedPoints[0] = {x: newXX, y: newYY};
        } else {
            hermiteCurveQML.updatePoint(0, newXX, newYY);
            dashboard.clickedPoints[0] = {x: newXX, y: newYY};
        }
    }

    // Title Bar
    Rectangle {
        id: titleBar
        height: parent.height * 0.05
        width: parent.width * 0.3
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parentMargin  // Giả sử parentMargin đã định nghĩa

        radius: 12
        color: "#1976D2"

        Text {
            text: "ROBOT MANAGEMENT SYSTEM"
            color: "white"
            fontSizeMode: Text.Fit

            font.bold: true
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }
    }

    // Map selection
    ComboBox {
        id: comboBoxImage
        width: parent.width * 0.13
        height: titleBar.height
        model: fileListModelQML
        textRole: "fileName"

        anchors.top: titleBar.top
        anchors.right: titleBar.left
        anchors.rightMargin: componentMargin

        background: Rectangle {
            color: "#4CAF50"  // Màu nền xanh lá cây nhạt
            border.color: "#388E3C"  // Viền xanh lá cây đậm
            radius: 12
            border.width: 2
        }   

        contentItem: Text {
            text: comboBoxImage.currentText
            color: "white"
            // font.pixelSize: parent.height * 0.5
            fontSizeMode: Text.Fit
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
            leftPadding: parent.width * 0.05
        }

        indicator: Rectangle {
            width: comboBoxImage.height * 0.9
            height: comboBoxImage.height * 0.9
            color: "#66BB6A"
            border.color: "#4CAF50"
            border.width: 2
            radius: 12
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: (parent.height - height) / 2
        
            Image {
                source: "qrc:/images/arrow_down.png"
                anchors.centerIn: parent
                width: comboBoxImage.height * 0.6
                height: comboBoxImage.height * 0.6
            }
        }

        popup.y: comboBoxImage.height + componentMargin

        popup.background: Rectangle {
            border.color: "#388E3C"
            radius: 12
            border.width: 2
        }

        delegate: ItemDelegate {
            width: comboBoxImage.width
            contentItem: Text {
                text: modelData
                // font.pixelSize: comboBoxImage.height * 0.3
                fontSizeMode: Text.Fit
                color: comboBoxImage.highlightedIndex === index ? "white" : "black"
            }
            
            background: Rectangle {
                color: comboBoxImage.highlightedIndex === index ? "#388E3C" : "transparent"
                radius: 12
            }
        }

        Component.onCompleted: updateImage()
        onActivated: updateImage()
        
        function updateImage() {
            var yamlFilePath = ":/maps/" + comboBoxImage.currentText + ".yaml"
            mainWindowQML.readYAML(yamlFilePath)
            mapImage.source = Qt.resolvedUrl("../maps/" + mainWindowQML.getYamlValue().image)
            mapResolution = mainWindowQML.getYamlValue().resolution
            mapOrigin = mainWindowQML.getYamlValue().origin

            dashboard.clickedPoints = [];
            hermiteCurveQML.clearLamdmarkPoints();
            updateRobotPose();

            hermiteCurveQML.createCurve();
            canvasMapImage.requestPaint();

            viewModelQML.onImageLoader(mapImage.width, mapImage.height, mapImage.sourceSize.width, mapImage.sourceSize.height);                   

        }
    }

    // Connection status
    Rectangle {
        id: connectionStatus
        height: titleBar.height
        anchors.top: titleBar.top
        anchors.left: parent.left
        anchors.right: comboBoxImage.left
        anchors.leftMargin: parentMargin
        anchors.rightMargin: componentMargin

        radius: 12
        border.width: 2
        border.color: "#BDBDBD"
        color: "#FFFFFF"

        Text {
            text: "Connected"
            color: "#37474F"
            // font.pixelSize: parent.height * 0.5
            fontSizeMode: Text.Fit
            font.bold: true
            anchors.centerIn: parent
        }
    }

    // Logout Button
    Button {
        id: logoutButton
        width: parent.width * 0.18
        height: titleBar.height
        anchors.top: titleBar.top
        anchors.left: titleBar.right
        anchors.leftMargin: componentMargin

        background: Rectangle {
            radius: 12
            border.color: "#272626"
            border.width: 2
        }

        contentItem: Text {
            text: "LOG OUT"
            color: "#37474F"
            // font.pixelSize: parent.height * 0.5
            fontSizeMode: Text.Fit
            wrapMode: Text.WordWrap
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: dashboard.logOutRequested()
    }

    // Close Button
    Button {
        id: closeButton
        height: titleBar.height
        anchors.top: titleBar.top
        anchors.left: logoutButton.right
        anchors.right: parent.right
        anchors.leftMargin: componentMargin
        anchors.rightMargin: parentMargin

        background: Rectangle {
            color: "#D32F2F"
            radius: 12
            border.color: "#B71C1C"
            border.width: 2
        }

        contentItem: Text {
            text: "Close Application"
            color: "white"
            fontSizeMode: Text.Fit
            wrapMode: Text.WordWrap
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        onClicked: Qt.quit()
    }

    // Navigate Button
    CustomButton {
        id: startNavigateButton
        width: (imageCamera.width - componentMargin) * 0.5
        height: imageCamera.height * 0.25
        anchors.left: imageCamera.left
        anchors.bottom: imageCamera.top
        anchors.bottomMargin: componentMargin

        text: "Start \n Navigate"
        normalColor: "#2ecc71" 
        hoverColor: "#27ae60"
        borderColor: "#1e8449"
        onClicked: {
            viewModelQML.sendMoveCommand("start");
        }
    }

    // Stop Navigate Button
    CustomButton {
        id: stopNavigateButton
        width: startNavigateButton.width
        height: startNavigateButton.height
        anchors.right: imageCamera.right
        anchors.bottom: imageCamera.top
        anchors.bottomMargin: componentMargin

        text: "Stop \n Navigate"
        normalColor: "#e74c3c" 
        hoverColor: "#c0392b"
        borderColor: "#962d22"
        onClicked: {
            viewModelQML.sendMoveCommand("stop");
        }        
    }

    // Teleop Joystick
    Rectangle {
        id: teleopJoystick
        width: connectionStatus.width
        height: (parent.height - (parentMargin * 2 + componentMargin * 2 + connectionStatus.height)) / 2
        anchors.top: connectionStatus.bottom
        anchors.left: connectionStatus.left
        anchors.topMargin: componentMargin

        radius: 12
        border.width: 2
        border.color: "#BDBDBD"
        color: "#FFFFFF"
        Component.onCompleted: {
            viewModelQML.sendVelocityCommand(0, 0);
        }
        Text {
            id: teleopJoystickText
            text: "TELEOP JOYSTICK"
            color: "#37474F"
            font.pixelSize: teleopJoystick.height * 0.05
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: componentMargin
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Joystick
        Item {
            id: joystickArea
            width: parent.width * 0.7
            height: width
            anchors.top: teleopJoystickText.bottom
            anchors.topMargin: componentMargin
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: outerCircle
                width: parent.width
                height: width
                radius: width / 2
                color: "#E0E0E0"
                border.color: "#B0BEC5"
                border.width: 2
            }

            Rectangle {
                id: innerCircle
                width: outerCircle.width * 0.3
                height: width
                radius: width / 2
                color: "#2196F3"
                border.color: "#1976D2"
                border.width: 2
                x: (outerCircle.width - width) / 2
                y: (outerCircle.height - height) / 2

                property bool dragging: false
                property var startPosition: Qt.point(0, 0)
            }

            MouseArea {
                id: joystickMouseArea
                anchors.fill: outerCircle
                onPressed: {
                    innerCircle.dragging = true
                    // Cập nhật vị trí ban đầu khi bắt đầu kéo
                    innerCircle.startPosition = Qt.point(innerCircle.x, innerCircle.y)
                }
                
                onPositionChanged: {
                    if (innerCircle.dragging) {
                        var centerX = outerCircle.width / 2
                        var centerY = outerCircle.height / 2
                        var dx = mouseX - centerX
                        var dy = mouseY - centerY
                        var distance = Math.sqrt(dx * dx + dy * dy)
                        var maxDistance = (outerCircle.width - innerCircle.width) / 2

                        if (distance > maxDistance) {
                            var angle = Math.atan2(dy, dx)
                            innerCircle.x = centerX + Math.cos(angle) * maxDistance - innerCircle.width / 2
                            innerCircle.y = centerY + Math.sin(angle) * maxDistance - innerCircle.height / 2
                        } else {
                            innerCircle.x = mouseX - innerCircle.width / 2
                            innerCircle.y = mouseY - innerCircle.height / 2
                        }

                        var innerCenterY = innerCircle.y + innerCircle.height / 2
                        var heightValue = (innerCenterY < centerY) ? 1 : -1

                        var innerCenterX = innerCircle.x + innerCircle.width / 2
                        var widthValue = (innerCenterX < centerX) ? 2 : -2

                        dashboard.linearSpeed = linearSpeedSlider.value * (1 - innerCircle.y / (outerCircle.height / 2 - innerCircle.height / 2));
                        dashboard.angularSpeed = angularSpeedSlider.value * (1 - innerCircle.x / (outerCircle.width / 2 - innerCircle.width / 2));
                        viewModelQML.sendVelocityCommand(dashboard.linearSpeed, dashboard.angularSpeed);
                    }
                }

                onReleased: {
                    innerCircle.dragging = false
                    // Quay về vị trí trung tâm khi thả
                    innerCircle.x = (outerCircle.width - innerCircle.width) / 2
                    innerCircle.y = (outerCircle.height - innerCircle.height) / 2
                    dashboard.linearSpeed = 0;
                    dashboard.angularSpeed = 0;
                    viewModelQML.sendVelocityCommand(dashboard.linearSpeed, dashboard.angularSpeed);
                }
            }
        }

        // Linear Speed Slider
        Row {
            id: linearSpeedRow
            anchors.top: joystickArea.bottom
            anchors.topMargin: componentMargin * 1.5
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Text {
                text: "Linear Speed:"
                font.pixelSize: 14
                color: "#212121"
                anchors.verticalCenter: parent.verticalCenter
            }

            Slider {
                id: linearSpeedSlider
                from: 0
                to: 2
                value: 0.4
                width: 150
                height: 30
                onValueChanged: linearSpeedValue.text = value.toFixed(2)
            }

            Text {
                id: linearSpeedValue
                text: linearSpeedSlider.value.toFixed(2)
                font.pixelSize: 14
                color: "#212121"
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        // Angular Speed Slider
        
        Row {
            id: angularSpeedRow
            anchors.top: linearSpeedRow.bottom
            anchors.topMargin: componentMargin * 0.75
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Text {
                text: "Angular Speed:"
                font.pixelSize: 14
                color: "#212121"
                anchors.verticalCenter: parent.verticalCenter
            }

            Slider {
                id: angularSpeedSlider
                from: 0
                to: 3
                value: 0.6
                width: 150
                height: 30
                onValueChanged: angularSpeedValue.text = value.toFixed(2)
            }

            Text {
                id: angularSpeedValue
                text: angularSpeedSlider.value.toFixed(2)
                font.pixelSize: 14
                color: "#212121"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    // Robot Parameter
    Rectangle {
        id: robotParameter
        width: comboBoxImage.width
        anchors.top: comboBoxImage.bottom
        anchors.bottom: startNavigateButton.top
        anchors.topMargin: componentMargin
        anchors.bottomMargin: componentMargin
        anchors.left: comboBoxImage.left

        radius: 12
        border.width: 2
        border.color: "#BDBDBD"
        color: "#FFFFFF"

        Text {
            id: robotSpeedTitle
            text: "ROBOT SPEED"
            color: "#37474F"
            font.pixelSize: teleopJoystick.height * 0.05
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: componentMargin
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: robotPositionText
            text: "Current Position:"
            font.pixelSize: robotSpeedTitle.font.pixelSize
            font.bold: true
            color: "#212121"
            anchors.top: robotSpeedTitle.bottom
            anchors.left: parent.left
            anchors.topMargin: componentMargin * 2
            anchors.leftMargin: componentMargin
            horizontalAlignment: Text.AlignLeft            
        }

        Column {
            id: positionColumn
            anchors.top: robotPositionText.bottom
            anchors.left: parent.left
            anchors.topMargin: componentMargin * 0.5
            anchors.leftMargin: componentMargin * 1.5
            spacing: 5

            Text { text: " - Pos X: " + (robotPose.position_x); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
            Text { text: " - Pos Y: " + (robotPose.position_y); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
            Text { text: " - Angular: " + (robotPose.angular_yaw); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
        }

        Text {
            id: movementStatusText
            text: "Movement Status:"
            font.pixelSize: robotSpeedTitle.font.pixelSize
            font.bold: true
            color: "#212121"
            anchors.top: positionColumn.bottom
            anchors.left: parent.left
            anchors.topMargin: componentMargin
            anchors.leftMargin: componentMargin
            horizontalAlignment: Text.AlignLeft            
        }

        Column {
            id: movementColumn
            anchors.top: movementStatusText.bottom
            anchors.left: parent.left
            anchors.topMargin: componentMargin * 0.5
            anchors.leftMargin: componentMargin * 1.5
            spacing: 5

            Text { text: " - Estimate Distance: " + (robotPose.position_x).toFixed(2); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
            Text { text: " - Remaining Distance: " + (robotPose.position_y).toFixed(2); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
            Text { text: " - Remaining Time: " + (robotPose.angular_yaw * (180 / Math.PI)).toFixed(2); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
        }

        Text {
            id: velocityText
            text: "Robot Velocity:"
            font.pixelSize: robotSpeedTitle.font.pixelSize
            font.bold: true
            color: "#212121"
            anchors.top: movementColumn.bottom
            anchors.left: parent.left
            anchors.topMargin: componentMargin
            anchors.leftMargin: componentMargin
            horizontalAlignment: Text.AlignLeft            
        }

        Column {
            id: velocityColumn
            anchors.top: velocityText.bottom
            anchors.left: parent.left
            anchors.topMargin: componentMargin * 0.5
            anchors.leftMargin: componentMargin * 1.5
            spacing: 5

            Text { text: " - Linear velocity: " + dashboard.linearSpeed.toFixed(2); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
            Text { text: " - Angular velocity: " + dashboard.angularSpeed.toFixed(2); font.pixelSize: robotSpeedTitle.font.pixelSize * 0.8; color: "#424242" }
        }        
    }

    // Destination
    Rectangle {
        id: destination
        width: connectionStatus.width
        height: teleopJoystick.height

        anchors.bottom: parent.bottom
        anchors.left: teleopJoystick.left
        anchors.bottomMargin: parentMargin

        clip: true

        Rectangle {
            id: titleDestination
            width: goalButtonRectangle.width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: goalButtonRectangle.top
            color: "#1fcf7d"
            Text {
                text: "Destination"
                color: "#37474F"
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        Rectangle {
            id: goalButtonRectangle
            width: parent.width
            height: width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            border.color: "#BDBDBD"
            color: "#FFFFFF"

            Grid {
                id: goalButtonGrid
                columns: 2
                rows: 5
                spacing: parent.height * 0.05
                anchors.fill: parent
                anchors.margins: parent.height * 0.1

                Repeater {
                    model: 10
                    CustomButton {
                        text: "Goal " + (index + 1)
                        width: (goalButtonGrid.width - goalButtonGrid.spacing) / 2
                        height: goalButtonRectangle.height * 0.12
                        onClicked: {
                            viewModelQML.sendGoal(index);
                        }
                    }
                }
                Connections {
                    target: viewModelQML
                    onWaypointsChanged: {
                        canvasMapImage.requestPaint();
                    }
                }
            }
        }
    }

    // Image from Robot's camera
    Rectangle {
        id: imageCamera
        width: comboBoxImage.width
        height: width

        anchors.bottom: parent.bottom
        anchors.left: destination.right
        anchors.bottomMargin: parentMargin
        anchors.leftMargin: componentMargin

        radius: 12
        border.width: 2
        border.color: "#BDBDBD"
        color: "#FFFFFF"

        Text {
            text: "CAMERA"
            color: "#37474F"
            font.pixelSize: parent.height * 0.1
            font.bold: true
            anchors.centerIn: parent
        }
    }

    // Map Rectangle
    Rectangle {
        id: mapImageRectangle
        height: robotParameter.height * 1.3
        anchors.top: robotParameter.top
        anchors.left: robotParameter.right
        anchors.right: parent.right
        anchors.leftMargin: componentMargin
        anchors.rightMargin: parentMargin

        color: "white"
        border.color: "white"
        border.width: 2
        radius: 12
        clip: true

        Connections {
            target: viewModelQML
            onRobotPoseChanged: {
                dashboard.updateRobotPose();                   
            }
        }

        Image {
            id: mapImage
            width: parent.width 
            height: width * (sourceSize.height / sourceSize.width)
            fillMode: Image.PreserveAspectCrop
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            visible: !!mapImage.source
            layer.enabled: true
            layer.smooth: true
            
            Rectangle {
                id: robotImageContainer
                width: dashboard.height * 0.03
                height: width
                rotation: -(robotPose.angular_yaw - 90)
                x: dashboard.robotX - width / 2
                y: dashboard.robotY - height / 2
                color: "transparent"
             
                Shape {
                    id: robotIamge
                    Component.onCompleted: updateRobotPose()
                    ShapePath {
                        fillColor: "#e74c3c"
                        strokeColor: "#c0392b" // Màu viền sẫm hơn để nổi bật
                        strokeWidth: 2
                        capStyle: ShapePath.RoundCap // Làm tròn nét vẽ
                        startX: robotImageContainer.width / 2
                        startY: 0
                        PathLine { x: robotImageContainer.width; y: robotImageContainer.height }
                        PathLine { x: robotImageContainer.width * 0.75; y: robotImageContainer.height * 0.75 }
                        PathLine { x: robotImageContainer.width / 2; y: robotImageContainer.height / 1.5 }
                        PathLine { x: robotImageContainer.width * 0.25; y: robotImageContainer.height * 0.75 }
                        PathLine { x: 0; y: robotImageContainer.height }
                        PathLine { x: robotImageContainer.width / 2; y: 0 }
                    }
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "grey"
            border.width: 5
            radius: 12
        }

        Canvas {
            id: canvasMapImage
            anchors.fill: mapImage

            MouseArea {
                id: imageMouseArea
                anchors.fill: parent
                hoverEnabled: true
                property var metterX: null
                property var metterY: null

                onPressed: {
                    if (dashboard.isCreatingPoint) {
                        hermiteCurveQML.addPoint(mouse.x, mouse.y);
                        dashboard.clickedPoints.push({x: mouse.x, y: mouse.y});
                    } else if (!dashboard.isCreatingPoint && dashboard.selectedPointIndex == -1) {
                        for (var i = 0; i < dashboard.clickedPoints.length; ++i) {
                            var dx = mouse.x - dashboard.clickedPoints[i].x;
                            var dy = mouse.y - dashboard.clickedPoints[i].y;
                            if (Math.sqrt(dx * dx + dy * dy) < 8) {
                                dashboard.selectedPointIndex = i;
                                break;
                            }
                        }

                        if (isClearingLandmarkPoint && dashboard.selectedPointIndex != -1) {
                            dashboard.clickedPoints.splice(dashboard.selectedPointIndex, 1);
                            hermiteCurveQML.removePoint(dashboard.selectedPointIndex);

                            dashboard.selectedPointIndex = -1;
                            isClearingLandmarkPoint = false;
                            isCreatingPoint = true;
                            creatingPointsButton.enabled = true;
                            enableEditingButton.enabled = true;
                            hermiteCurveQML.createCurve();
                            canvasMapImage.requestPaint();

                            if (dashboard.clickedPoints.length == 0) {
                                clearLamdmarkPointButton.enabled = false;
                            }
                        }
                    }

                    if (dashboard.clickedPoints.length != 0) {
                        clearLamdmarkPointButton.enabled = true;
                    }

                    hermiteCurveQML.createCurve();
                    canvasMapImage.requestPaint();
                }

                onPositionChanged: (mouse) => {
                    let [xRatio, yRatio] = [mouse.x / parent.width, mouse.y / parent.height];
                    let [PixelX, PixelY] = [Math.round(xRatio * mapImage.sourceSize.width), Math.round(yRatio * mapImage.sourceSize.height)];
                    
                    metterX = (PixelX * mapResolution + mapOrigin[0]).toFixed(2);
                    metterY = -(PixelY * mapResolution - (mapImage.sourceSize.height * mapResolution + mapOrigin[1])).toFixed(2);

                    pixelText.text = `Pixel: X = ${metterX}, Y = ${metterY}`;

                    if (dashboard.selectedPointIndex != -1 && dashboard.isMovingPoint) {
                        let newX = mouse.x;
                        let newY = mouse.y;

                        if (newX < 0) newX = 0;
                        if (newY < 0) newY = 0;
                        if (newX > mapImage.width) newX = mapImage.width;
                        if (newY > mapImage.height) newY = mapImage.height;

                        dashboard.clickedPoints[dashboard.selectedPointIndex].x = newX;
                        dashboard.clickedPoints[dashboard.selectedPointIndex].y = newY;
                        hermiteCurveQML.updatePoint(dashboard.selectedPointIndex, newX, newY);
                        hermiteCurveQML.createCurve();
                        canvasMapImage.requestPaint();
                    }
                }

                onReleased: {
                    dashboard.selectedPointIndex = -1;
                }
            }

            onPaint: {
                let ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);
                for (let i = 1; i < dashboard.clickedPoints.length; i++) {
                    let point = dashboard.clickedPoints[i];
                    ctx.beginPath();
                    ctx.arc(point.x, point.y, 8, 0, 2 * Math.PI);
                    ctx.fillStyle = "red";
                    ctx.fill();
                }

                let curvePoints = viewModelQML.waypointsQml;
                // let curvePoints = hermiteCurveQML.curvePointsQml;
                ctx.beginPath();
                for (let i = 0; i < curvePoints.length; i++) {
                    let segment = curvePoints[i];
                    let x = segment.x;
                    let y = segment.y;

                    if (i === 0) {
                        ctx.moveTo(x[0] + robotImageContainer.width * 0.75, y[0] - robotImageContainer.width * 0.75);
                    }

                    for (let j = 1; j < x.length; j++) {
                        ctx.lineTo(x[j] + robotImageContainer.width * 0.75, y[j] - robotImageContainer.width * 0.75);
                    }
                }
                ctx.strokeStyle = "blue";
                ctx.stroke();
            }
        }

        Text {
            id: pixelText
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 10
            anchors.rightMargin: 10
            font.pixelSize: 14
            color: "black"
        }
    }

    // Cruise Mode Button
    Button {
        id: cruiseModeButton
        width: height
        anchors.top: mapImageRectangle.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.topMargin: componentMargin
        anchors.bottomMargin: parentMargin
        anchors.rightMargin: parentMargin

        background: Rectangle {
            color: "#2fcdd3"
            radius: 20
            border.color: "#23b2d6"
            border.width: 2
        }

        contentItem: Text {
            text: "Cruise \n Mode"
            color: "grey"
            fontSizeMode: Text.Fit
            wrapMode: Text.WordWrap
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: {
            viewModelQML.sendVelocityCommand(0.0, 0.5)
        }
    }

    // Switch Scenario
    Button {
        id: switchScenarioButton
        width: cruiseModeButton.width
        height: width
        anchors.top: cruiseModeButton.top
        anchors.right: cruiseModeButton.left
        anchors.rightMargin: componentMargin

        background: Rectangle {
            color: "#2fd38f"
            radius: 20
            border.color: "#529e42"
            border.width: 2
        }

        contentItem: Text {
            text: "Switch Scenario"
            color: "grey"
            fontSizeMode: Text.Fit
            wrapMode: Text.WordWrap
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: Qt.quit()
    }

    // Path Tracking Mode Rectangle
    Rectangle {
        id: pathTrackingRectangle
        height: cruiseModeButton.height
        anchors {
                top: cruiseModeButton.top
                right: switchScenarioButton.left
                left: imageCamera.right
                rightMargin: componentMargin
                leftMargin: componentMargin
            }
        border.color: "#BDBDBD"
        border.width: 2
        radius: 12

        Row {
            id: buttonRow
            spacing: parent.width * 0.05
            anchors.verticalCenter: parent.verticalCenter
            anchors.centerIn: parent
            property var diameter: buttonRow.spacing * 3

            // Create Points Button
            RoundButton {
                id: creatingPointsButton
                width: buttonRow.diameter
                height: width
                property real scaleFactor: 1.0
                scale: scaleFactor
                Behavior on scale { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }

                text: dashboard.isCreatingPoint ? "Disable\nCreating" : "Enable\nCreating"
                font.pixelSize: 14

                background: Rectangle {
                    anchors.fill: parent
                    color: dashboard.isCreatingPoint ? "#3F51B5" : "#C5CAE9"
                    radius: width / 2
                    border.color: "black"
                    border.width: 2
                    Behavior on color { ColorAnimation { duration: 200; easing.type: Easing.InOutQuad } }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: creatingPointsButton.scaleFactor = 0.9
                    onReleased: creatingPointsButton.scaleFactor = 1.0
                    onClicked: {
                        dashboard.isCreatingPoint = !dashboard.isCreatingPoint;
                        dashboard.isMovingPoint = !dashboard.isCreatingPoint;
                    }
                }
            }

            // Enable Editing Button
            RoundButton {
                id: enableEditingButton
                width: buttonRow.diameter
                height: width
                property real scaleFactor: 1.0
                scale: scaleFactor
                Behavior on scale { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }

                text: dashboard.isMovingPoint ? "Disable\nEditing" : "Enable\nEditing"
                font.pixelSize: 14

                background: Rectangle {
                    anchors.fill: parent
                    color: dashboard.isMovingPoint ? "#3F51B5" : "#C5CAE9"
                    radius: width / 2
                    border.color: "black"
                    border.width: 2
                    Behavior on color { ColorAnimation { duration: 200; easing.type: Easing.InOutQuad } }
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: enableEditingButton.scaleFactor = 0.9
                    onReleased: enableEditingButton.scaleFactor = 1.0
                    onClicked: {
                        dashboard.isMovingPoint = !dashboard.isMovingPoint;
                        dashboard.isCreatingPoint = !dashboard.isMovingPoint;
                    }
                }
            }

            // Clear Landmark Point Button
            RoundButton {
                id: clearLamdmarkPointButton
                width: buttonRow.diameter
                height: width
                property real scaleFactor: 1.0
                scale: scaleFactor
                Behavior on scale { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }

                text: "Clear\nLandmark"
                font.pixelSize: 14

                background: Rectangle {
                    anchors.fill: parent
                    color: "#F44336"
                    radius: width / 2
                    border.color: "black"
                    border.width: 2
                }

                enabled: false

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: clearLamdmarkPointButton.scaleFactor = 0.9
                    onReleased: clearLamdmarkPointButton.scaleFactor = 1.0
                    onClicked: {
                        isClearingLandmarkPoint = true;
                        isCreatingPoint = false;
                        isMovingPoint = false;
                        creatingPointsButton.enabled = false;
                        enableEditingButton.enabled = false;
                    }
                }
            }

            // Clear Curve Button
            RoundButton {
                id: clearCurveButton
                width: buttonRow.diameter
                height: width
                property real scaleFactor: 1.0
                scale: scaleFactor
                Behavior on scale { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }

                text: "Clear\nCurve"
                font.pixelSize: 14

                background: Rectangle {
                    anchors.fill: parent
                    color: "#F44336"
                    radius: width / 2
                    border.color: "black"
                    border.width: 2
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onPressed: clearCurveButton.scaleFactor = 0.9
                    onReleased: clearCurveButton.scaleFactor = 1.0
                    onClicked: {
                        clearLamdmarkPointButton.enabled = false;
                        dashboard.clickedPoints = [];
                        hermiteCurveQML.clearLamdmarkPoints();
                        hermiteCurveQML.clearCurvePoints();
                        canvasMapImage.requestPaint();
                    }
                }
            }
        }
    }
}
