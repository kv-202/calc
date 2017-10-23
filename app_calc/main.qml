import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import calc 1.0

ApplicationWindow
{
    minimumHeight: 300
    minimumWidth: 500

    property int currentAction: CalcModel.Add

    function numberClick(text)
    {
        if ((currentNumber.text.length == 1) && (currentNumber.text[0] == '0'))
            currentNumber.text = text;
        else
            currentNumber.text = currentNumber.text + text;
    }

    function actionClick(text, value)
    {
        oldNumber.text = currentNumber.text;
        currentNumber.text = "0";
        action.text = text;
        currentAction = value;
    }

    function cancelClick()
    {
        currentNumber.text = oldNumber.text;
        oldNumber.text = "0";
        action.text = "+";
    }

    function dotClick()
    {
        if (currentNumber.text.search("[" + Qt.locale().decimalPoint + "]") == -1)
            currentNumber.text = currentNumber.text + Qt.locale().decimalPoint;
    }

    function getAction(value)
    {
        switch (value)
        {
            case CalcModel.Add:
                return "+";
            case CalcModel.Sub:
                return "-";
            case CalcModel.Div:
                return "/";
            case CalcModel.Mul:
                return "*";
            default:
                return " ";
        }
    }

    Item
    {
        anchors.fill: parent

        Item
        {
            anchors.left: parent.left
            anchors.right: rightTopRect.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            ListView
            {
                id: listView

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: tasks.top

                delegate:
                MouseArea
                {
                    property var waitColor: "#777777"

                    width: listView.width
                    height: taskCount.height

                    Row
                    {
                        anchors.fill: parent

                        Text { text: a; color: wait? waitColor: "#00FF00" }
                        Text { text: getAction(action); color: wait? waitColor: "#000000" }
                        Text { text: b; color: wait? waitColor: "#00FF00" }
                        Text { text: "="; color: wait? waitColor: "#000000" }
                        Text
                        {
                            text: wait? "wait...": (error.length? error: result)
                            color: error.length? "#FF0000": (wait? waitColor: "#0000FF")
                        }
                    }

                    onClicked:
                    {
                        if (!wait && !error.length)
                            currentNumber.text = result;
                    }
                }

                model: calcModel.historyModel

                onCountChanged: listView.positionViewAtEnd();
            }

            Row
            {
                id: tasks

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                Label { text: "Task queue size: " }
                Label
                {
                    id: taskCount
                    text: calcModel.requestCount
                }
            }
        }

        Column
        {
            id: rightTopRect

            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom

            Row
            {
                Label
                {
                    id: action
                    text: "+"
                }

                Label
                {
                    id: oldNumber
                    text: "0"
                }
            }

            TextField
            {
                id: currentNumber

                anchors.left: parent.left
                anchors.right: parent.right

                text: "0"
                readOnly: true
            }

            Row
            {
                Column
                {                  
                    Button { text: "7"; onClicked: numberClick(text) }
                    Button { text: "4"; onClicked: numberClick(text) }
                    Button { text: "1"; onClicked: numberClick(text) }
                    Button { text: "0"; onClicked: numberClick(text) }
                }

                Column
                {
                    Button { text: "8"; onClicked: numberClick(text) }
                    Button { text: "5"; onClicked: numberClick(text) }
                    Button { text: "2"; onClicked: numberClick(text) }
                    Button { text: "С"; onClicked: cancelClick() }
                }

                Column
                {
                    Button { text: "9"; onClicked: numberClick(text) }
                    Button { text: "6"; onClicked: numberClick(text) }
                    Button { text: "3"; onClicked: numberClick(text) }
                    Button { text: Qt.locale().decimalPoint; onClicked: dotClick() }
                }

                Column
                {
                    Button { text: "/"; onClicked: actionClick(text, CalcModel.Div) }
                    Button { text: "*"; onClicked: actionClick(text, CalcModel.Mul) }
                    Button { text: "+"; onClicked: actionClick(text, CalcModel.Add) }
                    Button { text: "-"; onClicked: actionClick(text, CalcModel.Sub) }
                }
            }

            Row
            {
                Label { text: "Duration (sec.): " }

                TextField
                {
                    id: duration
                    validator: IntValidator {bottom: 0; top: 60;}
                    text: "0"
                }

                Button
                {
                    text: "="
                    onClicked:
                    {
                        var local = Qt.locale();
                        var a = Number.fromLocaleString(local, oldNumber.text);
                        var b = Number.fromLocaleString(local, currentNumber.text);
                        var t = Number.fromLocaleString(local, duration.text);
                        calcModel.onCalculate(a, b, currentAction, t);

                    }
                }
            }
        }
    }
}
