//*********************************************************************************
// Generated by SmartRF Studio version 2.10.0 (build#110)
// The applied template is compatible with CC2640R2 SDK 2.20.xx.xx
// Device: CC2640R2F Rev. 2.5 (Rev. F)
// 
//*********************************************************************************


//*********************************************************************************
// Parameter summary
// Adv. Address: 010203040506 
// Adv. Data: 255 
// BLE Channel: 37 
// Extended Header: 09 09 010203040506 babe 
// Frequency: 2402 MHz
// PDU Payload length:: 11 
// TX Power: -3 dBm 
// Whitening: true 

#include <ti/devices/DeviceFamily.h>
#include DeviceFamily_constructPath(driverlib/rf_mailbox.h)
#include DeviceFamily_constructPath(driverlib/rf_common_cmd.h)
#include DeviceFamily_constructPath(driverlib/rf_ble_cmd.h)
#include <ti/drivers/rf/RF.h>
#include DeviceFamily_constructPath(rf_patches/rf_patch_cpe_bt5.h)
#include "smartrf_settings.h"


adv_data_t ADV_DATA;

#if(sensor==23)
static uint64_t devAddress = { 0xC81B6AB18BEC };
#elif(sensor==711)
static uint64_t devAddress = { 0xC81B6AB1A085 };
#endif

// TI-RTOS RF Mode Object
RF_Mode RF_ble =
{
    .rfMode = RF_MODE_BLE,
    .cpePatchFxn = &rf_patch_cpe_bt5,
    .mcePatchFxn = 0,
    .rfePatchFxn = 0,
};

// TX Power table
// The RF_TxPowerTable_DEFAULT_PA_ENTRY macro is defined in RF.h and requires the following arguments:
// RF_TxPowerTable_DEFAULT_PA_ENTRY(bias, gain, boost coefficient)
// See the Technical Reference Manual for further details about the "txPower" Command field.
// The PA settings require the CCFG_FORCE_VDDR_HH = 0 unless stated otherwise.
RF_TxPowerTable_Entry txPowerTable[TX_POWER_TABLE_SIZE] = 
{ 
    {-21, RF_TxPowerTable_DEFAULT_PA_ENTRY(7, 3, 0, 6) },
    {-18, RF_TxPowerTable_DEFAULT_PA_ENTRY(9, 3, 0, 6) },
    {-15, RF_TxPowerTable_DEFAULT_PA_ENTRY(11, 3, 0, 6) },
    {-12, RF_TxPowerTable_DEFAULT_PA_ENTRY(11, 1, 0, 10) },
    {-9, RF_TxPowerTable_DEFAULT_PA_ENTRY(14, 1, 1, 12) },
    {-6, RF_TxPowerTable_DEFAULT_PA_ENTRY(18, 1, 1, 14) },
    {-3, RF_TxPowerTable_DEFAULT_PA_ENTRY(24, 1, 1, 18) },
    {0, RF_TxPowerTable_DEFAULT_PA_ENTRY(33, 1, 1, 24) },
    {1, RF_TxPowerTable_DEFAULT_PA_ENTRY(20, 0, 0, 33) },
    {2, RF_TxPowerTable_DEFAULT_PA_ENTRY(24, 0, 0, 39) },
    {3, RF_TxPowerTable_DEFAULT_PA_ENTRY(28, 0, 0, 45) },
    {4, RF_TxPowerTable_DEFAULT_PA_ENTRY(36, 0, 1, 73) },
    {5, RF_TxPowerTable_DEFAULT_PA_ENTRY(48, 0, 1, 73) },
    RF_TxPowerTable_TERMINATION_ENTRY
};


