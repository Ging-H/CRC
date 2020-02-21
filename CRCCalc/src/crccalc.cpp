#include "crccalc.h"
#include <iostream>
#include <stdio.h>

CrcCalc::CrcCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CrcCalc)
{
    ui->setupUi(this);
    this->listCRC(ui->cbbSelect);
    ui->txtEdit->setPlaceholderText("只能输入Hex字符串与空格: 0-9,a-f,A-F,");
}

CrcCalc::~CrcCalc()
{
    delete ui;
}

/* 监控文本,限制只能输入十六进制字符 槽函数 */
void CrcCalc::on_txtEdit_textChanged()
{
    bool isMatch = this->isHexString(ui->txtEdit->toPlainText());
    if(!isMatch){
        QString tmp;
        disconnect(this->ui->txtEdit,SIGNAL(textChanged()),this,SLOT(on_txtEdit_textChanged()));
        tmp = ui->txtEdit->toPlainText();
        tmp.replace(QRegExp("[^a-f0-9A-F ]"), "");
        ui->txtEdit->setPlainText(tmp);
        ui->txtEdit->moveCursor(QTextCursor::End);
        connect(this->ui->txtEdit,SIGNAL(textChanged()),this,SLOT(on_txtEdit_textChanged()));
    }
}

/* 检查src中字符是否符合Hex规则表达式 */
bool CrcCalc::isHexString(QString src)
{
    bool isMatch = true;
    QRegExp regExp("[a-f0-9A-F ]*");
    isMatch = regExp.exactMatch(src);
    return isMatch;
}

/* 计算crc校验码 */
void CrcCalc::on_btnCalc_clicked()
{
    quint32 index = ui->cbbSelect->currentIndex();
    CRCList calcSelect =ui->cbbSelect->itemData(index).value<CRCList>();
    QByteArray tmpBuf ;
    uint8_t crc8_;
    uint16_t crc16_;
    uint32_t crc32_;
    if(ui->txtEdit->toPlainText() != NULL){
        tmpBuf = this->stringToHex(ui->txtEdit->toPlainText());
        if(!tmpBuf.isEmpty() ){
            switch(calcSelect){
            case CRC4_itu :
                crc8_= crc4_itu_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC16_modbus :
                crc16_ = crc16_modbus_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC32 :
                crc32_ = crc32_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc32_);break;
            case CRC5_epc:
                crc8_ = crc5_epc_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC5_itu:
                crc8_ = crc5_itu_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC5_usb:
                crc8_ = crc5_usb_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC6_itu:
                crc8_ = crc6_itu_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC7_mmc:
                crc8_ = crc7_mmc_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC8:
                crc8_  = crc8_Calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC8_itu:
                crc8_ = crc8_itu_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC8_rohc:
                crc8_ = crc8_rohc_Calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC8_maxim:           //DS18B20
                crc8_ = crc8_maxim_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc8_);break;
            case CRC16_ibm:
                crc16_ = crc16_ibm_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_maxim:
                crc16_ = crc16_maxim_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_usb:
                crc16_ = crc16_usb_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_ccitt:
                crc16_ = crc16_ccitt_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_ccitt_false:
                crc16_ = crc16_ccitt_false_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_x25:
                crc16_ = crc16_x25_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_xmodem:
                crc16_ = crc16_xmodem_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC16_dnp:
                crc16_ = crc16_dnp_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc16_);break;
            case CRC32_mpeg_2:
                crc32_ = crc32_mpeg_2_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
                tmpBuf = this->toQByteArray(crc32_);break;
            default: break;
            }
            tmpBuf = tmpBuf.toHex().toUpper();
            tmpBuf.prepend("0x");
            QString str = QString::fromLocal8Bit(tmpBuf);
            ui->txtBrowser->setPlainText(str);
        }
    }
}


