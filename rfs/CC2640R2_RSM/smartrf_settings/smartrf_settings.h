#ifndef _SMARTRF_SETTINGS_H_
#define _SMARTRF_SETTINGS_H_

//*********************************************************************************
// Generated by SmartRF Studio version 2.10.0 (build#110)
// The applied template is compatible with CC2640R2 SDK 2.20.xx.xx
// Device: CC2640R2F Rev. 2.5 (Rev. F)
// 
//*********************************************************************************
#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/rf_mailbox.h)
#include DeviceFamily_constructPath(driverlib/rf_common_cmd.h)
#include DeviceFamily_constructPath(driverlib/rf_ble_cmd.h)
#include <ti/drivers/rf/RF.h>


// TX Power table size definition
#define TX_POWER_TABLE_SIZE 14
#define ADVLEN 3

typedef struct {
    uint8_t LEN;
    union {
        uint8_t value;
        struct {
            unsigned char RND:2;
            unsigned char SEQ:2;
            unsigned char BUZZ0:1;
            unsigned char BUZZ1:1;
            unsigned char USB:1;
            unsigned char TYPE:1;
        };
    } SQN;
#if(sensor==23)
    uint8_t BATT;
    uint8_t ADC[2];
#elif(sensor==711)
    uint8_t ADC[2];
    uint8_t BATT;
#endif
} adv_data_t;

extern adv_data_t ADV_DATA;


// TX Power Table Object
extern RF_TxPowerTable_Entry txPowerTable[TX_POWER_TABLE_SIZE];


// TI-RTOS RF Mode Object
extern RF_Mode RF_ble;


// RF Core API commands
extern rfc_CMD_BLE5_RADIO_SETUP_t RF_cmdBle5RadioSetup;
extern rfc_CMD_FS_t RF_cmdFs;
extern rfc_CMD_BLE_ADV_NC_t RF_cmdBleAdvNc[3];


// RF Core API Overrides
extern uint32_t pOverridesCommon[];
extern uint32_t pOverrides1Mbps[];
extern uint32_t pOverrides2Mbps[];
extern uint32_t pOverridesCoded[];


#endif // _SMARTRF_SETTINGS_H_
