#include "serialassistant.h"
#include <iostream>



serialAssistant::serialAssistant(QWidget *parent)
    : QWidget(parent)
{
    
    ui.setupUi(this);

    serialPort = new QSerialPort(this);
    
    // get and show  ports
    for each (const QSerialPortInfo &info in QSerialPortInfo::availablePorts())
    {
        ui.serialPortComBox->addItem(info.portName());
    }
    
    connect(serialPort, SIGNAL(readyRead()),this, SLOT(receive()));
}

void serialAssistant::start() {
    if (ui.baudRatCombox->currentText() == "4800") {
        serialAssistant::baudRate = QSerialPort::Baud4800;
    }
    else if (ui.baudRatCombox->currentText() == "9600") {
        serialAssistant::baudRate = QSerialPort::Baud9600;
    }
    else if (ui.baudRatCombox->currentText() == "115200") {
        serialAssistant::baudRate = QSerialPort::Baud115200;
    }


    if (ui.dataBitComBox->currentText() == "5") {
        serialAssistant::dataBits = QSerialPort::Data5;
    }
    else if (ui.dataBitComBox->currentText() == "6") {
        serialAssistant::dataBits = QSerialPort::Data6;
    }
    else if (ui.dataBitComBox->currentText() == "7") {
        serialAssistant::dataBits = QSerialPort::Data7;
    }
    else if (ui.dataBitComBox->currentText() == "8") {
        serialAssistant::dataBits = QSerialPort::Data8;
    }


    if (ui.stopBitComBox->currentText() == "1") {
        serialAssistant::stopBits = QSerialPort::OneStop;
    }
    else if (ui.stopBitComBox->currentText() == "1.5") {
        serialAssistant::stopBits = QSerialPort::OneAndHalfStop;
    }
    else if (ui.stopBitComBox->currentText() == "2") {
        serialAssistant::stopBits = QSerialPort::TwoStop;
    }

    if (ui.checkComBox->currentText() == "none") {
        serialAssistant::checkBits = QSerialPort::NoParity;
    }
   
    serialPort->setPortName(ui.serialPortComBox->currentText());
    serialPort->setBaudRate(serialAssistant::baudRate);
    serialPort->setDataBits(serialAssistant::dataBits);
    serialPort->setStopBits(serialAssistant::stopBits);
    serialPort->setParity(serialAssistant::checkBits);
 
   // std::cout << serialAssistant::baudRate << std::endl;
    // std::cout << serialAssistant::dataBits << std::endl;
    // std::cout << serialAssistant::stopBits << std::endl;
    // std::cout << serialAssistant::checkBits << std::endl;

    // chek status 
    if (serialPort->open(QIODevice::ReadWrite) == true) {
       
        QMessageBox::information(this, "tip", "ok");
    }
    else {
        QMessageBox::critical(this, "tip", "fail");
    }

}

void serialAssistant::stop()
{
    QMessageBox::information(this, "tip", "closed");
    serialPort->close();
}

void serialAssistant::clear()
{
    ui.sendLineEdit->clear();
}

void serialAssistant::send()
{
    serialPort->write(ui.sendLineEdit->text().toLocal8Bit().data());
    //std::cout << ui.sendLineEdit->text().toLocal8Bit().data() << std::endl;
}

void serialAssistant::receive()
{
    QString buffer;
    buffer =  QString(serialPort->readAll());
    ui.receivePlainTextEdit->appendPlainText(buffer);
    //std::cout << buffer.toStdString() << std::endl;
}