/* 将QString 转换成可以十六进制的字符QByteArray */ // "33 35" -> 0x33 0x35
/* 并且删除 非打印字符  */
QByteArray CrcCalc::stringToHex(QString src )
{
    QByteArray buf;
    QString tmpString ;
    tmpString = src.remove(QRegExp("\\s"));// delete ' '
    QByteArray tmpTest = tmpString.toLatin1();// "3335"->0x33 0x33 0x33 0x35
    if(tmpTest.length() & 0x01 ) // 奇数个字符,最后一个字符不能满足转换成Hex数据
    {
        tmpTest.remove(tmpTest.length()-1, 1); // 移除并警告
        QMessageBox::information(NULL, tr("不支持的输入"),  tr("请输入完整的字节"), 0, 0);
        buf.clear();
    }else{
        buf = QByteArray::fromHex(tmpTest); // ascii to hex(hex字符串转换成 hex数据 )//0x33 0x33 0x33 0x35 -> 0x33 0x35
    }
    return buf;
}

/* 状态栏显示相关crc信息 */
void CrcCalc::on_cbbSelect_currentIndexChanged(int index)
{
//    index = index;
    switch(index){
    case CRC4_itu :
        ui->statusBar->showMessage("CRC-4/ITU, (0x03), Init:0x00, Refin:True, Refout:True, XORout:0x00");
        break;
    case CRC16_modbus :
        ui->statusBar->showMessage("CRC-16/MODBUS, (0x8005), Init:0xFFFF, Refin:True, Refout:True, XORout:0x0000");
        break;
    case CRC32 :
        ui->statusBar->showMessage("CRC-32, (0x4C11DB7), Init:0xFFFFFFF, Refin:True, Refout:True, XORout:0xFFFFFFF");
        break;
    case CRC5_epc:
        ui->statusBar->showMessage("CRC-5/EPC, (0x09), Init:0x09, Refin:False, Refout:False, XORout:0x00");
        break;
    case CRC5_itu:
        ui->statusBar->showMessage("CRC-5/ITU, (0x15), Init:0x00, Refin:True, Refout:True, XORout:0x00");
        break;
    case CRC5_usb:
        ui->statusBar->showMessage("CRC-5/USB, (0x05), Init:0x1F, Refin:True, Refout:True, XORout:0x1F");
        break;
    case CRC6_itu:
        ui->statusBar->showMessage("CRC-6/ITU, (0x03), Init:0x00, Refin:True, Refout:True, XORout:0x00");
        break;
    case CRC7_mmc:
        ui->statusBar->showMessage("CRC-7/MMC, (0x09), Init:0x00, Refin:False, Refout:False, XORout:0x00");
        break;
    case CRC8:
        ui->statusBar->showMessage("CRC-8, (0x07), Init:0x00, Refin:False, Refout:False, XORout:0x00");
        break;
    case CRC8_itu:
        ui->statusBar->showMessage("CRC-8/ITU, (0x07), Init:0x00, Refin:False, Refout:False, XORout:0x55");
        break;
    case CRC8_rohc:
        ui->statusBar->showMessage("CRC-8/ROHC, (0x07), Init:0xFF, Refin:True, Refout:True, XORout:0x00");
        break;
    case CRC8_maxim:
        ui->statusBar->showMessage("CRC-8/MAXIM, (0x31), Init:0x00, Refin:True, Refout:True, XORout:0x00");
        break;    //DS18B20
    case CRC16_ibm:
        ui->statusBar->showMessage("CRC-16/IBM, (0x8005), Init:0x0000, Refin:True, Refout:True, XORout:0x0000");
        break;
    case CRC16_maxim:
        ui->statusBar->showMessage("CRC-16/MAXIM, (0x8005), Init:0x0000, Refin:True, Refout:True, XORout:0xFFFF");

        break;
    case CRC16_usb:
        ui->statusBar->showMessage("CRC-16/USB, (0x8005), Init:0xFFFF, Refin:True, Refout:True, XORout:0xFFFF");
        break;
    case CRC16_ccitt:
        ui->statusBar->showMessage("CRC-16/CCITT, (0x1021), Init:0x0000, Refin:True, Refout:True, XORout:0x0000");
        break;
    case CRC16_ccitt_false:
        ui->statusBar->showMessage("CRC-16/CCITT-FALSE, (0x1021), Init:0xFFFF, Refin:False, Refout:False, XORout:0x0000");
        break;
    case CRC16_x25:
        ui->statusBar->showMessage("CRC-16/X25, (0x1021), Init:0xFFFF, Refin:True, Refout:True, XORout:0xFFFF");
        break;
    case CRC16_xmodem:
        ui->statusBar->showMessage("CRC-16/XMODEM, (0x1021), Init:0x0000, Refin:False, Refout:False, XORout:0x0000");
        break;
    case CRC16_dnp:
        ui->statusBar->showMessage("CRC-16/DNP, (0x3D65), Init:0x0000, Refin:True, Refout:True, XORout:0xFFFF");
        break;
    case CRC32_mpeg_2:
        ui->statusBar->showMessage("CRC-32/MPEG-2, (0x4C11DB7), Init:0xFFFFFFF, Refin:False, Refout:False, XORout:0x0000000");
        break;
    default: break;
    }
}

