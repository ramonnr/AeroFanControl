import QtQuick 2.0
import QtCharts 2.0

Item {
    Connections{
        target: ECData
        onFanSpeed:{
            var f0name = "fan0: "
            var f1name = "fan1: "
            if(fan === 0){
                fan0.append(fan0.count,speed)
                fan0.name = f0name + speed
            }
            if(fan ===1){
                fan1.append(fan1.count,speed)
                fan1.name = f1name + speed
            }
            if(Math.max(fan0.count,fan1.count) > xaxis.max){xaxis.max++}
        }
        onCpuTemp:{
            var cpuname = "temp: "
            cpuTemp.append(cpuTemp.count,temp)
            cpuTemp.name = cpuname + temp
        }
    }
    ChartView{
        anchors.fill:parent
        animationOptions: ChartView.NoAnimation
        ValueAxis{
            id: yaxisFan
            min:0
            max: 4000
        }
        ValueAxis{
            id: yaxisTemp
            min:0
            max: 120
        }

        ValueAxis{
            id: xaxis
            min: 0
            max: 3
        }
        LineSeries{
            id: fan0
            name: "fan0"
            axisX: xaxis
            axisY: yaxisFan
        }
        LineSeries{
            id: fan1
            name: "fan1"
            axisX: xaxis
            axisY: yaxisFan
            color: "Red"
        }
        LineSeries{
            id: cpuTemp
            name: "cpu temp"
            axisX: xaxis
            axisYRight: yaxisTemp
        }
    }
}
