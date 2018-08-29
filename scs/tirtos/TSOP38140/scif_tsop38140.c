/// \addtogroup module_scif_driver_setup
//@{
#include "scif_tsop38140.h"
#include "scif_framework.h"
#undef DEVICE_FAMILY_PATH
#if defined(DEVICE_FAMILY)
    #define DEVICE_FAMILY_PATH(x) <ti/devices/DEVICE_FAMILY/x>
#elif defined(DeviceFamily_CC26X0)
    #define DEVICE_FAMILY_PATH(x) <ti/devices/cc26x0/x>
#elif defined(DeviceFamily_CC26X0R2)
    #define DEVICE_FAMILY_PATH(x) <ti/devices/cc26x0r2/x>
#elif defined(DeviceFamily_CC13X0)
    #define DEVICE_FAMILY_PATH(x) <ti/devices/cc13x0/x>
#else
    #define DEVICE_FAMILY_PATH(x) <x>
#endif
#include DEVICE_FAMILY_PATH(inc/hw_types.h)
#include DEVICE_FAMILY_PATH(inc/hw_memmap.h)
#include DEVICE_FAMILY_PATH(inc/hw_aon_event.h)
#include DEVICE_FAMILY_PATH(inc/hw_aon_rtc.h)
#include DEVICE_FAMILY_PATH(inc/hw_aon_wuc.h)
#include DEVICE_FAMILY_PATH(inc/hw_aux_sce.h)
#include DEVICE_FAMILY_PATH(inc/hw_aux_smph.h)
#include DEVICE_FAMILY_PATH(inc/hw_aux_evctl.h)
#include DEVICE_FAMILY_PATH(inc/hw_aux_aiodio.h)
#include DEVICE_FAMILY_PATH(inc/hw_aux_timer.h)
#include DEVICE_FAMILY_PATH(inc/hw_aux_wuc.h)
#include DEVICE_FAMILY_PATH(inc/hw_event.h)
#include DEVICE_FAMILY_PATH(inc/hw_ints.h)
#include DEVICE_FAMILY_PATH(inc/hw_ioc.h)
#include <string.h>
#if defined(__IAR_SYSTEMS_ICC__)
    #include <intrinsics.h>
#endif


// OSAL function prototypes
uint32_t scifOsalEnterCriticalSection(void);
void scifOsalLeaveCriticalSection(uint32_t key);




