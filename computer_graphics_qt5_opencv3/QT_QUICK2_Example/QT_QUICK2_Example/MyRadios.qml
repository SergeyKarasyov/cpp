import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item
{

    ColumnLayout
    {
        anchors.centerIn: parent

        RadioButton
        {
            text: "Video"
        }
        RadioButton
        {
            text: "Image"
        }
    }
}
