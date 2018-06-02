import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

Window {
    id:mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Item {
        id: mainItem
        anchors.fill: parent


        Label{
            id:numberOfElementsLable
            text: "Number Of Elements To Serialize"
            anchors.centerIn: parent


        }

        SpinBox{
            id:numberOfElementsSpinBox
            value: 20
            from: 0
            to: 1000000000
            editable: true
            anchors.verticalCenter: numberOfElementsLable.verticalCenter
            anchors.left: numberOfElementsLable.right
            anchors.leftMargin: 20
        }


        Button{
            id:testButton
            anchors.horizontalCenter: numberOfElementsLable.horizontalCenter
            anchors.top: numberOfElementsLable.bottom
            anchors.topMargin: 10
            text:"Benchmark Serialization"
            onClicked: benchmark.benchmarkSerialization(numberOfElementsSpinBox.value)

        }


        Button
        {
            id:startProcessEventsLoopBenchmark
            text: "Start Process Events loop"
            onClicked: benchmark.startBenchmarkProcessEventsBusyLoop()
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

        }


        Button
        {
            id:startEventLoopBenchmark
            text: "Start Event loop benchmark"
            onClicked: benchmark.startBenchmarkEventLoopBusyLoop()
            anchors.left: startProcessEventsLoopBenchmark.right
            anchors.leftMargin: 10
            anchors.verticalCenter:startProcessEventsLoopBenchmark.verticalCenter
        }

        Button
        {
            id:interruptLoop
            text:"Interrupt Loop"
            onClicked: benchmark.intteruptLoop()
            anchors.left: startEventLoopBenchmark.right
            anchors.leftMargin: 10
            anchors.verticalCenter: startProcessEventsLoopBenchmark.verticalCenter
        }


        Button
        {
            id:mapVsStructBemchmarkButton
            text:"Start Map vs Struct Benchmark"
            onClicked: benchmark.startBenchmarkFour()
            anchors.left: parent.left
            anchors.top: parent.top

        }
    }





}
