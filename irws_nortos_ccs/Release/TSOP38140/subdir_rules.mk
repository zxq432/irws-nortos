################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
TSOP38140/scif_framework.obj: /root/workspace_v8/scs/nortos/TSOP38140/scif_framework.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=none -me -O4 --include_path="/root/workspace_v8/irws_nortos_ccs" --include_path="/opt/ti/xdctools_3_50_07_20_core" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/devices/cc26x0r2" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/source" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/nortos" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/nortos/posix" --include_path="/root/workspace_v8" --include_path="/root/workspace_v8/source/ti/blestack/boards/CC2640R2_RSM" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=NORTOS --define=sensor=23 --define=Display_DISABLE_ALL --define=DeviceFamily_CC26X0R2 --define=BOARD_DISPLAY_USE_LCD=0 --define=BOARD_DISPLAY_USE_UART=0 --define=BOARD_DISPLAY_USE_UART_ANSI=1 --define=CC2640R2_RSM --define=CC26XX --define=CC26XX_R2 --define=POWER_SAVING --define=RF_SINGLEMODE --define=USE_DEFAULT_USER_CFG --define=xdc_runtime_Assert_DISABLE_ALL --define=xdc_runtime_Log_DISABLE_ALL -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="TSOP38140/scif_framework.d_raw" --obj_directory="TSOP38140" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

TSOP38140/scif_osal_none.obj: /root/workspace_v8/scs/nortos/TSOP38140/scif_osal_none.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=none -me -O4 --include_path="/root/workspace_v8/irws_nortos_ccs" --include_path="/opt/ti/xdctools_3_50_07_20_core" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/devices/cc26x0r2" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/source" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/nortos" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/nortos/posix" --include_path="/root/workspace_v8" --include_path="/root/workspace_v8/source/ti/blestack/boards/CC2640R2_RSM" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=NORTOS --define=sensor=23 --define=Display_DISABLE_ALL --define=DeviceFamily_CC26X0R2 --define=BOARD_DISPLAY_USE_LCD=0 --define=BOARD_DISPLAY_USE_UART=0 --define=BOARD_DISPLAY_USE_UART_ANSI=1 --define=CC2640R2_RSM --define=CC26XX --define=CC26XX_R2 --define=POWER_SAVING --define=RF_SINGLEMODE --define=USE_DEFAULT_USER_CFG --define=xdc_runtime_Assert_DISABLE_ALL --define=xdc_runtime_Log_DISABLE_ALL -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="TSOP38140/scif_osal_none.d_raw" --obj_directory="TSOP38140" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

TSOP38140/scif_tsop38140.obj: /root/workspace_v8/scs/nortos/TSOP38140/scif_tsop38140.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=none -me -O4 --include_path="/root/workspace_v8/irws_nortos_ccs" --include_path="/opt/ti/xdctools_3_50_07_20_core" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/source/ti/devices/cc26x0r2" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/tirtos/packages" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/source" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/nortos" --include_path="/root/ti/simplelink_cc2640r2_sdk_2_20_00_49/kernel/nortos/posix" --include_path="/root/workspace_v8" --include_path="/root/workspace_v8/source/ti/blestack/boards/CC2640R2_RSM" --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --define=NORTOS --define=sensor=23 --define=Display_DISABLE_ALL --define=DeviceFamily_CC26X0R2 --define=BOARD_DISPLAY_USE_LCD=0 --define=BOARD_DISPLAY_USE_UART=0 --define=BOARD_DISPLAY_USE_UART_ANSI=1 --define=CC2640R2_RSM --define=CC26XX --define=CC26XX_R2 --define=POWER_SAVING --define=RF_SINGLEMODE --define=USE_DEFAULT_USER_CFG --define=xdc_runtime_Assert_DISABLE_ALL --define=xdc_runtime_Log_DISABLE_ALL -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="TSOP38140/scif_tsop38140.d_raw" --obj_directory="TSOP38140" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