// Overrides for CMD_BLE5_RADIO_SETUP
uint32_t pOverridesCommon[] =
{
    // override_ble5_setup_override_common.xml
    // Rx: Set LNA IB trim value based on the selected defaultPhy.mainMode setting. (NOTE: The value 0x8 is a placeholder. The value to use should be set during run-time by radio driver function.)
    ADI_HALFREG_OVERRIDE(0,4,0xF,0x8),
    // Rx: Set LNA IB offset used for automatic software compensation to 0
    (uint32_t)0x00008883,
    // Synth: Use 24 MHz crystal, enable extra PLL filtering
    (uint32_t)0x02010403,
    // Synth: Set fine top and bottom code to 127 and 0
    HW_REG_OVERRIDE(0x4020, 0x7F00),
    // Synth: Configure faster calibration
    HW32_ARRAY_OVERRIDE(0x4004, 1),
    // Synth: Configure faster calibration
    (uint32_t)0x1C0C0618,
    // Synth: Configure faster calibration
    (uint32_t)0xC00401A1,
    // Synth: Configure faster calibration
    (uint32_t)0x21010101,
    // Synth: Configure faster calibration
    (uint32_t)0xC0040141,
    // Synth: Configure faster calibration
    (uint32_t)0x00214AD3,
    // Synth: Decrease synth programming time-out by 64 us (0x0300 RAT ticks = 192 us)
    (uint32_t)0x03000243,
    // Bluetooth 5: Set correct total clock accuracy for received AuxPtr assuming local sleep clock of 50 ppm
    (uint32_t)0x0E490823,
    // override_frontend_id.xml
    (uint32_t)0xFFFFFFFF,
};


// Overrides for CMD_BLE5_RADIO_SETUP
uint32_t pOverrides1Mbps[] =
{
    // override_ble5_setup_override_1mbps.xml
    // Rx: Set LNA IB trim to normal trim value. (NOTE: The value 0x8 is a placeholder. The value to use should be set during run-time by radio driver function.)
    ADI_HALFREG_OVERRIDE(0,4,0xF,0x8),
    // Rx: Configure AGC to use gain table for improved performance
    HW_REG_OVERRIDE(0x6084, 0x05F8),
    (uint32_t)0xFFFFFFFF,
};


// Overrides for CMD_BLE5_RADIO_SETUP
uint32_t pOverrides2Mbps[] =
{
    // override_ble5_setup_override_2mbps.xml
    // Rx: Set LNA IB trim to normal trim value. (NOTE: The value 0x8 is a placeholder. The value to use should be set during run-time by radio driver function.)
    ADI_HALFREG_OVERRIDE(0,4,0xF,0x8),
    (uint32_t)0xFFFFFFFF,
};


// Overrides for CMD_BLE5_RADIO_SETUP
uint32_t pOverridesCoded[] =
{
    // override_ble5_setup_override_coded.xml
    // Rx: Set LNA IB trim to 0xF (maximum)
    ADI_HALFREG_OVERRIDE(0,4,0xF,0xF),
    // Rx: Override AGC target gain to improve performance
    HW_REG_OVERRIDE(0x6088, 0x001B),
    (uint32_t)0xFFFFFFFF,
};


// CMD_BLE5_RADIO_SETUP
// Bluetooth 5 Radio Setup Command for all PHYs
rfc_CMD_BLE5_RADIO_SETUP_t RF_cmdBle5RadioSetup =
{
    .commandNo = 0x1820,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .defaultPhy.mainMode = 0x0,
    .defaultPhy.coding = 0x0,
    .__dummy0 = 0x00,
    .config.frontEndMode = 0x0,
    .config.biasMode = 0x0,
    .config.analogCfgMode = 0x0,
    .config.bNoFsPowerUp = 0x0,
    .txPower = 0x2558,
    .pRegOverrideCommon = pOverridesCommon,
    .pRegOverride1Mbps = pOverrides1Mbps,
    .pRegOverride2Mbps = pOverrides2Mbps,
    .pRegOverrideCoded = pOverridesCoded,
};

// CMD_FS
// Frequency Synthesizer Programming Command
rfc_CMD_FS_t RF_cmdFs =
{
    .commandNo = 0x0803,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = 0x0,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x0,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .frequency = 0x0962,
    .fractFreq = 0x0000,
    .synthConf.bTxMode = 0x0,
    .synthConf.refFreq = 0x0,
    .__dummy0 = 0x00,
    .__dummy1 = 0x00,
    .__dummy2 = 0x00,
    .__dummy3 = 0x0000,
};