/// Firmware image to be uploaded to the AUX RAM
static const uint16_t pAuxRamImage[] = {
    /*0x0000*/ 0x1408, 0x040C, 0x1408, 0x042C, 0x1408, 0x0447, 0x1408, 0x044D, 0x4436, 0x2437, 0xAEFE, 0xADB7, 0x6442, 0x7000, 0x7C6B, 0x6872, 
    /*0x0020*/ 0x0068, 0x1425, 0x6873, 0x0069, 0x1425, 0x6874, 0x006A, 0x1425, 0x786B, 0xF801, 0xFA01, 0xBEF2, 0x7870, 0x6872, 0xFD0E, 0x6874, 
    /*0x0040*/ 0xED92, 0xFD06, 0x7C70, 0x642D, 0x0450, 0x786B, 0x8F1F, 0xED8F, 0xEC01, 0xBE01, 0xADB7, 0x8DB7, 0x6630, 0x6542, 0x0000, 0x1870, 
    /*0x0060*/ 0x9D88, 0x9C01, 0xB60D, 0x1067, 0xAF19, 0xAA00, 0xB609, 0xA8FF, 0xAF39, 0xBE06, 0x0C6B, 0x8869, 0x8F08, 0xFD47, 0x9DB7, 0x086B, 
    /*0x0080*/ 0x8801, 0x8A01, 0xBEEC, 0x262F, 0xAEFE, 0x4630, 0x0450, 0x5527, 0x6642, 0x0000, 0x0C6B, 0x140B, 0x0450, 0x6742, 0x03FF, 0x0C6D, 
    /*0x00A0*/ 0x786C, 0x686D, 0xED37, 0xB605, 0x0000, 0x0C6C, 0x7C71, 0x652D, 0x0C6D, 0x786D, 0x686E, 0xFD0E, 0xF801, 0xE92B, 0xFD0E, 0xBE01, 
    /*0x00C0*/ 0x6436, 0xBDB7, 0x241A, 0xA6FE, 0xADB7, 0x641A, 0xADB7, 0x0000, 0x0087, 0x008F, 0x0116, 0x0000, 0x0000, 0xFFFF, 0x0000, 0x0000, 
    /*0x00E0*/ 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0960, 0x003C, 0x0004, 0x0009, 0x0000, 0x0960, 0x0000, 0x003C, 0x0000, 0x0001, 0x0001, 
    /*0x0100*/ 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x7878, 0x6000, 0x1517, 0x7878, 0x1526, 0x0001, 0x0C67, 0xADB7, 0x087D, 
    /*0x0120*/ 0x8A00, 0xBE7E, 0x7877, 0x152E, 0x7071, 0x6005, 0x1536, 0x0000, 0x0C79, 0x2001, 0x0000, 0x8A06, 0xA60C, 0x5001, 0x660F, 0x1003, 
    /*0x0140*/ 0x8500, 0xFD47, 0x460F, 0x108B, 0x8500, 0xFD47, 0xD8FF, 0xBEF6, 0x04AF, 0x112C, 0x9B0C, 0x1000, 0x9B09, 0x640B, 0xCDB1, 0x5003, 
    /*0x0160*/ 0x153C, 0x107E, 0xFF39, 0x107E, 0x9F19, 0x9A00, 0xBE07, 0xAA00, 0xBE03, 0x0001, 0x0C79, 0x0009, 0x2000, 0x04C5, 0x112C, 0x9B0C, 
    /*0x0180*/ 0x1000, 0x9B09, 0x640B, 0xCDB1, 0x2001, 0x8801, 0x8A09, 0xAED3, 0x7877, 0x1526, 0x0879, 0x8A01, 0xBE0E, 0x087B, 0x8A00, 0xBE07, 
    /*0x01A0*/ 0x0005, 0x0C76, 0x0876, 0x0C7C, 0x0001, 0x0C7D, 0x04DA, 0x087C, 0x88FF, 0x0C7C, 0x04E8, 0x087B, 0x8A01, 0xBE07, 0x003C, 0x0C76, 
    /*0x01C0*/ 0x0876, 0x0C7C, 0x0001, 0x0C7D, 0x04E8, 0x087C, 0x88FF, 0x0C7C, 0x0879, 0x0C7B, 0x087C, 0x8A00, 0xBE04, 0x0876, 0x0C7C, 0x0001, 
    /*0x01E0*/ 0x0C7D, 0x087A, 0x1875, 0x8D29, 0xBE02, 0x0001, 0x0C7D, 0x087D, 0x8A01, 0xBE05, 0x0000, 0x0C7D, 0x086C, 0x8201, 0x0C6C, 0x0879, 
    /*0x0200*/ 0x8A01, 0xBE0E, 0x860F, 0x03A0, 0x8B0C, 0x0001, 0x8B09, 0x640B, 0x0000, 0x7878, 0x1543, 0xCDB1, 0x8801, 0x8A64, 0xAEFA, 0x440B, 
    /*0x0220*/ 0x087A, 0x8801, 0x0C7A, 0x0001, 0x0C67, 0xADB7, 0xADB7, 0xDD47, 0xDDAB, 0xD810, 0xF007, 0xED87, 0xED87, 0x4003, 0xCD87, 0xCD87, 
    /*0x0240*/ 0xCD92, 0xFF05, 0xFD04, 0xFD0E, 0xFF25, 0xADB7, 0xED47, 0xEDAB, 0xE816, 0xF007, 0x5001, 0xDD87, 0xDF26, 0xADB7, 0xED47, 0xEDAB, 
    /*0x0260*/ 0xE814, 0xF007, 0x5001, 0xDD87, 0xDF26, 0xADB7, 0xFB0C, 0xEDA4, 0xEB09, 0x640B, 0xCDB1, 0xADB7, 0xE913, 0xEDA0, 0xF912, 0xFD0E, 
    /*0x0280*/ 0xFD8D, 0xF001, 0xADB7, 0xED47, 0xEDAB, 0xE818, 0xF007, 0x5001, 0xDD87, 0xDF26, 0xADB7
};


