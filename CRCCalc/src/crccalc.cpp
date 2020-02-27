#include "crccalc.h"
#include <iostream>
#include <stdio.h>
#include "constString.h"

void crc16_riello_Table();

CrcCalc::CrcCalc(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CrcCalc)
{
    ui->setupUi(this);
    this->listCRC();
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

/**
 * @brief CrcCalc::isHexString 判断src是否Hex字符串
 * @param src: 文本输入
 * @return isMatch: src 仅包含有a-f0-9A-F和空格字符时,返回true
 */
bool CrcCalc::isHexString(QString src)
{
    bool isMatch = true;
    QRegExp regExp("[a-f0-9A-F ]*");
    isMatch = regExp.exactMatch(src);
    return isMatch;
}

/**
 * @brief CrcCalc::on_btnCalc_clicked 计算crc校验码,并显示计算结果
 */
void CrcCalc::on_btnCalc_clicked()
{
    quint32 index = ui->lstCRCSelect->currentRow();
    QByteArray tmpBuf ;
    if(ui->txtEdit->toPlainText() != NULL){
        tmpBuf = this->stringToHex(ui->txtEdit->toPlainText());
        if(!tmpBuf.isEmpty() ){
            this->calcCRC(tmpBuf, (CRCList)index);
        }
    }
}
void CrcCalc::calcCRC(QByteArray &tmpBuf, CRCList calcSelect )
{
    uint8_t crc8_;
    uint16_t crc16_;
    uint32_t crc32_;
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
        crc8_  = crc8_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
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
    case CRC8_cdma2000:
        crc8_ = crc8_cdma2000_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc8_);break;
    case CRC8_darc:
        crc8_ = crc8_darc_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc8_);break;
    case CRC8_dvb_s2:
        crc8_ = crc8_dvb_s2_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc8_);break;
    case CRC8_ebu:
        crc8_ = crc8_ebu_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc8_);break;
    case CRC8_i_code:
        crc8_ = crc8_i_code_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc8_);break;
    case CRC8_wcdma:
        crc8_ = crc8_wcdma_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
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
    case CRC16_aug_ccitt:
        crc16_ = crc16_aug_ccitt_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_buypass:
        crc16_ = crc16_buypass_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_cdma2000:
        crc16_ = crc16_cdma2000_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_dds_110:
        crc16_ = crc16_dds_110_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_dect_r:
        crc16_ = crc16_dect_r_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_dect_x:
        crc16_ = crc16_dect_x_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_en_13757:
        crc16_ = crc16_en_13757_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_genibus:
        crc16_ = crc16_genibus_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_mcrf4xx:
        crc16_ = crc16_mcrf4xx_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_riello:
        crc16_ = crc16_riello_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_t10_dif:
        crc16_ = crc16_t10_dif_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_teledisk:
        crc16_ = crc16_teledisk_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_tms37157:
        crc16_ = crc16_tms37157_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC16_a:
        crc16_ = crc16_a_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc16_);break;
    case CRC32_mpeg_2:
        crc32_ = crc32_mpeg_2_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_bzip2:
        crc32_ = crc32_bzip2_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_posix:
        crc32_ = crc32_posix_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_jamcrc:
        crc32_ = crc32_jamcrc_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_xfer:
        crc32_ = crc32_xfer_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_c:
        crc32_ = crc32_c_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_d:
        crc32_ = crc32_d_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    case CRC32_q:
        crc32_ = crc32_q_calc((uint8_t *)tmpBuf.data(), tmpBuf.length());
        tmpBuf = this->toQByteArray(crc32_);break;
    default: break;
    }
    tmpBuf = tmpBuf.toHex().toUpper();
    tmpBuf.prepend("0x");
    QString str = QString::fromLocal8Bit(tmpBuf);
    ui->txtBrowser->setPlainText(str);
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
void CrcCalc::on_lstCRCSelect_currentRowChanged(int currentRow)
{
    QString templateString = "/**\n"
                             "  * Name:    %1\n"
                             "  * Poly:    %2\n"
                             "  * Init:    %3\n"
                             "  * Refin:   %4\n"
                             "  * Refout:  %5\n"
                             "  * Xorout:  %6\n"
                             "  */\n";
    QString name;
    QString poly;
    QString init;
    QString refx;
    QString xorout;

    ui->txtMsg->clear();
    switch(currentRow){
    case CRC4_itu :
        name = "CRC4/ITU";poly = "0x03";init = "0x00";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc4_itu_string);
        break;
    case CRC16_modbus :
        name = "CRC16/MODBUS";poly = "0x8005";init = "0xFFFF";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_modbus_string);
        break;
    case CRC32 :
        name = "CRC32";poly = "0x4C11DB7";init = "0xFFFFFFFF";refx = "True";xorout = "0xFFFFFFFF";
        ui->txtMsg->appendPlainText(crc32_string);
        break;
    case CRC5_epc:
        name = "CRC5/EPC";poly = "0x09";init = "0x09";refx = "False";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc5_epu_string);
        break;
    case CRC5_itu:
        name = "CRC5/ITU";poly = "0x15";init = "0x00";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc5_itu_string);
        break;
    case CRC5_usb:
        name = "CRC5/USB";poly = "0x05";init = "0x1F";refx = "True";xorout = "0x1F";
        ui->txtMsg->appendPlainText(crc5_usb_string);
        break;
    case CRC6_itu:
        name = "CRC6/ITU";poly = "0x03";init = "0x00";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc6_itu_string);
        break;
    case CRC7_mmc:
        name = "CRC7/MMC";poly = "0x09";init = "0x00";refx = "False";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc7_mmc_string);
        break;
    case CRC8:
        name = "CRC8";poly = "0x07";init = "0x00";refx = "False";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_string);
        break;
    case CRC8_itu:
        name = "CRC8/ITU";poly = "0x07";init = "0x00";refx = "False";xorout = "0x55";
        ui->txtMsg->appendPlainText(crc8_itu_string);
        break;
    case CRC8_rohc:
        name = "CRC8/ROHC";poly = "0x07";init = "0xFF";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_rohc_string);
        break;
    case CRC8_darc:
        name = "CRC8/DARC";poly = "0x39";init = "0x00";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_darc_string);
        break;
    case CRC8_maxim:
        name = "CRC8/MAXIM";poly = "0x31";init = "0x00";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_maxim_string);
        break;    //DS18B20
    case CRC8_cdma2000:
        name = "CRC8/CDMA2000";poly = "0x9B";init = "0xFF";refx = "False";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_cdma2000_string);
        break;
    case CRC8_dvb_s2:
        name = "CRC8/DVD-S2";poly = "0xD5";init = "0x00";refx = "False";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_dvb_s2_string);
        break;
    case CRC8_ebu:
        name = "CRC8/EBU";poly = "0x1D";init = "0xFF";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_ebu_string);
        break;
    case CRC8_i_code:
        name = "CRC8/I-CODE";poly = "0x1D";init = "0xFD";refx = "False";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_i_code_string);
        break;
    case CRC8_wcdma:
        name = "CRC8/WCDMA";poly = "0x9B";init = "0x00";refx = "True";xorout = "0x00";
        ui->txtMsg->appendPlainText(crc8_wcdma_string);
        break;
    case CRC16_ibm:
        name = "CRC16/IBM";poly = "0x8005";init = "0x0000";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_ibm_string);
        break;
    case CRC16_maxim:
        name = "CRC16/MAXIM";poly = "0x8005";init = "0x0000";refx = "True";xorout = "0xFFFF";
        ui->txtMsg->appendPlainText(crc16_maxim_string);
        break;
    case CRC16_usb:
        name = "CRC16/USB";poly = "0x8005";init = "0xFFFF";refx = "True";xorout = "0xFFFF";
        ui->txtMsg->appendPlainText(crc16_usb_string);
        break;
    case CRC16_ccitt:
        name = "CRC16/CCITT(KERMIT)";poly = "0x1021";init = "0x0000";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_ccitt_string);
        break;
    case CRC16_ccitt_false:
        name = "CRC16/CCITT-False";poly = "0x1021";init = "0xFFFF";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_ccitt_false_string);
        break;
    case CRC16_x25:
        name = "CRC16/X25";poly = "0x1021";init = "0xFFFF";refx = "True";xorout = "0xFFFF";
        ui->txtMsg->appendPlainText(crc16_x25_string);
        break;
    case CRC16_xmodem:
        name = "CRC16/XMODEM";poly = "0x1021";init = "0x0000";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_xmodem_string);
        break;
    case CRC16_dnp:
        name = "CRC16/DNP";poly = "0x3D65";init = "0x0000";refx = "True";xorout = "0xFFFF";

        break;
    case CRC16_aug_ccitt:
        name = "CRC16/AUG-CCITT";poly = "0x1021";init = "0x1D0F";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_aug_ccitt_string);
        break;
    case CRC16_buypass:
        name = "CRC16/BUYPASS";poly = "0x8005";init = "0x0000";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_buypass_string);
        break;
    case CRC16_cdma2000:
        name = "CRC16/CDMA2000";poly = "0xC867";init = "0xFFFF";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_cdma2000_string);
        break;
    case CRC16_dds_110:
        name = "CRC16/DDS-110";poly = "0x8005";init = "0x800D";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_dds_110_string);
        break;
    case CRC16_dect_r:
        name = "CRC16/DECT-R";poly = "0x0589";init = "0x0000";refx = "False";xorout = "0x0001";
        ui->txtMsg->appendPlainText(crc16_dect_r_string);
        break;
    case CRC16_dect_x:
        name = "CRC16/DECT-X";poly = "0x0589";init = "0x0000";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_dect_x_string);
        break;
    case CRC16_en_13757:
        name = "CRC16/EN-13757";poly = "0x3D65";init = "0x0000";refx = "False";xorout = "0xFFFF";
        ui->txtMsg->appendPlainText(crc16_en_13757_string);
        break;
    case CRC16_genibus:
        name = "CRC16/GENIBUS";poly = "0x1021";init = "0xFFFF";refx = "False";xorout = "0xFFFF";
        ui->txtMsg->appendPlainText(crc16_genibus_string);
        break;
    case CRC16_mcrf4xx:
        name = "CRC16/MCRF4XX";poly = "0x1021";init = "0xFFFF";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_mcrf4xx_string);
        break;
    case CRC16_riello:
        name = "CRC16/RIELLO";poly = "0x1021";init = "0xB2AA";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_riello_string);
        break;
    case CRC16_t10_dif:
        name = "CRC16/T10-DIF";poly = "0x8BB7";init = "0x0000";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_t10_dif_string);
        break;
    case CRC16_teledisk:
        name = "CRC16/TELEDISK";poly = "0xA097";init = "0x0000";refx = "False";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_teledisk_string);
        break;
    case CRC16_tms37157:
        name = "CRC16/TMS37157";poly = "0x1021";init = "0x89EC";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_tms37157_string);
        break;
    case CRC16_a:
        name = "CRC16/A";poly = "0x1021";init = "0xC6C6";refx = "True";xorout = "0x0000";
        ui->txtMsg->appendPlainText(crc16_a_string);
        break;
    case CRC32_mpeg_2:
        name = "CRC32/MEPG-2";poly = "0x4C11DB7";init = "0xFFFFFFFF";refx = "False";xorout = "0x00000000";
        ui->txtMsg->appendPlainText(crc32_mpeg_2_string);
        break;
    case CRC32_bzip2:
        name = "CRC32/BZIP2";poly = "0x4C11DB7";init = "0xFFFFFFFF";refx = "True";xorout = "0xFFFFFFFF";
        ui->txtMsg->appendPlainText(crc32_bzip2_string);
        break;
    case CRC32_c:
        name = "CRC32/C";poly = "0x1EDC6F41";init = "0xFFFFFFFF";refx = "True";xorout = "0xFFFFFFFF";
        ui->txtMsg->appendPlainText(crc32_c_string);
        break;
    case CRC32_d:
        name = "CRC32/C";poly = "0xA833982B";init = "0xFFFFFFFF";refx = "True";xorout = "0xFFFFFFFF";
        ui->txtMsg->appendPlainText(crc32_d_string);
        break;
    case CRC32_posix:
        name = "CRC32/POSIX";poly = "0x4C11DB7";init = "0x00000000";refx = "False";xorout = "0xFFFFFFFF";
        ui->txtMsg->appendPlainText(crc32_posix_string);
        break;
    case CRC32_q:
        name = "CRC32/Q";poly = "0x814141AB";init = "0x00000000";refx = "False";xorout = "0x00000000";
        ui->txtMsg->appendPlainText(crc32_q_string);
        break;
    case CRC32_jamcrc:
        name = "CRC32/JAMCRC";poly = "0x4C11DB7";init = "0xFFFFFFFF";refx = "True";xorout = "0x00000000";
        ui->txtMsg->appendPlainText(crc32_jamcrc_string);
        break;
    case CRC32_xfer:
        name = "CRC32/XFER";poly = "0x000000AF";init = "0x00000000";refx = "False";xorout = "0x00000000";
        ui->txtMsg->appendPlainText(crc32_xfer_string);
        break;
    default: break;
    }
    ui->txtMsg->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor );
    ui->txtMsg->insertPlainText(templateString.arg(name,poly,init,refx,refx,xorout));
    ui->txtMsg->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor );
}

/* 显示crc列表 */
void CrcCalc::listCRC()
{
    QStringList CRCStringList;
    QMetaEnum metaEnum = QMetaEnum::fromType<CRCList>();
    for (qint32 i = 0; i < metaEnum.keyCount(); i++) {
        CRCStringList<<QString(metaEnum.key(i)).toUpper();
        /* 删除未知值 */
        if(metaEnum.value(i) == CRCList::Unknown ){
            CRCStringList.removeLast();
        }
    }
    ui->lstCRCSelect->addItems(CRCStringList);
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
        file = new QFile(filePath);
        if(file->open(QIODevice::ReadOnly | QIODevice::ReadOnly)){

            QByteArray tmpBuf = file->readAll();
            CRCList crcList = (CRCList)ui->lstCRCSelect->currentRow();
            this->calcCRC(tmpBuf, crcList);

            file->close();
            ui->lblMsg->setText("CRC Complete!");
        }else{
            QMessageBox::information(NULL, tr("打开失败"),  tr("打开文件失败"), 0, 0);
            ui->lblMsg->setText("False!");
        }
        delete file;
    }else{
        ui->lblMsg->clear();
    }
}