// Structure for CMD_BLE_ADV_NC.pParams
rfc_bleAdvPar_t bleAdvPar =
{
    .pRxQ = 0, // INSERT APPLICABLE POINTER: (dataQueue_t*)&xxx
    .rxConfig.bAutoFlushIgnored = 0x0,
    .rxConfig.bAutoFlushCrcErr = 0x0,
    .rxConfig.bAutoFlushEmpty = 0x0,
    .rxConfig.bIncludeLenByte = 0x0,
    .rxConfig.bIncludeCrc = 0x0,
    .rxConfig.bAppendRssi = 0x0,
    .rxConfig.bAppendStatus = 0x0,
    .rxConfig.bAppendTimestamp = 0x0,
    .advConfig.advFilterPolicy = 0x0,
    .advConfig.deviceAddrType = 0x0,
    .advConfig.peerAddrType = 0x0,
    .advConfig.bStrictLenFilter = 0x0,
    .advConfig.chSel = 0x0,
    .advConfig.privIgnMode = 0x0,
    .advConfig.rpaMode = 0x0,
    .advLen = ADVLEN,
    .scanRspLen = 0x00,
    .pAdvData = (uint8_t*)&ADV_DATA.LEN, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .pScanRspData = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .pDeviceAddress = (uint16_t*)&devAddress, // INSERT APPLICABLE POINTER: (uint16_t*)&xxx
    .pWhiteList = 0, // INSERT APPLICABLE POINTER: (uint32_t*)&xxx
    .__dummy0 = 0x0000,
    .__dummy1 = 0x00,
    .endTrigger.triggerType = 0x1,
    .endTrigger.bEnaCmd = 0x0,
    .endTrigger.triggerNo = 0x0,
    .endTrigger.pastTrig = 0x0,
    .endTime = 0x00000000,
};

// CMD_BLE_ADV_NC
// BLE Non-Connectable Advertiser Command
rfc_CMD_BLE_ADV_NC_t RF_cmdBleAdvNc[3] = {
{
    .commandNo = 0x1805,
    .status = 0x0000,
    .pNextOp = (rfc_radioOp_t*)&RF_cmdBleAdvNc[1], // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 0x00000000,
    .startTrigger.triggerType = TRIG_NOW,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = COND_ALWAYS, //0x1,
    .condition.nSkip = 0x0,
    .channel = 0x25,
    .whitening.init = 0, //0x65,
    .whitening.bOverride = 0, //0x1,
    .pParams = &bleAdvPar,
    .pOutput = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
},
{
    .commandNo = 0x1805,
    .status = 0x0000,
    .pNextOp = (rfc_radioOp_t*)&RF_cmdBleAdvNc[2], // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 40000,
    .startTrigger.triggerType = TRIG_NOW, //TRIG_REL_PREVSTART,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = COND_ALWAYS,
    .condition.nSkip = 0x0,
    .channel = 0x26,
    .whitening.init = 0, //0x65,
    .whitening.bOverride = 0, //0x1,
    .pParams = &bleAdvPar,
    .pOutput = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
},
{
    .commandNo = 0x1805,
    .status = 0x0000,
    .pNextOp = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
    .startTime = 40000,
    .startTrigger.triggerType = TRIG_NOW, //TRIG_REL_PREVSTART,
    .startTrigger.bEnaCmd = 0x0,
    .startTrigger.triggerNo = 0x0,
    .startTrigger.pastTrig = 0x1,
    .condition.rule = 0x1,
    .condition.nSkip = 0x0,
    .channel = 0x27,
    .whitening.init = 0, //0x65,
    .whitening.bOverride = 0, //0x1,
    .pParams = &bleAdvPar,
    .pOutput = 0, // INSERT APPLICABLE POINTER: (uint8_t*)&xxx
},
};
