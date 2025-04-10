import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Shapes 1.12
import QtWebEngine 1.7
import QtGraphicalEffects 1.12
 
Rectangle {
    signal logOutRequested()

    id: dashboard
    anchors.centerIn: parent 
    color: "#F5F5F5"

    property var parentMargin: parent.height * 0.01
    property var componentMargin: parent.height * 0.015

    property var selectedPointIndex: -1

    property bool isCreateLandmark: true
    property bool isClearingLandmark: false
    property bool isNavigationMode: true
    property bool isVirtualWallMode: false

    property var robotPoseMeter: rosHandlingQML.robotPoseMeterQml
    property var robotPosePixel: []

    // Title Bar
    Label {
        id: titleBarLabel
        height: parent.height * 0.05
        width: parent.width * 0.3
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parentMargin

        text: "ROBOT MANAGEMENT SYSTEM"
        color: "#37474F"
        font.bold: true
        font.pixelSize: titleBarLabel.height * 0.6
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        padding: componentMargin

        background: Rectangle {
            color: "#1976D2"
            radius: 12
        }
    }

    // Map selection
    ComboBox {
        id: comboBoxImage
        width: parent.width * 0.13
        height: titleBarLabel.height
        model: fileHandlerQML
        textRole: "fileName"

        anchors.top: titleBarLabel.top
        anchors.right: titleBarLabel.left
        anchors.rightMargin: componentMargin

        background: Rectangle {
            color: "#4CAF50"
            border.color: "#388E3C"
            radius: 12
            border.width: 2
        }

        contentItem: Text {
            text: comboBoxImage.currentText
            color: "white"
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
            readYamlQML.readYaml(yamlFilePath)
            mapImage.source = Qt.resolvedUrl("../maps/" + readYamlQML.getYamlValue().image)

            hermiteCurveQML.clearLandmarkPoints(-1);
            readYamlQML.onImageLoader(mapImage.width, mapImage.height, mapImage.sourceSize.width, mapImage.sourceSize.height, robotImageContainer.width, robotImageContainer.height);                   
            hermiteCurveQML.addPoint(robotPoseMeter[0], robotPoseMeter[1]);
            dashboard.robotPosePixel = rosHandlingQML.getRobotPosePixel(robotPoseMeter[0], robotPoseMeter[1]);
        
            canvasMapImage.requestPaint();
        }
    }

    // Connection status
    Rectangle {
        id: connectionStatus
        height: titleBarLabel.height
        anchors.top: titleBarLabel.top
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
    CustomButton {
        id: logoutButton
        width: (mapImageRectangle.width - titleBarLabel.width - componentMargin * 2) / 2
        height: titleBarLabel.height
        anchors.top: titleBarLabel.top
        anchors.left: titleBarLabel.right
        anchors.leftMargin: componentMargin

        text: "LOG OUT"
        normalColor: "#37474F"
        hoverColor: "#272626"
        borderColor: "#272626"


        onClicked: dashboard.logOutRequested()
    }

    // Close Button
    CustomButton {
        id: closeButton
        height: titleBarLabel.height
        anchors.top: titleBarLabel.top
        anchors.left: logoutButton.right
        anchors.right: parent.right
        anchors.leftMargin: componentMargin
        anchors.rightMargin: parentMargin

        text: "CLOSE APPLICATION"
        normalColor: "#D32F2F"
        hoverColor: "#B71C1C"
        borderColor: "#B71C1C"

        onClicked: Qt.quit()
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
            rosHandlingQML.publishVelocityCommand(0, 0);
        }

        Text {
            id: teleopJoystickText
            text: "TELEOP JOYSTICK"
            color: "#34495E"
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
                    // Update initial position when drag starts
                    innerCircle.startPosition = Qt.point(innerCircle.x, innerCircle.y)
                }
                
                onPositionChanged: {
                    if (hermiteCurveQML.getLandmarkPointCount() != 0) {
                        hermiteCurveQML.clearLandmarkPoints(-1);
                        canvasMapImage.requestPaint();
                    }
                    if (isNavigationMode) {
                        rosHandlingQML.clearWaypoints();
                    }
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

                        var linearSpeed = linearSpeedSlider.value * (1 - innerCircle.y / (centerY - innerCircle.height / 2));
                        var angularSpeed = angularSpeedSlider.value * (1 - innerCircle.x / (centerX - innerCircle.width / 2));

                        rosHandlingQML.publishVelocityCommand(linearSpeed, angularSpeed);
                    }
                }

                onReleased: {
                    innerCircle.dragging = false
                    // Return to center position when drag ends
                    innerCircle.x = (outerCircle.width - innerCircle.width) / 2
                    innerCircle.y = (outerCircle.height - innerCircle.height) / 2
                    rosHandlingQML.publishVelocityCommand(0, 0);
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
                text: linearSpeedSlider.value.toFixed(2) + " m/s"
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
                text: angularSpeedSlider.value.toFixed(2) + " rad/s"
                font.pixelSize: 14
                color: "#212121"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    // Switch Scenario Button
    CustomButton {
        id: switchScenarioButton
        width: imageCamera.width 
        height: imageCamera.height * 0.25
        anchors.left: imageCamera.left
        anchors.bottom: imageCamera.top
        anchors.bottomMargin: componentMargin

        text: isNavigationMode ? "Navigation Mode" : "Custom Path Mode"
        normalColor: isNavigationMode ? "#1fcf7d" : "#3498db"
        hoverColor: isNavigationMode ? "#1abc9c" : "#2980b9"
        borderColor: isNavigationMode ? "#16a085" : "#1f6391"

        onClicked: {
            isNavigationMode = !isNavigationMode;
            hermiteCurveQML.clearLandmarkPoints(-1);
            rosHandlingQML.clearWaypoints();
            virtualWallQML.clearVirtualWall();
            canvasMapImage.requestPaint();
        }
    }

    // Robot Parameter
    Rectangle {
        id: robotParameter
        width: comboBoxImage.width
        anchors.top: comboBoxImage.bottom
        anchors.bottom: switchScenarioButton.top
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
            color: "#34495E"
            font.pixelSize: teleopJoystick.height * 0.05
            font.bold: true
            anchors.top: parent.top
            anchors.topMargin: componentMargin
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Column {
            anchors.top: robotSpeedTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.topMargin: componentMargin
            anchors.leftMargin: componentMargin
            anchors.rightMargin: componentMargin
            spacing: componentMargin

            Repeater {
                model: [
                    {title: "Current Position", items: [
                        {text: "-  Pos X: " + (robotPoseMeter[0].toFixed(2)) + " m"},
                        {text: "-  Pos Y: " + (robotPoseMeter[1].toFixed(2)) + " m"},
                        {text: "-  Angular: " + (robotPoseMeter[2].toFixed(2)) + " degrees"},
                    ]},
                    {title: "Movement Status", items: [
                        {text: "-  Estimate Distance: " + rosHandlingQML.estimateDistanceQml.toFixed(2) + " m"},
                        {text: "-  Remaining Distance: " + rosHandlingQML.remainingDistanceQml.toFixed(2) + " m"},
                    ]},
                    {title: "Robot Velocity", items: [
                        {text: "-  Linear velocity: " + rosHandlingQML.speedQml[0].toFixed(2) + " m/s"},
                        {text: "-  Angular velocity: " + rosHandlingQML.speedQml[1].toFixed(2) + " rad/s"}
                    ]},
                    {title: "Battery Status", items: [
                        {text: "-  Battery Level: Null"},
                        {text: "-  Battery Voltage: Null"},
                        {text: "-  Battery Current: Null"}
                    ]},
                ]

                Column {
                    width: parent.width
                    spacing: componentMargin * 0.5

                    Text {
                        text: modelData.title
                        font.pixelSize: robotSpeedTitle.font.pixelSize * 0.9
                        // font.bold: true
                        color: "#636363"
                        horizontalAlignment: Text.AlignLeft
                        wrapMode: Text.Wrap
                    }

                    Column {
                        width: parent.width
                        spacing: componentMargin * 0.5
                        anchors.left: parent.left
                        anchors.leftMargin: componentMargin * 1.5
                        Repeater {
                            model: modelData.items
                            Text {
                                text: modelData.text
                                font.pixelSize: robotSpeedTitle.font.pixelSize * 0.75
                                color: "#424242"
                                horizontalAlignment: Text.AlignLeft
                                wrapMode: Text.Wrap
                            }
                        }
                    }
                }
            }
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
        anchors.rightMargin: parentMargin

        enabled: isNavigationMode
        clip: true
        opacity: 1

        Behavior on opacity {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        onEnabledChanged: opacity = isNavigationMode ? 1 : 0.7

        Rectangle {
            id: titleDestination
            width: goalButtonRectangle.width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.bottom: goalButtonRectangle.top
            color: "#1fcf7d"
            Text {
                text: "Destination"
                color: "#34495E"
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
                spacing: parent.height * 0.06
                anchors.fill: parent
                anchors.margins: parent.height * 0.08

                Repeater {
                    model: 10
                    CustomButton {
                        normalColor: "#F48FB1"
                        hoverColor: "#e76993"
                        borderColor: "#e07fa0"
                        textColor: "#EAEAEA"
                        text: "Goal " + (index + 1)
                        width: (goalButtonGrid.width - goalButtonGrid.spacing) / 2
                        height: goalButtonRectangle.height * 0.12
                        onClicked: {
                            rosHandlingQML.publishGoal(index);
                        }
                    }
                }
                Connections {
                    target: rosHandlingQML
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

        WebEngineView {
            id: webView
            anchors.fill: parent
            url: "http://192.168.62.138:8080/stream?view=topic&topic=/armbot_rgb_camera/image_raw"  // URL stream
            onLoadingChanged: {
                if (loadRequest.status === WebEngineView.LoadSucceeded) {
                    imageCamera.visible = true
                    webView.visible = true
                    // Inject CSS
                    var css = `
                        var img = document.getElementsByTagName('img')[0];
                        if (img) {
                            img.style.width = '${imageCamera.width}px';
                            img.style.height = '${imageCamera.height}px';
                            img.style.objectFit = 'contain';
                            img.style.display = 'block';
                            img.style.margin = '0 auto';
                        }
                    `
                    webView.runJavaScript(css, function(result) {
                        console.log("CSS injection result:", result)
                    })
                } else if (loadRequest.status === WebEngineView.LoadFailed) {
                    console.log("Failed to load image stream:", loadRequest.errorString)
                }
            }
        }
    }

    // Map Rectangle
    Rectangle {
        id: mapImageRectangle
        height: robotParameter.height * 1.34
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

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "grey"
            border.width: 5
            radius: 12
            z: 4
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
            z: 1
        }
    
        Rectangle {
            id: robotImageContainer
            width: dashboard.height * 0.02
            height: width
            rotation: -(robotPoseMeter[2] - 90)

            Connections {
                target: rosHandlingQML
                onRobotPoseChanged: {
                    dashboard.robotPosePixel = rosHandlingQML.getRobotPosePixel(robotPoseMeter[0], robotPoseMeter[1]);
                }
            }
            
            x: dashboard.robotPosePixel[0] - width / 2
            y: dashboard.robotPosePixel[1] - height / 2 - (-mapImageRectangle.height / 2 + mapImage.height / 2)

            color: "transparent"
            z: 3    

            Shape {
                id: robotIamge
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

        Canvas {
            id: canvasMapImage
            anchors.fill: mapImage
            z: 2

            MouseArea {
                id: imageMouseArea
                anchors.fill: parent
                hoverEnabled: true

                onPressed: {
                    if (isCreateLandmark && !isNavigationMode) {
                        var meterValues = readYamlQML.getConvertPixelToMeter(mouse.x, mouse.y);
                        hermiteCurveQML.addPoint(meterValues[0], meterValues[1]);
                    } else if (!isCreateLandmark && selectedPointIndex == -1) {
                        var landmarkPointsList = hermiteCurveQML.getLandmarkPointsList();
                        for (var i = 1; i < hermiteCurveQML.getLandmarkPointCount(); ++i) {
                            var dx = mouse.x - landmarkPointsList[i][0];
                            var dy = mouse.y - landmarkPointsList[i][1];
                            if (Math.sqrt(dx * dx + dy * dy) < 8) {
                                selectedPointIndex = i;
                                break;
                            }
                        }
                    }

                    if (isVirtualWallMode && isNavigationMode) {
                        var meterValues = readYamlQML.getConvertPixelToMeter(mouse.x, mouse.y);
                        virtualWallQML.addVirtualWallPoint(meterValues[0], meterValues[1]);
                    }

                    if (isClearingLandmark && selectedPointIndex != -1) {
                        hermiteCurveQML.clearLandmarkPoints(selectedPointIndex);
                        selectedPointIndex = -1;
                    }

                    hermiteCurveQML.createCurve();
                    canvasMapImage.requestPaint();
                }

                onPositionChanged: (mouse) => {
                    let newX = mouse.x;
                    let newY = mouse.y;

                    if (newX < 0) newX = 0;
                    if (newY < 0) newY = 0;
                    if (newX > mapImage.width) newX = mapImage.width;
                    if (newY > mapImage.height) newY = mapImage.height;

                    var meterValues = readYamlQML.getConvertPixelToMeter(newX, newY);
                    pixelText.text = `Pixel: X = ${meterValues[0].toFixed(2)}, Y = ${meterValues[1].toFixed(2)}`; 
                    if (selectedPointIndex != -1 && !isCreateLandmark) {
                        hermiteCurveQML.updatePoint(selectedPointIndex, meterValues[0], meterValues[1]);
                        hermiteCurveQML.createCurve();
                        canvasMapImage.requestPaint();
                    }
                }

                onReleased: {
                    selectedPointIndex = -1;
                }
            }

            onPaint: {
                let ctx = getContext("2d");
                ctx.clearRect(0, 0, width, height);
                let curvePoints = [];

                function drawPath(points, pathColor) {
                    if (!points || points.length === 0) return;
                    ctx.beginPath();
                    for (let i = 0; i < points.length; i++) {
                        let point = points[i];
                        let x = point[0];
                        let y = point[1];
                        if (i === 0) {
                            ctx.moveTo(x, y);
                        } else {
                            ctx.lineTo(x, y);
                        }
                    }
                    ctx.strokeStyle = pathColor;
                    ctx.stroke();
                }

                function drawPoint(x, y) {
                    if (x === undefined || y === undefined) return;
                    ctx.beginPath();
                    ctx.arc(x, y, 6, 0, 2 * Math.PI);
                    ctx.fillStyle = "e76993";
                    ctx.fill();
                }

                function drawLandmarkPoints(points) {
                    if (!points || points.length === 0) return;
                    for (let i = 1; i < points.length; i++) {
                        let point = points[i];
                        if (point && point[0] !== undefined && point[1] !== undefined) {
                            drawPoint(point[0], point[1]);
                        }
                    }
                }

                if (isNavigationMode) {
                    curvePoints = rosHandlingQML.waypointsQml;
                    if (curvePoints.length > 0) {
                        drawPath(curvePoints, "blue");
                        drawPoint(curvePoints[curvePoints.length - 1][0], curvePoints[curvePoints.length - 1][1]);
                    }

                    var pathSize = virtualWallQML.virtualWallPathSize;
                    if (pathSize > 0) {
                        for (var i = 0; i < pathSize; ++i) {
                            var path = virtualWallQML.getVirtualWallPath(i);
                            drawPath(path, "red");
                        }
                        rosHandlingQML.publishVirtualWall();                            
                    }

                } else if (!isNavigationMode && !isVirtualWallMode) {
                    hermiteCurveQML.getLandmarkPointCount() === 0 && hermiteCurveQML.addPoint(robotPoseMeter[0], robotPoseMeter[1]);                    
                    curvePoints = hermiteCurveQML.curvePointsQml;
                    if (curvePoints.length > 0) {
                        drawPath(curvePoints, "green");
                        drawLandmarkPoints(hermiteCurveQML.getLandmarkPointsList());
                    }
                }
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
            z: 4
        }
    }

    // Custom Path Handling
    Item {
        id: customPathItem
        height: startNavigateButton.height
        width: mapImageRectangle.width * 0.4
        anchors {
            top: startNavigateButton.top
            left: imageCamera.right
            leftMargin: componentMargin
        }

        enabled: !isNavigationMode
        opacity: !isNavigationMode ? 1 : 0.7

        Behavior on opacity {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        onEnabledChanged: opacity = !isNavigationMode ? 1 : 0.7

        Label {
            id: customPathLabelTitle
            anchors.top: parent.top
            anchors.left: parent.left
            height: parent.height * 0.2

            text: "Custom Path Handling"
            color: "#FFFFFF"
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            padding: componentMargin

            background: Rectangle {
                color: "#3498db"
            }
        }

        Rectangle {
            id: customPathRectangleHandling
            anchors.top: customPathLabelTitle.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            color: "#ffffff"
            border.color: "#3498db"
            border.width: 2

            Row {
                id: buttonRow
                spacing: parent.width * 0.12
                anchors.verticalCenter: parent.verticalCenter
                anchors.centerIn: parent
                property var diameter: buttonRow.spacing * 1.4

                // Enable Editing Button
                CustomButton {
                    id: dragLandmarkButton
                    width: buttonRow.diameter
                    height: width
                    text: (!isCreateLandmark && !isClearingLandmark) ? "Drag is \nOn" : "Drag is \nOff"

                    isRound: true
                    hasGlow: true
                    isOn: !isCreateLandmark && !isClearingLandmark

                    normalColor: isOn ? "#3498DB" : "#B0BEC5"
                    hoverColor: isOn ? "#CFD8DC" : "#2E86C1"
                    borderColor: isOn ? "#2471A3" : "#90A4AE"
                    glowColor: isOn ? "#3498DB" : "#B0BEC5"

                    onClicked: {
                        if (isClearingLandmark) {
                            isClearingLandmark = false;
                            isCreateLandmark = false;
                        } else {
                            isCreateLandmark = !isCreateLandmark;
                        }
                    }
                }

                // Clear Landmark Point Button
                CustomButton {
                    id: clearLandmarkButton
                    width: buttonRow.diameter
                    height: width
                    text: (!isCreateLandmark && isClearingLandmark) ? "Clear is \nOn" : "Clear is \nOff"

                    isRound: true
                    hasGlow: true
                    isOn: isClearingLandmark

                    normalColor: isOn ? "#F39C12" : "#B0BEC5"
                    hoverColor: isOn ? "#CFD8DC" : "#D68910"
                    borderColor: isOn ? "#B9770E" : "#90A4AE"
                    glowColor: isOn ? "#F39C12" : "#B0BEC5"

                    onClicked: {
                        isClearingLandmark = !isClearingLandmark;
                        if (isClearingLandmark && isCreateLandmark) {
                            isCreateLandmark = false;
                        } else if (!isClearingLandmark && !isCreateLandmark) {
                            isCreateLandmark = true;
                        }
                    }
                }

                // Clear Curve Button
                CustomButton {
                    id: clearCurveButton
                    width: buttonRow.diameter
                    height: width
                    text: "Clear\nCurve"

                    isRound: true

                    normalColor: "#E74C3C"
                    hoverColor: "#C0392B"
                    borderColor: "#A93226"

                    onClicked: {
                        hermiteCurveQML.clearLandmarkPoints(-1);
                        canvasMapImage.requestPaint();
                    }
                }
            }
        }
    }
    
    // Virtual Wall Handling
    Item {
        id: virtualWallItem
        width: customPathItem.width * 0.7
        height: customPathRectangleHandling.height
        anchors {
            bottom: customPathItem.bottom
            left: customPathItem.right
            leftMargin: componentMargin
        }

        enabled: isNavigationMode
        opacity: isNavigationMode ? 1 : 0.7

        Behavior on opacity {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        onEnabledChanged: opacity = isNavigationMode ? 1 : 0.7

        Label {
            id: virtualWallLabelTitle
            height: customPathLabelTitle.height
            anchors.top: parent.top
            width: parent.width

            text: "Virtual Wall Handling"
            color: "#333333"
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            padding: componentMargin

            background: Rectangle {
                color: "#968f2f"
            }
        }

        Rectangle {
            id: virtualWallRectangleHandling
            anchors.top: virtualWallLabelTitle.bottom
            width: parent.width
            anchors.bottom: parent.bottom

            color: "#ffffff"
            border.color: "#968f2f"
            border.width: 2

            Row {
                id: virtualWallButtonRow
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.leftMargin: componentMargin
                anchors.rightMargin: componentMargin
                spacing: componentMargin


                CustomButton {
                    text: "Create\nVirtual Wall"

                    hasGlow: true
                    isOn: isVirtualWallMode

                    normalColor: "#16A085"
                    hoverColor: "#1ABC9C"
                    borderColor: "#0E6655"

                    onClicked: {
                        isVirtualWallMode = !isVirtualWallMode;
                    }
                }

                CustomButton {
                    text: "Clear\nVirtual Wall"

                    normalColor: "#6C3483"
                    hoverColor: "#8E44AD"
                    borderColor: "#4A235A"

                    onClicked: {
                        virtualWallQML.clearVirtualWall();
                        canvasMapImage.requestPaint();
                        rosHandlingQML.publishVirtualWall();
                    }
                }
            }
        }
    }

    // Start Button
    CustomButton {
        id: startNavigateButton
        width: stopNavigateButton.width
        height: width
        anchors.top: stopNavigateButton.top
        anchors.right: stopNavigateButton.left
        anchors.rightMargin: componentMargin

        isRound: true
        text: "Start \n Navigate"
        normalColor: "#4CAF50" 
        hoverColor: "#388E3C"
        borderColor: "#2E7D32"
        onClicked: {
            if (isNavigationMode) {
            rosHandlingQML.publishMoveCommand("start");
            } else {
                rosHandlingQML.publishHermitePath();
            }
        }
    }

    // Stop Button
    CustomButton {
        id: stopNavigateButton
        width: height
        anchors.top: mapImageRectangle.bottom
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.topMargin: componentMargin
        anchors.bottomMargin: parentMargin
        anchors.rightMargin: componentMargin * 3

        isRound: true

        text: "Stop \n Navigate"
        normalColor: "#D32F2F" 
        hoverColor: "#B71C1C"
        borderColor: "#9A0007"
        onClicked: {
            rosHandlingQML.publishMoveCommand("stop");
        }        
    }
}

