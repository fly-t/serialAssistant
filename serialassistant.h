#pragma once

#include <QtWidgets/QWidget>
#include "ui_serialassistant.h"

#include <QSerialPort>        //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include<qmessagebox.h>

class serialAssistant : public QWidget
{
    Q_OBJECT

public:
    serialAssistant(QWidget* parent = Q_NULLPTR) ;
    ~serialAssistant() {};
   
  
    QSerialPort* serialPort;
    QSerialPort::BaudRate baudRate{};
    QSerialPort::StopBits stopBits{};
    QSerialPort::DataBits dataBits{};
    QSerialPort::Parity checkBits{};

public slots:
    void start();
    void stop();
    void clear();
    void send();
    void receive();


private:
    Ui::serialAssistantClass ui;
};