/// Look-up table that converts from AUX I/O index to MCU IOCFG offset
static const uint8_t pAuxIoIndexToMcuIocfgOffsetLut[] = {
    0, 0, 0, 36, 32, 28, 24, 20, 8, 4, 0, 0, 0, 0, 0, 0
};


/** \brief Look-up table of data structure information for each task
  *
  * There is one entry per data structure (\c cfg, \c input, \c output and \c state) per task:
  * - [31:20] Data structure size (number of 16-bit words)
  * - [19:12] Buffer count (when 2+, first data structure is preceded by buffering control variables)
  * - [11:0] Address of the first data structure
  */
static const uint32_t pScifTaskDataStructInfoLut[] = {
//  cfg         input       output      state       
    0x004010EA, 0x00000000, 0x001010F2, 0x00D010F4  // IRLED
};




// No run-time logging task data structure signatures needed in this project




// No task-specific initialization functions




// No task-specific uninitialization functions




/** \brief Initilializes task resource hardware dependencies
  *
  * This function is called by the internal driver initialization function, \ref scifInit().
  */
static void scifTaskResourceInit(void) {
    scifInitIo(3, AUXIOMODE_INPUT, -1, 0);
    scifInitIo(4, AUXIOMODE_OPEN_SOURCE | (2 << BI_AUXIOMODE_OUTPUT_DRIVE_STRENGTH), -1, 0);
    scifInitIo(9, AUXIOMODE_OPEN_SOURCE | (2 << BI_AUXIOMODE_OUTPUT_DRIVE_STRENGTH), -1, 0);
    scifInitIo(10, AUXIOMODE_OUTPUT | (2 << BI_AUXIOMODE_OUTPUT_DRIVE_STRENGTH), -1, 0);
} // scifTaskResourceInit




/** \brief Uninitilializes task resource hardware dependencies
  *
  * This function is called by the internal driver uninitialization function, \ref scifUninit().
  */
static void scifTaskResourceUninit(void) {
    scifUninitIo(3, -1);
    scifUninitIo(4, -1);
    scifUninitIo(9, -1);
    scifUninitIo(10, -1);
} // scifTaskResourceUninit




/** \brief Re-initializes I/O pins used by the specified tasks
  *
  * It is possible to stop a Sensor Controller task and let the System CPU borrow and operate its I/O
  * pins. For example, the Sensor Controller can operate an SPI interface in one application state while
  * the System CPU with SSI operates the SPI interface in another application state.
  *
  * This function must be called before \ref scifExecuteTasksOnceNbl() or \ref scifStartTasksNbl() if
  * I/O pins belonging to Sensor Controller tasks have been borrowed System CPU peripherals.
  *
  * \param[in]      bvTaskIds
  *     Bit-vector of task IDs for the task I/Os to be re-initialized
  */
void scifTsop38140ReinitTaskIo(uint32_t bvTaskIds) {
    if (bvTaskIds & (1 << SCIF_TSOP38140_IRLED_TASK_ID)) {
        scifReinitIo(3, -1, 0);
        scifReinitIo(4, -1, 2);
        scifReinitIo(9, -1, 2);
        scifReinitIo(10, -1, 2);
    }
} // scifTsop38140ReinitTaskIo




/// Driver setup data, to be used in the call to \ref scifInit()
const SCIF_DATA_T scifTsop38140DriverSetup = {
    (volatile SCIF_INT_DATA_T*) 0x400E00D6,
    (volatile SCIF_TASK_CTRL_T*) 0x400E00E0,
    (volatile uint16_t*) 0x400E00CE,
    0x0000,
    sizeof(pAuxRamImage),
    pAuxRamImage,
    pScifTaskDataStructInfoLut,
    pAuxIoIndexToMcuIocfgOffsetLut,
    scifTaskResourceInit,
    scifTaskResourceUninit,
    (volatile uint16_t*) NULL,
    (volatile uint16_t*) NULL,
    NULL
};




