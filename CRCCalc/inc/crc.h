#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;


uint8_t   crc4_itu_calc          (uint8_t *data, uint32_t length);//("CRC-4/ITU, (0x03), Init:0x00, Refin:True, Refout:True, XORout:0x00");

uint8_t   crc5_epc_calc          (uint8_t *data, uint32_t length);//("CRC-5/EPC, (0x09), Init:0x09, Refin:False, Refout:False, XORout:0x00");
uint8_t   crc5_itu_calc          (uint8_t *data, uint32_t length);//("CRC-5/ITU, (0x15), Init:0x00, Refin:True, Refout:True, XORout:0x00");
uint8_t   crc5_usb_calc          (uint8_t *data, uint32_t length);//("CRC-5/USB, (0x05), Init:0x1F, Refin:True, Refout:True, XORout:0x1F");
uint8_t   crc6_itu_calc          (uint8_t *data, uint32_t length);//("CRC-6/ITU, (0x03), Init:0x00, Refin:True, Refout:True, XORout:0x00");
uint8_t   crc7_mmc_calc          (uint8_t *data, uint32_t length);//("CRC-7/MMC, (0x09), Init:0x00, Refin:False, Refout:False, XORout:0x00");

uint8_t   crc8_calc              (uint8_t *data, uint32_t length);//("CRC-8,         (0x07), Init:0x00, Refin:False, Refout:False, XORout:0x00");
uint8_t   crc8_itu_calc          (uint8_t *data, uint32_t length);//("CRC-8/ITU(ATM),(0x07), Init:0x00, Refin:False, Refout:False, XORout:0x55");
uint8_t   crc8_rohc_Calc         (uint8_t *data, uint32_t length);//("CRC-8/ROHC,    (0x07), Init:0xFF, Refin:True,  Refout:True,  XORout:0x00");
uint8_t   crc8_maxim_calc        (uint8_t *data, uint32_t length);//("CRC-8/MAXIM,   (0x31), Init:0x00, Refin:True,  Refout:True,  XORout:0x00"); /* Alias:   DOW-CRC,CRC-8/IBUTTON Use: Maxim(Dallas)'s some devices,e.g. DS18B20 */
uint8_t   crc8_cdma2000_calc     (uint8_t *data, uint32_t length);//("CRC-8/CDMA2000,(0x9B), Init:0xFF, Refin:False, Refout:False, XORout:0x00");
uint8_t   crc8_darc_calc         (uint8_t *data, uint32_t length);//("CRC-8/DARC,    (0x39), Init:0x00, Refin:True,  Refout:True,  XORout:0x00");
uint8_t   crc8_dvb_s2_calc       (uint8_t *data, uint32_t length);//("CRC-8/DVD-S2,  (0xD5), Init:0x00, Refin:False, Refout:False, XORout:0x00");
uint8_t   crc8_ebu_calc          (uint8_t *data, uint32_t length);//("CRC-8/EBU,     (0x1D), Init:0xFF, Refin:True,  Refout:True,  XORout:0x00");
uint8_t   crc8_i_code_calc       (uint8_t *data, uint32_t length);//("CRC-8/I-CODE,  (0x1D), Init:0xFD, Refin:False, Refout:False, XORout:0x00");
uint8_t   crc8_wcdma_calc        (uint8_t *data, uint32_t length);//("CRC-8/WCDMA,   (0x9B), Init:0x00, Refin:True,  Refout:True,  XORout:0x00");