/* 显示crc列表 */
void CrcCalc::listCRC(QComboBox *cbbDataBit)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<CRCList>();
    for (qint32 i = 0; i < metaEnum.keyCount(); i++) {
        cbbDataBit->addItem(metaEnum.key(i), metaEnum.value(i));
        /* 删除未知值 */
        if(metaEnum.value(i) == CRCList::Unknown )
            cbbDataBit->removeItem(i);
    }
    ui->cbbSelect->setCurrentIndex(CrcCalc::CRC16_modbus);// 设定默认值
}

QByteArray CrcCalc::toQByteArray(uint8_t tmp)
{
    QByteArray retVal;
    retVal.resize(1);
    retVal[0] = tmp;
    return retVal;
}
QByteArray CrcCalc::toQByteArray(uint16_t tmp)
{
    QByteArray retVal;
    retVal.resize(2);
    retVal[0] = (tmp>>8);
    retVal[1] = (tmp&0x00FF);
    return retVal;
}
QByteArray CrcCalc::toQByteArray(uint32_t tmp)
{
    QByteArray retVal;
    retVal.resize(4);
    retVal[0] = ((tmp&0xFF000000)>>24);
    retVal[1] = ((tmp&0x00FF0000)>>16);
    retVal[2] = ((tmp&0x0000FF00)>>8);
    retVal[3] =  (tmp&0x000000FF);
    return retVal;
}



void CrcCalc::on_btnLoadFile_clicked()
{
    ui->lblMsg->setText("Open File");
    QString filePath = QFileDialog::getOpenFileName(this,"Open FIle", qApp->applicationDirPath(), "All(*.*)") ;
    if(NULL != filePath ){
        ui->cbbSelect->setCurrentIndex(CrcCalc::CRC32);
        file = new QFile(filePath);
        if(file->open(QIODevice::ReadOnly | QIODevice::ReadOnly)){
            QByteArray tmpBuf = file->readAll();
            uint32_t crc32_;
            crc32_ = crc32_calc((unsigned char *)tmpBuf.data(), tmpBuf.length()); // use table to check CRC32
            tmpBuf = this->toQByteArray(crc32_);
            tmpBuf = tmpBuf.toHex().toUpper();
            tmpBuf.prepend("0x");
            QString str = QString::fromLocal8Bit(tmpBuf);
            ui->txtBrowser->setPlainText(str);
            file->close();
            ui->lblMsg->setText("Complete!");
        }else{
            QMessageBox::information(NULL, tr("打开失败"),  tr("打开文件失败"), 0, 0);
            ui->lblMsg->setText("False!");
        }
        delete file;
    }else{
        ui->lblMsg->clear();
    }
}
