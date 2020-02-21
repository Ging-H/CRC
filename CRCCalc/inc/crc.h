#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;


//void crc8_GenerateTable();
//void crc8_rohc_GenerateTable();
//void crc4_itu_GenerateTable();
//void crc5_itu_GenerateTable();


uint8_t   crc4_itu_calc          (uint8_t *data, uint32_t length);

uint8_t   crc5_epc_calc          (uint8_t *data, uint32_t length);
uint8_t   crc5_itu_calc          (uint8_t *data, uint32_t length);
uint8_t   crc5_usb_calc          (uint8_t *data, uint32_t length);
uint8_t   crc6_itu_calc          (uint8_t *data, uint32_t length);
uint8_t   crc7_mmc_calc          (uint8_t *data, uint32_t length);

uint8_t   crc8_Calc              (uint8_t *data, uint32_t length);
uint8_t   crc8_itu_calc          (uint8_t *data, uint32_t length);
uint8_t   crc8_rohc_Calc         (uint8_t *data, uint32_t length);
uint8_t   crc8_maxim_calc        (uint8_t *data, uint32_t length);

uint16_t  crc16_ibm_calc         (uint8_t *data, uint32_t length);
uint16_t  crc16_maxim_calc       (uint8_t *data, uint32_t length);
uint16_t  crc16_usb_calc         (uint8_t *data, uint32_t length);
uint16_t  crc16_modbus_calc      (uint8_t *data, uint32_t length);
uint16_t  crc16_ccitt_calc       (uint8_t *data, uint32_t length);
uint16_t  crc16_ccitt_false_calc (uint8_t *data, uint32_t length);
uint16_t  crc16_x25_calc         (uint8_t *data, uint32_t length);
uint16_t  crc16_xmodem_calc      (uint8_t *data, uint32_t length);
uint16_t  crc16_dnp_calc         (uint8_t *data, uint32_t length);

uint32_t  crc32_calc             (uint8_t *data, uint32_t length);
uint32_t  crc32_mpeg_2_calc      (uint8_t *data, uint32_t length);




#ifdef __cplusplus
}
#endif
#endif // CRC_H
