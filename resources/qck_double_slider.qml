import QtQuick 2.0
import QtQuick.Controls 2.1

Item {
    id: page
    width: 460
    height: 20

    signal first_moved(real val)
    signal second_moved(real val)
    function setFirst(val) {
        slider.first.value = val
    }
    function setSecond(val) {
        slider.second.value = val
    }
    Rectangle {
        color: "#305A7F"
        anchors.fill: parent
    }

    RangeSlider {
        id: slider
        second.value: 50
        /*orientation: RangeSlider.NoSnap*/
        wheelEnabled: true
        live: true
        from: 0
        anchors.fill: parent
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        to: 215
        padding: 6
        hoverEnabled: false
        first.handle.height: 20
        first.handle.width: 20
        second.handle.height: 20
        second.handle.width: 20

        first.onValueChanged: page.first_moved(first.value)
        second.onValueChanged: page.second_moved(second.value)
        background: Rectangle{
            x: slider.leftPadding
            y: slider.topPadding + slider.availableHeight/2 - height /2
            width: slider.availableWidth

            implicitHeight: 4
            height: implicitHeight
            radius: 2


            Rectangle{
                color: "white"
                id: section1
                radius: 2
                height: parent.height
                width: slider.first.visualPosition*parent.width
            }

            Rectangle{
                color: "#6A8BA8"
                radius: 2
                id: section2
                x: slider.first.visualPosition * parent.width
                height: parent.height
                width: slider.second.visualPosition*parent.width -x
            }

            Rectangle{
                color: "white"
                radius: 2
                border.width: 0
                id: section3
                x: slider.second.visualPosition * parent.width
                height: parent.height
                width: parent.width -x
            }
        }
    }
}

/*##^##
Designer {
    D{i:1;invisible:true}
}
##^##*/