/** \brief Starts or modifies RTC-based task scheduling tick generation
  *
  * RTC-based tick generation will wake up the Sensor Controller first at the specified value of the RTC
  * and then periodically at the specified interval. The application must call this function after
  * calling \ref scifInit().
  *
  * The application must ensure that:
  * - \a tickStart is not in the past (prefer using \ref scifTsop38140StartRtcTicksNow() to avoid this)
  * - \a tickPeriod is not too short. RTC ticks will be skipped silently if the Sensor Controller does
  *   not complete its tasks within a single tick interval.
  *
  * \param[in]      tickStart
  *     RTC value when the first tick is generated:
  *     - Bits 31:16 = seconds
  *     - Bits 15:0 = 1/65536 of a second
  * \param[in]      tickPeriod
  *     Interval at which subsequent ticks are generated:
  *     - Bits 31:16 = seconds
  *     - Bits 15:0 = 1/65536 of a second
  */
void scifTsop38140StartRtcTicks(uint32_t tickStart, uint32_t tickPeriod) {
    HWREG(AON_RTC_BASE + AON_RTC_O_CH2CMP) = tickStart;
    HWREG(AON_RTC_BASE + AON_RTC_O_CH2CMPINC) = tickPeriod;
    HWREG(AON_RTC_BASE + AON_RTC_O_CHCTL) |= AON_RTC_CHCTL_CH2_EN_M | AON_RTC_CHCTL_CH2_CONT_EN_M;
    HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) =
        (HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) & ~AON_EVENT_AUXWUSEL_WU0_EV_M) |
        (AON_EVENT_AUXWUSEL_WU0_EV_RTC_CH2);
} // scifTsop38140StartRtcTicks




/** \brief Starts or modifies RTC-based task scheduling tick generation
  *
  * RTC-based tick generation will wake up the Sensor Controller first after approximately 128 us and
  * then periodically at the specified interval. The application must call this function after calling
  * \ref scifInit().
  *
  * The application must ensure that \a tickPeriod is not too short. RTC ticks will be skipped silently
  * if the Sensor Controller does not complete its tasks within a single tick interval.
  *
  * \param[in]      tickPeriod
  *     Interval at which subsequent ticks are generated:
  *     - Bits 31:16 = seconds
  *     - Bits 15:0 = 1/65536 of a second
  */
void scifTsop38140StartRtcTicksNow(uint32_t tickPeriod) {
    uint32_t key, sec, subsec;
    key = scifOsalEnterCriticalSection();
    sec = HWREG(AON_RTC_BASE + AON_RTC_O_SEC);
    subsec = HWREG(AON_RTC_BASE + AON_RTC_O_SUBSEC);
    scifTsop38140StartRtcTicks(((sec << 16) | (subsec >> 16)) + 8, tickPeriod);
    scifOsalLeaveCriticalSection(key);
} // scifTsop38140StartRtcTicksNow




/** \brief Stops RTC-based task scheduling tick generation
  *
  * The application must call this function before calling \ref scifUninit().
  */
void scifTsop38140StopRtcTicks(void) {
    HWREG(AON_RTC_BASE + AON_RTC_O_CHCTL) &= ~(AON_RTC_CHCTL_CH2_EN_M | AON_RTC_CHCTL_CH2_CONT_EN_M);
    HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) =
        (HWREG(AON_EVENT_BASE + AON_EVENT_O_AUXWUSEL) & ~AON_EVENT_AUXWUSEL_WU0_EV_M) |
        (AON_EVENT_AUXWUSEL_WU0_EV_NONE);
    HWREG(AON_RTC_BASE + AON_RTC_O_SYNC);
} // scifTsop38140StopRtcTicks


//@}


// Generated by DESKTOP-NJ22OJR at 2018-08-19 12:29:49.871
