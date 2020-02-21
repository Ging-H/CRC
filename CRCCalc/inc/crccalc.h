#ifndef CRCCALC_H
#define CRCCALC_H

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QMetaEnum>
#include <QFileDialog>
#include <QFile>
#include "ui_crccalc.h"
#include <QDebug>
#include "crc.h"

namespace Ui {
class CrcCalc;
}

class CrcCalc : public QMainWindow
{
    Q_OBJECT
public:

    enum CRCList{
       CRC4_itu = 0,
       CRC5_epc,
       CRC5_itu,
       CRC5_usb,
       CRC6_itu,
       CRC7_mmc,
       CRC8,
       CRC8_itu,
       CRC8_rohc,
       CRC8_maxim,           //DS18B20
       CRC16_ibm,
       CRC16_maxim,
       CRC16_usb,
       CRC16_modbus,
       CRC16_ccitt,
       CRC16_ccitt_false,
       CRC16_x25,
       CRC16_xmodem,
       CRC16_dnp,
       CRC32,
       CRC32_mpeg_2,
       Unknown = -1,
    };
    Q_ENUM(CRCList)

    explicit CrcCalc(QWidget *parent = 0);
    ~CrcCalc();
    bool isHexString(QString src);
    QByteArray stringToHex(QString src );
    void listCRC(QComboBox *cbbDataBit);

    QByteArray toQByteArray(uint8_t  tmp);
    QByteArray toQByteArray(uint16_t tmp);
    QByteArray toQByteArray(uint32_t tmp);
    QFile *file;


    /* api for crc4 */
    void apiCRC4_itu(QByteArray &array);

    void apiCRC5_epc(QByteArray &array);
    void apiCRC5_itu(QByteArray &array);
    void apiCRC5_usb(QByteArray &array);

    void apiCRC6_itu(QByteArray &array);

    void apiCRC7_mmc(QByteArray &array);

    void apiCRC8(QByteArray &array);
    void apiCRC8_itu(QByteArray &array);
    void apiCRC8_rohc(QByteArray &array);
    void apiCRC8_maxim(QByteArray &array);

    void apiCRC16_ibm(QByteArray &array);
    void apiCRC16_maxim(QByteArray &array);
    void apiCRC16_usb(QByteArray &array);
    void apiCRC16_modbus(QByteArray &array);
    void apiCRC16_ccitt(QByteArray &array);
    void apiCRC16_ccitt_false(QByteArray &array);
    void apiCRC16_x25(QByteArray &array);
    void apiCRC16_xmodem(QByteArray &array);
    void apiCRC16_dnp(QByteArray &array);
    void apiCRC32(QByteArray &array);
    void apiCRC32_mpeg2(QByteArray &array);

private slots:
    void on_txtEdit_textChanged();

    void on_btnCalc_clicked();

    void on_cbbSelect_currentIndexChanged(int index);    

    void on_btnLoadFile_clicked();

private:
    Ui::CrcCalc *ui;
};

#endif // CRCCALC_H
