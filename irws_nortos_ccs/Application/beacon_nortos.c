/*
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/***** Includes *****/
/* For usleep() */
//#include <unistd.h>
/* Standard C Libraries */
#include <stdlib.h>

/* TI Drivers */
#include <ti/drivers/rf/RF.h>
#include <ti/drivers/PIN.h>
#include <ti/drivers/pin/PINCC26XX.h>

// DriverLib
#include <driverlib/aon_batmon.h>
#include DeviceFamily_constructPath(driverlib/rf_prop_mailbox.h)

/* Board Header files */
//#include "Board.h"
#include "irws_ex_include.h"
#include "rfs/CC2640R2_RSM/smartrf_settings/smartrf_settings.h"

#if(sensor==23)
#include "scs/nortos/TSOP38140/scif_tsop38140.h"
#elif(sensor==711)
#include "scs/nortos/HX711/scif_hx711.h"
#endif

/***** Defines *****/

/* TX Configuration */
#define PACKET_INTERVAL                 50*4000   //50ms @ 4 MHz
#define ABEACON_COUNT                   4
//#define ADV_PERIOD                      (6000 * 4000) - ((PACKET_INTERVAL * ABEACON_COUNT) + BBEACON_DELAY)
#define ADVLEN                          3
#define ADCNexp    2

#if(sensor==23)
#define IR_PEROID               6
#elif(sensor==711)
#define IR_PEROID               120
#endif
#define DATA_HOURS              360 / IR_PEROID - 1
#define BATT_HOURS              4 * 3600 / IR_PEROID
#define ADC_BATT2_6V            86
#define ADCN                    2
#define INTERVAL10MS            40000 // 1 ms = 4000 RAT tick
/* Do power measurement */
//#define POWER_MEASUREMENT

/***** Prototypes *****/
extern void Power_idleFunc(void);
extern uint32_t scifOsalEnterCriticalSection(void);
extern void scifOsalLeaveCriticalSection(uint32_t key);

/***** Variable declarations *****/
volatile bool dataReceived = false, txDone = false;

static RF_Object rfObject;
static RF_Handle rfHandle;

uint8_t advLen = ADVLEN, m, n;

/***** Function definitions *****/
void irwsStart();
void irwsCallback(RF_Handle handle, RF_CmdHandle command, RF_EventMask events);

void *mainThread(void *arg0)
{
    uint32_t key, batt; // time;
    RF_CmdHandle ch;
    RF_Params rfParams;
    RF_Params_init(&rfParams);
    rfParams.nInactivityTimeout = 0; /* Do not use the default value for this */

    /* Request access to the radio */
    RF_cmdBle5RadioSetup.txPower = (uint16_t)RF_TxPowerTable_findValue(txPowerTable, -3).rawValue;
    rfHandle = RF_open(&rfObject, &RF_ble, (RF_RadioSetup*)&RF_cmdBle5RadioSetup, &rfParams);
    dataReceived = false;
#if(sensor==23)
    ADV_DATA.SQN.TYPE = 0;
#elif(sensor==711)
    ADV_DATA.SQN.TYPE = 1;
#endif
    ADV_DATA.SQN.SEQ = 3;
    irwsStart();
    if (rfHandle == NULL) while(1);
    // urfi_initAdvCmd();

    while(1)
    {
        key = scifOsalEnterCriticalSection();
        while (dataReceived == false)
        {
           Power_idleFunc();
           scifOsalLeaveCriticalSection(key);
           // Let 'readCallback()' execute...
           key = scifOsalEnterCriticalSection();
        }
        dataReceived = false;
        scifOsalLeaveCriticalSection(key);

#if(sensor==23)
        ADV_DATA.SQN.BUZZ0 = scifTsop38140TaskData.irled.output.buzz;
        ADV_DATA.SQN.BUZZ1 = scifTsop38140TaskData.irled.state.buzz;
        ADV_DATA.SQN.USB = scifTsop38140TaskData.irled.state.out[1] == 0 ? 1 : 0;

        if(scifTsop38140TaskData.irled.state.bCount >= scifTsop38140TaskData.irled.cfg.bCount) {
            scifTsop38140TaskData.irled.state.bCount = 0;

            // Battery voltage (bit 10:8 - integer, but 7:0 fraction)
            batt = AONBatMonBatteryVoltageGet();
            //batt = (batt * 125) >> 5; // convert V to mV

            ADV_DATA.BATT = (batt >> 3) - 0x40;
            ADV_DATA.LEN = ADVLEN - 1;
        } else {
            ADV_DATA.LEN = ADVLEN - 2;
        }
#elif(sensor==711)
        ADV_DATA.SQN.BUZZ0 = scifHx711TaskData.adc24bit.output.buzz;
        ADV_DATA.SQN.BUZZ1 = scifHx711TaskData.adc24bit.state.buzz;

        *((uint16_t *) ADV_DATA.ADC) = scifHx711TaskData.adc24bit.output.adcVal;

        if(scifHx711TaskData.adc24bit.state.bCount >= scifHx711TaskData.adc24bit.cfg.bCount) {
            scifHx711TaskData.adc24bit.state.bCount = 0;

            // Battery voltage (bit 10:8 - integer, but 7:0 fraction)
            batt = AONBatMonBatteryVoltageGet();
            //batt = (batt * 125) >> 5; // convert V to mV

            ADV_DATA.BATT = (batt >> 3) - 0x40;
            ADV_DATA.LEN = ADVLEN + 1;
        } else {
            ADV_DATA.LEN = ADVLEN;
        }
#endif
        RF_cmdBleAdvNc[0].pParams->advLen = ADV_DATA.LEN + 1;
        //time = RF_getCurrentTime();
        ADV_DATA.SQN.SEQ++;
        //ADV_DATA.SQN.RND = 3;
        //for(n = 0; n < ADCN; n++) {
          for(m = 0; m < 3; m++) {
            RF_cmdBleAdvNc[m].status = IDLE; // clear command status values
            //RF_cmdBleAdvNc[m].startTime = time + (n * 10 + m) * INTERVAL10MS; //RF_convertMsToRatTicks(10);
          }
          /* txDone = false;
          ADV_DATA.SQN.RND++;
          if(n < ADCN - 1) {
              ch = RF_postCmd(rfHandle, (RF_Op*)&RF_cmdBleAdvNc, RF_PriorityNormal, &irwsCallback, 0);
              //assert(ch != RF_ALLOC_ERROR); // The command queue is full
              while(!txDone) Power_idleFunc();
          } else */
              ch = RF_postCmd(rfHandle, (RF_Op*)&RF_cmdBleAdvNc, RF_PriorityNormal, NULL, 0);
        //}
        // RF_close(rfHandle);
#if(sensor==23)
        scifTsop38140TaskData.irled.state.exit = 0;
#elif(sensor==711)
        scifHx711TaskData.adc24bit.state.exit = 0;
#endif
    } // while(1)
}  // mainThread