uint16_t  crc16_ibm_calc         (uint8_t *data, uint32_t length);//("CRC-16/IBM,    (0x8005), Init:0x0000, Refin:True, Refout:True, XORout:0x0000"); /* Alias:   CRC-16,CRC-16/ARC,CRC-16/LHA */
uint16_t  crc16_maxim_calc       (uint8_t *data, uint32_t length);//("CRC-16/MAXIM,  (0x8005), Init:0x0000, Refin:True, Refout:True, XORout:0xFFFF");
uint16_t  crc16_usb_calc         (uint8_t *data, uint32_t length);//("CRC-16/USB,    (0x8005), Init:0xFFFF, Refin:True, Refout:True, XORout:0xFFFF");
uint16_t  crc16_modbus_calc      (uint8_t *data, uint32_t length);//("CRC-16/MODBUS, (0x8005), Init:0xFFFF, Refin:True, Refout:True, XORout:0x0000");
uint16_t  crc16_ccitt_calc       (uint8_t *data, uint32_t length);//("CRC-16/CCITT(KERMIT), (0x1021), Init:0x0000, Refin:True,  Refout:True,  XORout:0x0000");
uint16_t  crc16_ccitt_false_calc (uint8_t *data, uint32_t length);//("CRC-16/CCITT-FALSE,   (0x1021), Init:0xFFFF, Refin:False, Refout:False, XORout:0x0000");
uint16_t  crc16_x25_calc         (uint8_t *data, uint32_t length);//("CRC-16/X25,      (0x1021), Init:0xFFFF, Refin:True, Refout:True, XORout:0xFFFF");
uint16_t  crc16_xmodem_calc      (uint8_t *data, uint32_t length);//("CRC-16/XMODEM,   (0x1021), Init:0x0000, Refin:False, Refout:False, XORout:0x0000"); /* Alias:   CRC-16/ZMODEM,CRC-16/ACORN */
uint16_t  crc16_dnp_calc         (uint8_t *data, uint32_t length);//("CRC-16/DNP,      (0x3D65), Init:0x0000, Refin:True, Refout:True, XORout:0xFFFF");
uint16_t  crc16_aug_ccitt_calc   (uint8_t *data, uint32_t length);//("CRC-16/AUG-CCITT,(0x1021), Init:0x1D0F, Refin:false, Refout:false, XORout:0x0000");
uint16_t  crc16_buypass_calc     (uint8_t *data, uint32_t length);//("CRC-16/BUYPASS,  (0x8005), Init:0x0000, Refin:false, Refout:false, XORout:0x0000");
uint16_t  crc16_cdma2000_calc    (uint8_t *data, uint32_t length);//("CRC-16/CDMA2000, (0xC867), Init:0xFFFF, Refin:false, Refout:false, XORout:0x0000");
uint16_t  crc16_dds_110_calc     (uint8_t *data, uint32_t length);//("CRC-16/DDS-110,  (0x8005), Init:0x800D, Refin:false, Refout:false, XORout:0x0000");
uint16_t  crc16_dect_r_calc      (uint8_t *data, uint32_t length);//("CRC-16/DECT-R,   (0x0589), Init:0x0000, Refin:false, Refout:false, XORout:0x0001");
uint16_t  crc16_dect_x_calc      (uint8_t *data, uint32_t length);//("CRC-16/DECT-R,   (0x0589), Init:0x0000, Refin:false, Refout:false, XORout:0x0000");
uint16_t  crc16_en_13757_calc    (uint8_t *data, uint32_t length);//("CRC-16/EN-13757, (0x3D65), Init:0x0000, Refin:False, Refout:False, XORout:0xFFFF");
uint16_t  crc16_genibus_calc     (uint8_t *data, uint32_t length);//("CRC-16/GENIBUS,  (0x1021), Init:0xFFFF, Refin:False, Refout:False, XORout:0xFFFF");
uint16_t  crc16_mcrf4xx_calc     (uint8_t *data, uint32_t length);//("CRC-16/MCRF4xx,  (0x1021), Init:0xFFFF, Refin:True,  Refout:True,  XORout:0x0000");
uint16_t  crc16_riello_calc      (uint8_t *data, uint32_t length);//("CRC-16/RIELLO,   (0x1021), Init:0xB244, Refin:True,  Refout:True,  XORout:0x0000");
uint16_t  crc16_t10_dif_calc     (uint8_t *data, uint32_t length);//("CRC-16/T10-DIF,  (0x8BB7), Init:0x0000, Refin:False, Refout:False, XORout:0x0000");
uint16_t  crc16_teledisk_calc    (uint8_t *data, uint32_t length);//("CRC-16/TELDISK,  (0xA097), Init:0x0000, Refin:False, Refout:False, XORout:0x0000");
uint16_t  crc16_tms37157_calc    (uint8_t *data, uint32_t length);//("CRC-16/TMS37157, (0x1021), Init:0x89EC, Refin:True,  Refout:True,  XORout:0x0000");
uint16_t  crc16_a_calc           (uint8_t *data, uint32_t length);//("CRC-16/A,        (0x1021), Init:0xC6C6, Refin:True,  Refout:True,  XORout:0x0000");

uint32_t  crc32_calc             (uint8_t *data, uint32_t length);//("CRC-32(ADCCP), (0x04C11DB7), Init:0xFFFFFFFF, Refin:True,  Refout:True,  XORout:0xFFFFFFFF");
uint32_t  crc32_mpeg_2_calc      (uint8_t *data, uint32_t length);//("CRC-32/MPEG-2, (0x04C11DB7), Init:0xFFFFFFFF, Refin:False, Refout:False, XORout:0x00000000");
uint32_t  crc32_bzip2_calc       (uint8_t *data, uint32_t length);//("CRC-32/BZIP-2, (0x04C11DB7), Init:0xFFFFFFFF, Refin:False, Refout:False, XORout:0xFFFFFFFF");
uint32_t  crc32_posix_calc       (uint8_t *data, uint32_t length);//("CRC-32/POSIX,  (0x04C11DB7), Init:0x00000000, Refin:False, Refout:False, XORout:0xFFFFFFFF");
uint32_t  crc32_jamcrc_calc      (uint8_t *data, uint32_t length);//("CRC-32/JAMCRC, (0x04C11DB7), Init:0xFFFFFFFF, Refin:True,  Refout:True,  XORout:0x00000000");
uint32_t  crc32_xfer_calc        (uint8_t *data, uint32_t length);//("CRC-32/XFER,   (0x000000AF), Init:0x00000000, Refin:False, Refout:False, XORout:0x00000000");
uint32_t  crc32_c_calc           (uint8_t *data, uint32_t length);//("CRC-32/C,      (0x1EDC6F41), Init:0xFFFFFFFF, Refin:True,  Refout:True,  XORout:0xFFFFFFFF");
uint32_t  crc32_d_calc           (uint8_t *data, uint32_t length);//("CRC-32/D,      (0xA833982B), Init:0xFFFFFFFF, Refin:True,  Refout:True,  XORout:0xFFFFFFFF");
uint32_t  crc32_q_calc           (uint8_t *data, uint32_t length);//("CRC-32/Q,      (0x814141AB), Init:0xFFFFFFFF, Refin:False, Refout:False, XORout:0x00000000");

#ifdef __cplusplus
}
#endif
#endif // CRC_H
