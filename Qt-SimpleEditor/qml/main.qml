import QtQuick 2.3
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Simple Editor")

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: newAction }
            MenuItem { action: exitAction }
        }
        Menu {
            title: qsTr("&Edit")
            MenuItem { action: cutAction }
            MenuItem { action: copyAction }
            MenuItem { action: pasteAction }
            MenuSeparator {}
            MenuItem { action: selectAllAction }
        }
    }

    toolBar: ToolBar {
        Row {
            anchors.fill: parent
            ToolButton { action: newAction }
            ToolButton { action: cutAction }
            ToolButton { action: copyAction }
            ToolButton { action: pasteAction }
        }
    }

    TextArea {
        id: textArea
        anchors.fill: parent
    }

    Action {
        id: exitAction
        text: qsTr("E&xit")
        onTriggered: Qt.quit()
    }
    Action {
        id: newAction
        text: qsTr("New")
        iconSource: "qrc:/images/copy.ico"
        onTriggered: {
            textArea.text = "";
        }
    }
    Action {
        id: cutAction
        text: qsTr("Cut")
        iconSource: "qrc:/images/copy.ico"
        onTriggered: textArea.cut()
    }
    Action {
        id: copyAction
        text: qsTr("Copy")
        iconSource: "qrc:/images/copy.ico"
        onTriggered: textArea.copy()
    }
    Action {
        id: pasteAction
        text: qsTr("Paste")
        iconSource: "qrc:/images/copy.ico"
        onTriggered: textArea.paste()
    }
    Action {
        id: selectAllAction
        text: qsTr("Select All")
        onTriggered: textArea.selectAll()
    }
}