void ctrlReadyCallback(void) {

} // ctrlReadyCallback




void taskAlertCallback(void) {

    // Clear the ALERT interrupt source
    scifClearAlertIntSource();

    /* Notify the main thread that data has been received */
    dataReceived = true;

    // Acknowledge the alert event
    scifAckAlertEvents();

} // taskAlertCallback

void irwsStart() {

    // Enable power domains
    PRCMPowerDomainOn(PRCM_DOMAIN_PERIPH);
    PRCMLoadSet();
    while (PRCMPowerDomainStatus(PRCM_DOMAIN_PERIPH) != PRCM_DOMAIN_POWER_ON);

    // Enable the GPIO module
    PRCMPeripheralRunEnable(PRCM_PERIPH_GPIO);
    PRCMPeripheralSleepEnable(PRCM_PERIPH_GPIO);
    PRCMPeripheralDeepSleepEnable(PRCM_PERIPH_GPIO);
    PRCMLoadSet();
    while (!PRCMLoadGet());

    // In this example, we keep the AUX domain access permanently enabled
    //scifOsalEnableAuxDomainAccess();

    // Initialize and start the Sensor Controller
    scifOsalRegisterCtrlReadyCallback(ctrlReadyCallback);
    scifOsalRegisterTaskAlertCallback(taskAlertCallback);
    /*IOCIODrvStrengthSet(IOID_9, IOC_CURRENT_4MA, PIN_DRVSTR_MAX);
    IOCIODrvStrengthSet(IOID_0, IOC_CURRENT_8MA, PIN_DRVSTR_MAX);
    IOCIODrvStrengthSet(IOID_1, IOC_CURRENT_8MA, PIN_DRVSTR_MAX);*/
#if(sensor==23)
    scifInit(&scifTsop38140DriverSetup);
    scifTsop38140StartRtcTicksNow(0x00060000);  //6s
#elif(sensor==711)
    scifInit(&scifHx711DriverSetup);
    scifHx711StartRtcTicksNow(0x00400000);  //64s
#endif
    IntMasterEnable();
    AONRTCEnable();

#if(sensor==23)
    scifStartTasksNbl(1<<SCIF_TSOP38140_IRLED_TASK_ID);
#elif(sensor==711)
    scifStartTasksNbl(1<<SCIF_HX711_ADC24BIT_TASK_ID);
#endif
}

void irwsCallback(RF_Handle handle, RF_CmdHandle command, RF_EventMask events)
{
    if (events & RF_EventLastCmdDone) {
        txDone = true;
        //m += 1;
    }
}
