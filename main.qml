import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import BangbooTranslater
import QMLUtils

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Bangboo")
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            Text {
                text: "输入:"
            }
            Button {
                text: "粘贴"
                onClicked: inputTextArea.text = QMLUtils.clipboardGetText()
            }
            Button {
                text: "清空"
                onClicked: inputTextArea.text = ""
            }
        }

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentHeight: inputTextArea.height
            clip: true
            TextArea {
                id: inputTextArea
                focus: true
                width: parent.width
                wrapMode: Text.Wrap
            }
        }
        RowLayout {
            id: buttonsLayout
            Layout.fillWidth: true
            Button {
                id: encodeButton
                Layout.fillWidth: true
                text: "编码"
                onClicked: {
                    buttonsLayout.enabled = false
                    translater.mode = BangbooTranslater.Encode
                    translater.start()
                }
            }
            Button {
                id: decodeButton
                Layout.fillWidth: true
                text: "解码"
                onClicked: {
                    buttonsLayout.enabled = false
                    translater.mode = BangbooTranslater.Decode
                    translater.start()
                }
            }
        }
        RowLayout {
            Text {
                text: "输出:"
            }
            Button {
                text: "复制"
                onClicked: QMLUtils.clipboardSetText(outputTextArea.text)
            }
            Text {
                text: outputTextArea.text.length
            }
        }
        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentHeight: outputTextArea.height
            clip: true
            TextArea {
                id: outputTextArea
                width: parent.width
                readOnly: true
                selectByMouse: true
                wrapMode: Text.Wrap
            }
        }
    }

    Dialog {
        id: dialog
        anchors.centerIn: parent
        focus: true
        modal: true
        standardButtons: Dialog.Ok
        Text {
            id: dialogText
            wrapMode: Text.Wrap
        }

        function show(msg) {
            dialogText.text = msg
            open();
        }
    }

    BangbooTranslater {
        id: translater
        input: inputTextArea.text
        onError: function(msg) { dialog.show(msg); buttonsLayout.enabled = true }
        onTranslateFinished: function(result) { outputTextArea.text = result; buttonsLayout.enabled = true }
    }
}
