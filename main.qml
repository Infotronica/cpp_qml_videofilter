import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtMultimedia 5.9
import MyAbstractVideoFilter.CPP 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600
    //visibility: Window.Maximized

    Camera {
        id: camera
        deviceId: QtMultimedia.availableCameras[0].deviceId

        exposure {
            exposureCompensation: -1.0
            exposureMode: Camera.ExposureNightPortrait
        }
    }

    MyAbstractVideoFilter {
        id: myAbstractVideoFilter
    }

    VideoOutput {
        anchors.fill: parent
        source: camera
        autoOrientation: true
        filters: [ myAbstractVideoFilter ]
    }
}
