import QtQuick
import QtCharts
import QtQuick.Window

Rectangle {
    id: root
    width: 800
    height: 600

    property int count: 0
    readonly property int maxIndexCount: 10
    property int indexCount: maxIndexCount
    readonly property int maxPoints: 1000

    Rectangle {    
        id: plotArea
        width: parent.width
        height: (parent.height / 2)

        color: "darkgrey"

        // anchors.top: parent.top

        ChartView {
            id: chartView
            title: "Revolute joint angle:"
            anchors.fill: parent
            antialiasing: true

            ValueAxis {
                id: axisEmpty
            }


            ValueAxis {
                id: axisYRange
                min: -90
                max: 270
            }

            ValueAxis {
                id: axisXRange
                min: 0
                max: maxPoints
            }

            LineSeries {
                name: "Angle"

                axisX: axisXRange
                axisY: axisYRange
                useOpenGL: true

                Component.onDestruction: {
                    axisX = axisEmpty
                    axisY = axisEmpty
                }
            }
        }
    }


    Item {
        id: pyhsicsMain
        width: parent.width
        height: (root.height - plotArea.height)

        x: 0
        y: plotArea.height


        Revolute {
            id: revolute
            width: parent.width
            height: parent.height
        }
    }

    Timer {
        interval: 100; running: true; repeat: true
        onTriggered: {
            // console.log("onAngleChanged - getJointAngle: " + revolute.getJointAngle() + " - getJointSpeed: " + revolute.getJointSpeed())

            var lineSeries = chartView.series(0);
            if (!lineSeries) {
                console.log("No line series")
            }

            if(count < maxPoints) {
                lineSeries.append(count, revolute.getJointAngle());                
            } else {
                lineSeries.remove(0)
                lineSeries.append(count, revolute.getJointAngle());
                if(indexCount <= 0)
                {
                    axisXRange.min = count - maxPoints
                    axisXRange.max = count
                    indexCount = maxIndexCount
                } else {
                    indexCount--
                }   
            }

            count++
        }
    }
}
