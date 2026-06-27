// Define to prevent recursive inclusion  // 定义以防止递归包含
#ifndef CONFIG_H
#define CONFIG_H

#include "stm32f1xx_hal.h"

// ############################### VARIANT SELECTION ###############################
// 变体选择
// PlatformIO: uncomment desired variant in platformio.ini
// PlatformIO: 在platformio.ini中取消注释所需的变体
// Keil uVision: select desired variant from the Target drop down menu (to the right of the Load button)
// Keil uVision: 从Target下拉菜单中选择所需的变体（在Load按钮右侧）
// Ubuntu: define the desired build variant here if you want to use make in console
// Ubuntu: 如果想在控制台使用make，在此定义所需的构建变体
// or use VARIANT environment variable for example like "make -e VARIANT=VARIANT_NUNCHUK". Select only one at a time.
// 或使用VARIANT环境变量，例如"make -e VARIANT=VARIANT_NUNCHUK"。一次只能选择一个。
#if !defined(PLATFORMIO)
  //#define VARIANT_ADC         // Variant for control via ADC input  // 用于通过ADC输入控制的变体
  //#define VARIANT_USART       // Variant for Serial control via USART3 input  // 用于通过USART3输入串行控制的变体
  //#define VARIANT_NUNCHUK     // Variant for Nunchuk controlled vehicle build  // 用于Nunchuk控制车辆构建的变体
  //#define VARIANT_PPM         // Variant for RC-Remote with PPM-Sum Signal  // 用于带PPM-Sum信号的遥控器的变体
  //#define VARIANT_PWM         // Variant for RC-Remote with PWM Signal  // 用于带PWM信号的遥控器的变体
  //#define VARIANT_IBUS        // Variant for RC-Remotes with FLYSKY IBUS  // 用于带FLYSKY IBUS的遥控器的变体
  //#define VARIANT_HOVERCAR    // Variant for HOVERCAR build  // 用于HOVERCAR构建的变体
  //#define VARIANT_HOVERBOARD  // Variant for HOVERBOARD build  // 用于HOVERBOARD构建的变体
  //#define VARIANT_TRANSPOTTER // Variant for TRANSPOTTER build https://github.com/NiklasFauth/hoverboard-firmware-hack/wiki/Build-Instruction:-TranspOtter https://hackaday.io/project/161891-transpotter-ng  // 用于TRANSPOTTER构建的变体
  //#define VARIANT_SKATEBOARD  // Variant for SKATEBOARD build  // 用于SKATEBOARD构建的变体
#endif
// ########################### END OF VARIANT SELECTION ############################
// 变体选择结束


// ############################### DO-NOT-TOUCH SETTINGS ###############################
// 请勿修改设置
#define PWM_FREQ            16000     // PWM frequency in Hz / is also used for buzzer  // PWM频率(Hz)/也用于蜂鸣器
#define DEAD_TIME              48     // PWM deadtime  // PWM死区时间
#ifdef VARIANT_TRANSPOTTER
  #define DELAY_IN_MAIN_LOOP    2
#else
  #define DELAY_IN_MAIN_LOOP    5     // in ms. default 5. it is independent of all the timing critical stuff. do not touch if you do not know what you are doing.  // 以毫秒为单位。默认5。它独立于所有时序关键内容。如果不知道自己在做什么，请勿修改。
#endif
#define TIMEOUT                20     // number of wrong / missing input commands before emergency off  // 紧急关闭前错误/缺失输入命令的数量
#define A2BIT_CONV             50     // A to bit for current conversion on ADC. Example: 1 A = 50, 2 A = 100, etc  // ADC上电流转换的安培到比特值。例如：1 A = 50, 2 A = 100等
// #define PRINTF_FLOAT_SUPPORT          // [-] Uncomment this for printf to support float on Serial Debug. It will increase code size! Better to avoid it!  // 取消注释此行以使printf在串行调试中支持浮点数。这会增加代码大小！最好避免使用！

// ADC conversion time definitions  // ADC转换时间定义
#define ADC_CONV_TIME_1C5       (14)  //Total ADC clock cycles / conversion = (  1.5+12.5)  // 总ADC时钟周期/转换 = (1.5+12.5)
#define ADC_CONV_TIME_7C5       (20)  //Total ADC clock cycles / conversion = (  7.5+12.5)  // 总ADC时钟周期/转换 = (7.5+12.5)
#define ADC_CONV_TIME_13C5      (26)  //Total ADC clock cycles / conversion = ( 13.5+12.5)  // 总ADC时钟周期/转换 = (13.5+12.5)
#define ADC_CONV_TIME_28C5      (41)  //Total ADC clock cycles / conversion = ( 28.5+12.5)  // 总ADC时钟周期/转换 = (28.5+12.5)
#define ADC_CONV_TIME_41C5      (54)  //Total ADC clock cycles / conversion = ( 41.5+12.5)  // 总ADC时钟周期/转换 = (41.5+12.5)
#define ADC_CONV_TIME_55C5      (68)  //Total ADC clock cycles / conversion = ( 55.5+12.5)  // 总ADC时钟周期/转换 = (55.5+12.5)
#define ADC_CONV_TIME_71C5      (84)  //Total ADC clock cycles / conversion = ( 71.5+12.5)  // 总ADC时钟周期/转换 = (71.5+12.5)
#define ADC_CONV_TIME_239C5     (252) //Total ADC clock cycles / conversion = (239.5+12.5)  // 总ADC时钟周期/转换 = (239.5+12.5)

// This settings influences the actual sample-time. Only use definitions above
// 此设置影响实际采样时间。仅使用上述定义
// This parameter needs to be the same as the ADC conversion for Current Phase of the FIRST Motor in setup.c
// 此参数需要与setup.c中第一个电机的电流相位的ADC转换相同
#define ADC_CONV_CLOCK_CYCLES   (ADC_CONV_TIME_7C5)

// Set the configured ADC divider. This parameter needs to be the same ADC divider as PeriphClkInit.AdcClockSelection (see main.c)
// 设置配置的ADC分频器。此参数需要与PeriphClkInit.AdcClockSelection中的ADC分频器相同（见main.c）
#define ADC_CLOCK_DIV           (4)

// ADC Total conversion time: this will be used to offset TIM8 in advance of TIM1 to align the Phase current ADC measurement
// ADC总转换时间：这将用于将TIM8提前于TIM1以对齐相位电流ADC测量
// This parameter is used in setup.c
// 此参数在setup.c中使用
#define ADC_TOTAL_CONV_TIME     (ADC_CLOCK_DIV * ADC_CONV_CLOCK_CYCLES) // = ((SystemCoreClock / ADC_CLOCK_HZ) * ADC_CONV_CLOCK_CYCLES), where ADC_CLOCK_HZ = SystemCoreClock/ADC_CLOCK_DIV  // ADC总转换时间
// ########################### END OF  DO-NOT-TOUCH SETTINGS ############################
// 请勿修改设置结束

// ############################### BOARD VARIANT ###############################
// 板卡变体
/* Board Variant
 * 0 - Default board type
 * 1 - Alternate board type with different pin mapping for DCLINK, Buzzer and ON/OFF, Button and Charger
*/
/* 板卡变体
 * 0 - 默认板卡类型
 * 1 - 交替板卡类型，具有不同的引脚映射用于DCLINK、蜂鸣器和开/关、按钮和充电器
*/
#define BOARD_VARIANT           0         // change if board with alternate pin mapping  // 如果板卡具有交替引脚映射则更改
// ######################## END OF BOARD VARIANT ###############################
// 板卡变体结束

// ############################### BATTERY ###############################
// 电池
/* 电池电压校准：连接电源。
 * 参见如何校准。
 * 将调试输出值第5号写入BAT_CALIB_ADC。编译并烧录固件。
 * 然后可以在调试输出值第6号验证电压（校准后的电压乘以100）。
*/
#define BAT_FILT_COEF           655       // 电池电压滤波系数(定点数)。coef_fixedPoint = coef_floatingPoint * 2^16。此处655 = 0.01 * 2^16
#define BAT_CALIB_REAL_VOLTAGE  3970      // 万用表测量的输入电压(乘以100)。此处43.00V * 100 = 4300
#define BAT_CALIB_ADC           1492      // 主板测量的ADC值（UART调试输出第5号值）
#define BAT_CELLS               10        // 电池电芯数。普通平衡车电池：10串
#define BAT_LVL2_ENABLE         0         // 是否蜂鸣，1或0
#define BAT_LVL1_ENABLE         1         // 是否蜂鸣，1或0
#define BAT_DEAD_ENABLE         1         // 是否关机，1或0
#define BAT_BLINK_INTERVAL      80        // 电池LED闪烁间隔（80次循环 * 5ms ≈ 400ms）
#define BAT_LVL5                (390 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 绿色闪烁：不蜂鸣
#define BAT_LVL4                (380 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 黄色：不蜂鸣
#define BAT_LVL3                (370 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 黄色闪烁：不蜂鸣
#define BAT_LVL2                (360 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 红色：此电压等级轻柔蜂鸣。[V*100/芯] 此处3.60V/芯
#define BAT_LVL1                (350 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 红色闪烁：快速蜂鸣。电池快没电了，立即充电！[V*100/芯] 此处3.50V/芯
#define BAT_DEAD                (337 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 所有LED熄灭：欠压关机（非行驶状态）。[V*100/芯] 此处3.37V/芯
// ######################## END OF BATTERY ###############################



// ############################### TEMPERATURE ###############################
// 温度
/* 板卡过热检测：传感器在STM/GD芯片内部。
 * 未校准时非常不准确（偏差可达45°C）。请在校准后才启用此功能！
 * 让板卡冷却下来。
 * 参见如何校准。
 * 通过热成像仪或贴在芯片顶部的温度传感器获取芯片实际温度，写入TEMP_CAL_LOW_DEG_C。
 * 将调试输出值第8号写入TEMP_CAL_LOW_ADC。行驶使板卡升温，应至少升温20°C。对HIGH值重复此操作。
 * 启用警告和/或关机，编译并烧录固件。
*/
#define TEMP_FILT_COEF          655       // 温度滤波系数(定点数)。coef_fixedPoint = coef_floatingPoint * 2^16。此处655 = 0.01 * 2^16
#define TEMP_CAL_LOW_ADC        1655      // 温度点1：ADC值
#define TEMP_CAL_LOW_DEG_C      358       // 温度点1：测量温度[°C * 10]。此处35.8°C
#define TEMP_CAL_HIGH_ADC       1588      // 温度点2：ADC值
#define TEMP_CAL_HIGH_DEG_C     489       // 温度点2：测量温度[°C * 10]。此处48.9°C
#define TEMP_WARNING_ENABLE     0         // 是否蜂鸣，1或0，未校准切勿启用！
#define TEMP_WARNING            600       // 急促蜂鸣[°C * 10]。此处60.0°C
#define TEMP_POWEROFF_ENABLE    0         // 是否关机，1或0，未校准切勿启用！
#define TEMP_POWEROFF           650       // 过热关机（非行驶状态）。[°C * 10]。此处65.0°C
// ######################## END OF TEMPERATURE ###############################



// ############################### MOTOR CONTROL #########################
// 电机控制
/* 通用说明：
 * 1. 此处的参数会覆盖默认电机参数。所有可用参数请查看BLDC_controller_data.c
 * 2. 参数以定点数数据类型表示，以提高代码执行效率
 * 3. 校准定点参数请使用Fixed-Point Viewer工具（见<https://github.com/EmanuelFeru/FixedPointViewer>）
 * 4. 关于参数和控制器工作原理的更多详情请参阅Simulink模型
 * 5. 已创建webview，无需安装Matlab/Simulink，除非要重新生成代码。
 * webview是HTML页面，可用Microsoft Internet Explorer或Microsoft Edge浏览器打开
 *
 * 弱磁/超前角说明：
 * 1. 弱磁是从0到FIELD_WEAK_MAX或PHASE_ADV_MAX的线性插值（取决于选择FOC还是SIN）
 * 2. 弱磁从FIELD_WEAK_LO开始介入，在FIELD_WEAK_HI达到最大值
 * 3. 如果重新校准弱磁，请采取所有安全措施！电机会高速旋转！

   输入：
    - input1[inIdx].cmd 和 input2[inIdx].cmd：归一化输入值。INPUT_MIN 到 INPUT_MAX
    - button1 和 button2：数字输入值。0 或 1
    - adc_buffer.l_tx2 和 adc_buffer.l_rx2：未滤波ADC值（不需要）。0 到 4095
   输出：
    - cmdL 和 cmdR：正常行驶 INPUT_MIN 到 INPUT_MAX
*/
#define COM_CTRL        0               // [-] 换向控制类型
#define SIN_CTRL        1               // [-] 正弦波控制类型
#define FOC_CTRL        2               // [-] 矢量控制(FOC)类型

#define OPEN_MODE       0               // [-] 开环模式
#define VLT_MODE        1               // [-] 电压模式
#define SPD_MODE        2               // [-] 速度模式
#define TRQ_MODE        3               // [-] 扭矩模式

// 使能/禁用电机
#define MOTOR_LEFT_ENA                  // [-] 使能左电机。如不需要此电机运行请注释掉
#define MOTOR_RIGHT_ENA                 // [-] 使能右电机。如不需要此电机运行请注释掉

// 控制选择
#define CTRL_TYP_SEL    FOC_CTRL        // [-] 控制类型选择：COM_CTRL, SIN_CTRL, FOC_CTRL（默认）
#define CTRL_MOD_REQ    VLT_MODE        // [-] 控制模式请求：OPEN_MODE, VLT_MODE（默认）, SPD_MODE, TRQ_MODE。注意：SPD_MODE和TRQ_MODE仅在CTRL_FOC下可用！
#define DIAG_ENA        1               // [-] 电机诊断使能标志：0=禁用，1=使能（默认）

// 限制设置
#define I_MOT_MAX       15              // [A] 单电机最大电流限制
#define I_DC_MAX        17              // [A] 换向和正弦波类型的第二阶段直流母线电流限制（这是最终电流保护。超过此值会进行电流斩波。为避免此情况请确保I_DC_MAX = I_MOT_MAX + 2A）
#define N_MOT_MAX       1000            // [rpm] 电机最大转速限制

// 弱磁/超前角
#define FIELD_WEAK_ENA  0               // [-] 弱磁/超前角使能标志：0=禁用（默认），1=使能
#define FIELD_WEAK_MAX  5               // [A] 最大弱磁D轴电流（仅FOC）。电流越大最高转速越高。10"轮子已测试到10A。
#define PHASE_ADV_MAX   25              // [deg] 最大超前角（仅SIN）。角度越大最高转速越高。
#define FIELD_WEAK_HI   1000            // (1000, 1500] 输入目标高阈值，用于达到最大弱磁/超前角。请勿设置高于1500。
#define FIELD_WEAK_LO   750             // ( 500, 1000] 输入目标低阈值，用于开始弱磁/超前角。请勿设置高于1000。

// 附加功能
#define STANDSTILL_HOLD_ENABLE              // [-] 静止保持标志。到达静止时保持位置。仅在电压或扭矩模式下有效。
#define ELECTRIC_BRAKE_ENABLE               // [-] 电制动使能标志。输入扭矩请求为0时用恒定制动替代电机"自由转动"。仅在扭矩模式下有效。
#define ELECTRIC_BRAKE_MAX    50            // (0, 500) 输入扭矩请求为0时（踏板完全松开）施加的最大电制动力。
#define ELECTRIC_BRAKE_THRES  30            // (0, 500) 电制动开始介入的阈值。降低此值可减少油门死区行程。
// ########################### END OF MOTOR CONTROL ########################



// ############################## DEFAULT SETTINGS ############################
// 默认设置（如果之前未设置则在此文件末尾应用）
  #define INACTIVITY_TIMEOUT        3       // 不行驶后自动关机的分钟数。不太精确。
#define BEEPS_BACKWARD            1       // 倒车蜂鸣，0或1
#define ADC_MARGIN                100     // ADC输入余量，施加在原始ADC最小值和最大值上，确保在噪声存在时仍能达到MIN和MAX值
#define ADC_PROTECT_TIMEOUT       100     // ADC保护：进入安全状态前的错误/缺失输入命令数
#define ADC_PROTECT_THRESH        200     // ADC保护阈值，在MIN/MAX ADC值之下/之上
#define AUTO_CALIBRATION_ENA              // 通过长按电源键使能/禁用输入自动校准。如不需要自动校准请注释掉此行。

/* FILTER为定点数 fixdt(0,16,16)：VAL_fixedPoint = VAL_floatingPoint * 2^16。此处6553 = 0.1 * 2^16
 * COEFFICIENT值为定点数 fixdt(1,16,14)
 * 如果 VAL_floatingPoint >= 0，VAL_fixedPoint = VAL_floatingPoint * 2^14
 * 如果 VAL_floatingPoint < 0，VAL_fixedPoint = 2^16 + floor(VAL_floatingPoint * 2^14)
*/
// RATE值为定点数 fixdt(1,16,4)：VAL_fixedPoint = VAL_floatingPoint * 2^4。此处480 = 30 * 2^4
#define DEFAULT_RATE                480   // 30.0f [-] 越小变化越慢 [0, 32767] = [0.0, 2047.9375]。请勿设为负数(>32767)
#define DEFAULT_FILTER              6553  // FILTER默认值 0.1f [-] 越小滤波越柔和 [0, 65535] = [0.0 - 1.0]
#define DEFAULT_SPEED_COEFFICIENT   16384 // SPEED_COEFFICIENT默认值 1.0f [-] 越大越强 [0, 65535] = [-2.0 - 2.0]。此处16384 = 1.0 * 2^14
#define DEFAULT_STEER_COEFFICIENT   8192  // STEER_COEFFICIENT默认值 0.5f [-] 越大越强 [0, 65535] = [-2.0 - 2.0]。此处8192 = 0.5 * 2^14。如不需要转向请设为0。
// ######################### END OF DEFAULT SETTINGS ##########################



// ############################## INPUT FORMAT ############################
/* ***_INPUT: TYPE, MIN, MID, MAX, DEADBAND
 * -----------------------------------------
 * TYPE:      0:Disabled, 1:Normal Pot, 2:Middle Resting Pot, 3:Auto-detect
 * MIN:       min ADC1-value while poti at minimum-position (0 - 4095)
 * MID:       mid ADC1-value while poti at mid-position (INPUT_MIN - INPUT_MAX)
 * MAX:       max ADC2-value while poti at maximum-position (0 - 4095)
 * DEADBAND:  how much of the center position is considered 'center' (100 = values -100 to 100 are considered 0)
 * 
 * Dual-inputs
 * PRI_INPUT: Primary   Input. These limits will be used for the input with priority 0
 * AUX_INPUT: Auxiliary Input. These limits will be used for the input with priority 1
 * -----------------------------------------
*/
 // ############################## END OF INPUT FORMAT ############################



// ############################## CRUISE CONTROL SETTINGS ############################
/* Cruise Control info:
 * enable CRUISE_CONTROL_SUPPORT and (SUPPORT_BUTTONS_LEFT or SUPPORT_BUTTONS_RIGHT depending on which cable is the button installed)
 * can be activated/deactivated by pressing button1 (Blue cable) to GND
 * when activated, it maintains the current speed by switching to SPD_MODE. Acceleration is still possible via the input request, but when released it resumes to previous set speed.
 * when deactivated, it returns to previous control MODE and follows the input request.
*/
// #define CRUISE_CONTROL_SUPPORT
// #define SUPPORT_BUTTONS_LEFT              // Use button1 (Blue Left cable)  to activate/deactivate Cruise Control
// #define SUPPORT_BUTTONS_RIGHT             // Use button1 (Blue Right cable) to activate/deactivate Cruise Control

// ######################### END OF CRUISE CONTROL SETTINGS ##########################



// ############################### DEBUG SERIAL ###############################
// 调试串口
/* 将3.3V USB-UART转换器的GND和RX连接到左传感器板线缆(USART2)或右传感器板线缆(USART3)
 * 注意不要使用线缆的红色线（15V会烧毁一切）。
 * 如果正在使用VARIANT_NUNCHUK请暂时禁用。
 * 使能DEBUG_SERIAL_USART3或DEBUG_SERIAL_USART2
 *
 * 调试ASCII输出格式：
 * // "in1:345 in2:1337 cmdL:0 cmdR:0 BatADC:0 BatV:0 TempADC:0 Temp:0\r\n"
 *
 * in1:     原始输入1：ADC1, UART, PWM, PPM, iBUS
 * in2:     原始输入2：ADC2, UART, PWM, PPM, iBUS
 * cmdL:    左侧输出命令：[-1000, 1000]
 * cmdR:    右侧输出命令：[-1000, 1000]
 * BatADC:  主板测量的电池ADC值
 * BatV:    校准后电池电压(乘以100)用于验证电池电压校准
 * TempADC: 板卡温度滤波ADC值，用于板卡温度校准
 * Temp:    温度（摄氏度），用于验证板卡温度校准
*/

// #define DEBUG_SERIAL_USART2          // 左传感器板线缆，如使用ADC或PPM请禁用！
// #define DEBUG_SERIAL_USART3          // 右传感器板线缆，如使用I2C(nunchuk或lcd)请禁用！
// #define DEBUG_SERIAL_PROTOCOL        // 取消注释此行可向主板发送用户命令、修改参数和打印特定信号（用户命令详见comms.c）
// ########################### END OF DEBUG SERIAL ############################
// 调试串口结束



// ############################### DEBUG LCD ###############################
// 调试LCD
// #define DEBUG_I2C_LCD                // 通过右传感器板线缆的I2C转换器连接标准16x2或更大的文本LCD
// ########################### END OF DEBUG LCD ############################
// 调试LCD结束


// ############################### BUZZER ENABLE / DISABLE ###############################
// 蜂鸣器使能/禁用
#define BUZZER_ENABLED              // 使能后蜂鸣器会响，否则不会
// ########################### END OF BUZZER ENABLE / DISABLE ############################
// 蜂鸣器使能/禁用结束



// ################################# VARIANT_ADC SETTINGS ############################
// ADC变体设置
#ifdef VARIANT_ADC
/* 通过两个电位器控制
 * 将电位器连接到左传感器板线缆（0到3.3V）（不要使用红色15V线！）
 *
 * ADC限制自动校准，查找ADC输入的最小值、最大值和中间值
 * 步骤：
 * - 长按电源键5秒以上，听到蜂鸣声后松开
 * - 自由来回移动电位器到最小和最大位置
 * - 将电位器释放到中间位置
 * - 短按电源键确认或等待20秒超时
 * 值将保存到Flash。使用platformio烧录时值会保留。要擦除请进行整片擦除。
 *
 * 校准后可选择将值写入以下宏定义
 * 步骤：
 * - 将USB-UART转换器的GND、RX和TX以3.3V模式连接到右传感器板线缆（不要使用红色15V线！）
 * - 使用115200波特率的串口终端读取值
 * - 将电位器转到最小位置，将in1值写入PRI_INPUT1 MIN，in2值写入PRI_INPUT2 MIN
 * - 将电位器转到最大位置，将in1值写入PRI_INPUT1 MAX，in2值写入PRI_INPUT2 MAX
 * - 对于中间位电位器：将电位器保持在中间位置，将in1值写入PRI_INPUT1 MID，in2值写入PRI_INPUT2 MID
*/
  #define CONTROL_ADC           0         // 使用ADC作为输入。数字表示双输入时的优先级。禁用CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2！

  // #define DUAL_INPUTS                     //  ADC*(主) + UART(辅)。取消注释以使用双输入
  #define PRI_INPUT1            3, 0, 0, 4095, 0      // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #define PRI_INPUT2            3, 0, 0, 4095, 0      // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY     0x1101    // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
    // #define SIDEBOARD_SERIAL_USART3 1
    #define CONTROL_SERIAL_USART3 1       // 右传感器板线缆。数字表示双输入时的优先级。如使用I2C(nunchuk或lcd)请禁用！Arduino控制请查看hoverSerial.ino
    #define FEEDBACK_SERIAL_USART3        // 右传感器板线缆，如使用I2C(nunchuk或lcd)请禁用！
    #define AUX_INPUT1          3, -1000, 0, 1000, 0  // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
    #define AUX_INPUT2          3, -1000, 0, 1000, 0  // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #else
    #define FLASH_WRITE_KEY     0x1001    // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
    #define DEBUG_SERIAL_USART3           // 右传感器板线缆，如使用I2C(nunchuk或lcd)请禁用！
  #endif

  // #define TANK_STEERING                   // 坦克转向模式，每个输入控制每个轮子
  // #define ADC_ALTERNATE_CONNECT           // 用于交换ADC输入
  // #define SUPPORT_BUTTONS_LEFT            // 使用左传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT           // 使用右传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！
#endif
// ############################# END OF VARIANT_ADC SETTINGS #########################
// ADC变体设置结束



// ############################ VARIANT_USART SETTINGS ############################
// USART变体设置
#ifdef VARIANT_USART
  // #define SIDEBOARD_SERIAL_USART2 0
  #define CONTROL_SERIAL_USART2  0    // 左传感器板线缆，如使用ADC或PPM请禁用！Arduino控制请查看hoverSerial.ino
  #define FEEDBACK_SERIAL_USART2      // 左传感器板线缆，如使用ADC或PPM请禁用！

  // #define SIDEBOARD_SERIAL_USART3 0
  // #define CONTROL_SERIAL_USART3  0    // 右传感器板线缆。数字表示双输入时的优先级。如使用I2C(nunchuk或lcd)请禁用！Arduino控制请查看hoverSerial.ino
  // #define FEEDBACK_SERIAL_USART3      // 右传感器板线缆，如使用I2C(nunchuk或lcd)请禁用！
 
  // #define DUAL_INPUTS                 //  UART*(主) + SIDEBOARD(辅)。取消注释以使用双输入
  #define PRI_INPUT1             3, -1000, 0, 1000, 0     // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #define PRI_INPUT2             3, -1000, 0, 1000, 0     // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY      0x1102  // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
    // #define SIDEBOARD_SERIAL_USART2 1   // 左子板
    #define SIDEBOARD_SERIAL_USART3 1   // 右子板
    #define AUX_INPUT1           3, -1000, 0, 1000, 0     // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
    #define AUX_INPUT2           3, -1000, 0, 1000, 0     // 类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #else
    #define FLASH_WRITE_KEY      0x1002  // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
  #endif

  // #define TANK_STEERING              // 坦克转向模式，每个输入控制每个轮子
  // #define SUPPORT_BUTTONS_LEFT       // 使用左传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT      // 使用右传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！
#endif
// ######################## END OF VARIANT_USART SETTINGS #########################
// USART变体设置结束



// ################################# VARIANT_NUNCHUK SETTINGS ############################
#ifdef VARIANT_NUNCHUK
  /* on Right sensor cable
   * keep cable short, use shielded cable, use ferrits, stabalize voltage in nunchuk,
   * use the right one of the 2 types of nunchuks, add i2c pullups.
   * use original nunchuk. most clones does not work very well.
   * Recommendation: Nunchuk Breakout Board https://github.com/Jan--Henrik/hoverboard-breakout
  */
  #define CONTROL_NUNCHUK         0       // use nunchuk as input. Number indicates priority for dual-input. Disable FEEDBACK_SERIAL_USART3, DEBUG_SERIAL_USART3!

  // #define DUAL_INPUTS                     // Nunchuk*(Primary) + UART(Auxiliary). Uncomment this to use Dual-inputs
  #define PRI_INPUT1              2, -1024, 0, 1024, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #define PRI_INPUT2              2, -1024, 0, 1024, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1103  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define SIDEBOARD_SERIAL_USART2 1
    #define CONTROL_SERIAL_USART2 1       // left sensor board cable, disable if ADC or PPM is used! For Arduino control check the hoverSerial.ino
    #define FEEDBACK_SERIAL_USART2        // left sensor board cable, disable if ADC or PPM is used!
    #define AUX_INPUT1            3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1003  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define DEBUG_SERIAL_USART2           // left sensor cable debug
  #endif

  // # maybe good for ARMCHAIR #
  #define FILTER                  3276    //  0.05f
  #define SPEED_COEFFICIENT       8192    //  0.5f
  #define STEER_COEFFICIENT       62259   // -0.2f
  // #define SUPPORT_BUTTONS                 // Define for Nunchuk buttons support
#endif
// ############################# END OF VARIANT_NUNCHUK SETTINGS #########################



// ################################# VARIANT_PPM SETTINGS ##############################
#ifdef VARIANT_PPM
/* ###### CONTROL VIA RC REMOTE ######
 * Right sensor board cable. Channel 1: steering, Channel 2: speed.
 * https://gist.github.com/peterpoetzi/1b63a4a844162196613871767189bd05
*/
  // #define DUAL_INPUTS                     // ADC*(Primary) + PPM(Auxiliary). Uncomment this to use Dual-inputs
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1104  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_ADC           0       // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2!
    #define CONTROL_PPM_RIGHT     1       // use PPM-Sum as input on the RIGHT cable. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART3!
    #define PRI_INPUT1            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1004  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define CONTROL_PPM_LEFT      0       // use PPM-Sum as input on the LEFT cable. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2!
    #define CONTROL_PPM_RIGHT     0       // use PPM-Sum as input on the RIGHT cable. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART3!
    #define PRI_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #endif
  #define PPM_NUM_CHANNELS        6       // total number of PPM channels to receive, even if they are not used.

  // #define TANK_STEERING                   // use for tank steering, each input controls each wheel 
  // #define SUPPORT_BUTTONS                 // Define for PPM buttons support
  // #define SUPPORT_BUTTONS_LEFT            // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2!
  // #define SUPPORT_BUTTONS_RIGHT           // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3!

  #if defined(CONTROL_PPM_RIGHT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART2           // left sensor cable debug
  #elif defined(CONTROL_PPM_LEFT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART3           // right sensor cable debug
  #endif
#endif
// ############################# END OF VARIANT_PPM SETTINGS ############################


// ################################# VARIANT_PWM SETTINGS ##############################
#ifdef VARIANT_PWM
/* ###### CONTROL VIA RC REMOTE ######
 * Right sensor board cable. Connect PA2 to channel 1 and PA3 to channel 2 on receiver.
 * Channel 1: steering, Channel 2: speed.
*/
  // #define DUAL_INPUTS                     // ADC*(Primary) + PWM(Auxiliary). Uncomment this to use Dual-inputs
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1105  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_ADC           0       // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2!
    #define CONTROL_PWM_RIGHT     1       // use RC PWM as input on the RIGHT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3!
    #define PRI_INPUT1            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1005  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define CONTROL_PWM_LEFT      0       // use RC PWM as input on the LEFT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART2!
    #define CONTROL_PWM_RIGHT     0       // use RC PWM as input on the RIGHT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3!
    #define PRI_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #endif

  #define FILTER                  6553    // 0.1f [-] fixdt(0,16,16) lower value == softer filter [0, 65535] = [0.0 - 1.0].
  #define SPEED_COEFFICIENT       16384   // 1.0f [-] fixdt(1,16,14) higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14
  #define STEER_COEFFICIENT       16384   // 1.0f [-] fixdt(1,16,14) higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14. If you do not want any steering, set it to 0.
  // #define TANK_STEERING                   // use for tank steering, each input controls each wheel 
  // #define INVERT_R_DIRECTION
  // #define INVERT_L_DIRECTION
  // #define SUPPORT_BUTTONS_LEFT            // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2!
  // #define SUPPORT_BUTTONS_RIGHT           // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3!

  #if defined(CONTROL_PWM_RIGHT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART2           // left sensor cable debug
  #elif defined(CONTROL_PWM_LEFT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART3           // right sensor cable debug
  #endif
#endif
// ############################# END OF VARIANT_PWM SETTINGS ############################



// ################################# VARIANT_IBUS SETTINGS ##############################
#ifdef VARIANT_IBUS
/* CONTROL VIA RC REMOTE WITH FLYSKY IBUS PROTOCOL 
* Connected to Right sensor board cable. Channel 1: steering, Channel 2: speed.
*/
  #define CONTROL_IBUS                    // use IBUS as input. Number indicates priority for dual-input.
  #define IBUS_NUM_CHANNELS       14      // total number of IBUS channels to receive, even if they are not used.
  #define IBUS_LENGTH             0x20
  #define IBUS_COMMAND            0x40
  #define USART3_BAUD             115200

  // #define DUAL_INPUTS                     // ADC*(Primary) + iBUS(Auxiliary). Uncomment this to use Dual-inputs
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1106  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_ADC           0       // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2!
    #define CONTROL_SERIAL_USART3 1       // use RC iBUS input on the RIGHT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3!
    #define FEEDBACK_SERIAL_USART3        // right sensor board cable, disable if ADC or PPM is used!
    #define PRI_INPUT1            3,     0, 0, 4095, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3,     0, 0, 4095, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT1            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1006  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_SERIAL_USART3 0       // use RC iBUS input on the RIGHT cable, disable if ADC or PPM is used!
    #define FEEDBACK_SERIAL_USART3        // right sensor board cable, disable if ADC or PPM is used!
    #define PRI_INPUT1            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #endif

  // #define TANK_STEERING                // use for tank steering, each input controls each wheel 

  #if defined(CONTROL_SERIAL_USART3) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART2           // left sensor cable debug
  #elif defined(DEBUG_SERIAL_USART2) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART3           // right sensor cable debug
  #endif
#endif
// ############################# END OF VARIANT_IBUS SETTINGS ############################



// ############################ VARIANT_HOVERCAR SETTINGS ############################
// HOVERCAR变体设置
#ifdef VARIANT_HOVERCAR
  #define FLASH_WRITE_KEY         0x1108  // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
  #undef  CTRL_MOD_REQ
  #define CTRL_MOD_REQ            TRQ_MODE  // 扭矩模式：电制动功能需要此模式。松开油门时动能回收生效
  #define CONTROL_ADC             0         // 使用ADC作为输入。数字表示双输入时的优先级。禁用CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2！

  #define PRI_INPUT1              3, 0, 0, 4095, 0  // 刹车踏板 TYPE=3 自动检测，通过开机流程校准
  #define PRI_INPUT2              3, 0, 0, 4095, 0  // 油门踏板 TYPE=3 自动检测，通过开机流程校准

  // 卡丁车扩展板：PB10/PB11 = USART3 通讯口（连接扩展板）
  #define FEEDBACK_SERIAL_USART3              // 右线缆 USART3 发送 Feedback 给扩展板
  #define RF_CMD_SERIAL_USART3                // 右线缆 USART3 接收 RF遥控命令（4字节帧）

  #define SPEED_COEFFICIENT       16384     // 速度系数 1.0f
  #define STEER_COEFFICIENT       8192      // 转向系数 0.5f

  // ---- 卡丁车模式：PB10=速度按钮，PB11=倒挡开关 ----
  #define KART_SPEED_BTN_PORT     GPIOB     // 速度按钮端口
  #define KART_SPEED_BTN_PIN      GPIO_PIN_10  // 速度按钮引脚
  #define KART_REVERSE_BTN_PORT   GPIOB     // 倒挡开关端口
  #define KART_REVERSE_BTN_PIN    GPIO_PIN_11  // 倒挡开关引脚
  #define KART_DEBOUNCE_MS        250       // 按钮消抖间隔(毫秒)

  #define MULTI_MODE_DRIVE                  // 3种驾驶模式，通过PB10按钮循环切换
  #ifdef MULTI_MODE_DRIVE
      // 模式1 - 新手：≈8 km/h
      #define MULTI_MODE_DRIVE_M1_MAX   400   // 最大速度
      #define MULTI_MODE_DRIVE_M1_RATE  250   // 变化率
      #define MULTI_MODE_M1_I_MOT_MAX   8     // 最大电流(A)
      #define MULTI_MODE_M1_N_MOT_MAX   180   // 最大转速(RPM)

      // 模式2 - 中级：≈21 km/h
      #define MULTI_MODE_DRIVE_M2_MAX   600   // 最大速度
      #define MULTI_MODE_DRIVE_M2_RATE  350   // 变化率
      #define MULTI_MODE_M2_I_MOT_MAX   12    // 最大电流(A)
      #define MULTI_MODE_M2_N_MOT_MAX   450   // 最大转速(RPM)

      // 模式3 - 高级：≈48 km/h
      #define MULTI_MODE_DRIVE_M3_MAX   800   // 最大速度
      #define MULTI_MODE_DRIVE_M3_RATE  450   // 变化率
      #define MULTI_MODE_M3_I_MOT_MAX   I_MOT_MAX  // 最大电流 = 全局限制
      #define MULTI_MODE_M3_N_MOT_MAX   N_MOT_MAX  // 最大转速 = 全局限制
  #endif

  // RF遥控命令编码（与扩展板一致）
  #define RF_CMD_NONE          0x00
  #define RF_CMD_LOCK          0x01           // 锁车：禁用油门
  #define RF_CMD_UNLOCK        0x02           // 解锁：启用油门
  #define RF_CMD_MODE1         0x03           // 切换到M1档
  #define RF_CMD_STOP          0x04           // 停车：激活驻车
  #define RF_CMD_START_FRAME   0xAA           // RF命令帧起始字节

#endif

// 多次敲击检测：默认在刹车踏板上检测双击（4个脉冲）
#define MULTIPLE_TAP_NR           2 * 2       // [-] 敲击次数定义：MULTIPLE_TAP_NR = 敲击次数 * 2。1=单击，2=双击，3=三击，以此类推
#define MULTIPLE_TAP_HI           600         // [-] 多次敲击检测高迟滞阈值
#define MULTIPLE_TAP_LO           200         // [-] 多次敲击检测低迟滞阈值
#define MULTIPLE_TAP_TIMEOUT      2000        // [ms] 多次敲击检测超时时间。敲击需在此时间窗口内完成才会被接受。
// ######################## END OF VARIANT_HOVERCAR SETTINGS #########################
// HOVERCAR变体设置结束



// ############################ VARIANT_HOVERBOARD SETTINGS ############################
// HOVERBOARD变体设置
// 通信：         [已完成]
// 平衡控制器：  [待完成]
#ifdef VARIANT_HOVERBOARD
  #define FLASH_WRITE_KEY     0x1008          // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
  #define SIDEBOARD_SERIAL_USART2 1           // 左传感器板线缆。数字表示双输入时的优先级。如使用ADC或PPM请禁用！
  #define FEEDBACK_SERIAL_USART2
  #define SIDEBOARD_SERIAL_USART3 0           // 右传感器板线缆。数字表示双输入时的优先级。如使用I2C(nunchuk或lcd)请禁用！
  #define FEEDBACK_SERIAL_USART3

  // 如果iBUS遥控接收机连接到左侧子板(AUX_INPUT)或右侧子板(PRI_INPUT)
  // 主输入：类型, 最小值, 中间值, 最大值, 死区 /* 类型：0:禁用, 1:普通电位器, 2:中间位电位器, 3:自动检测 */
  #define PRI_INPUT1          3, -1000, 0, 1000, 0  // 优先级子板可用于通过连接到子板的iBUS接收机发送命令
  #define PRI_INPUT2          3, -1000, 0, 1000, 0  // 优先级子板可用于通过连接到子板的iBUS接收机发送命令
  #define AUX_INPUT1          3, -1000, 0, 1000, 0  // 未使用
  #define AUX_INPUT2          3, -1000, 0, 1000, 0  // 未使用
#endif
// ######################## END OF VARIANT_HOVERBOARD SETTINGS #########################
// HOVERBOARD变体设置结束



// ################################# VARIANT_TRANSPOTTER SETTINGS ############################
// TRANSPOTTER变体设置
//TODO 添加验证
#ifdef VARIANT_TRANSPOTTER
  #define FLASH_WRITE_KEY     0x1009    // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
  #define CONTROL_GAMETRAK
  #define SUPPORT_LCD
  // #define SUPPORT_NUNCHUK
  #define GAMETRAK_CONNECTION_NORMAL    // 按照wiki说明正常接线
  // #define GAMETRAK_CONNECTION_ALTERNATE // 如果搞错了gametrak的ADC接线（转向变速度，线长变转向）请使用此定义
  #define ROT_P               1.2       // 方向控制器的P系数。正值/负值用于反转gametrak转向方向。
  // nunchuk控制期间（仅在激活时相关）
  #define SPEED_COEFFICIENT   14746     // 0.9f - 越大越强。0.0到约2.0？
  #define STEER_COEFFICIENT   8192      // 0.5f - 越大越强。如不需要转向请设为0.0；0.0到1.0
  #define INVERT_R_DIRECTION            // 反转右电机
  #define INVERT_L_DIRECTION            // 反转左电机
  #define PRI_INPUT1          2, -1000, 0, 1000, 0  // 虚拟输入，TRANSPOTTER不使用输入限制
  #define PRI_INPUT2          2, -1000, 0, 1000, 0  // 虚拟输入，TRANSPOTTER不使用输入限制
#endif
// ############################# END OF VARIANT_TRANSPOTTER SETTINGS ########################
// TRANSPOTTER变体设置结束


// ################################# VARIANT_SKATEBOARD SETTINGS ##############################
// 滑板变体设置
#ifdef VARIANT_SKATEBOARD
/* ###### 通过遥控器控制 ######
 * 右传感器板线缆。将PB10连接到接收机通道1，PB11连接到通道2。
 * 通道1：转向，通道2：速度。
*/
  #define FLASH_WRITE_KEY     0x1010    // Flash写入密钥。修改此密钥可忽略Flash中的输入校准值并使用config.h中的值
  #undef  CTRL_MOD_REQ
  #define CTRL_MOD_REQ        TRQ_MODE  // 滑板在扭矩模式下工作最佳
  // #define CONTROL_PWM_LEFT    0         // 在左线缆使用RC PWM输入。数字表示双输入时的优先级。禁用DEBUG_SERIAL_USART2！
  #define CONTROL_PWM_RIGHT   0         // 在右线缆使用RC PWM输入。数字表示双输入时的优先级。禁用DEBUG_SERIAL_USART3！

  #define PRI_INPUT1          0, -1000, 0, 1000,   0    // 禁用。类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #define PRI_INPUT2          2,  -800, 0,  700, 100    // 激活。类型, 最小值, 中间值, 最大值, 死区。参见输入格式部分
  #define INPUT_BRK           -400      // (-1000 - 0) 修改此值以调整制动力度

  #define FILTER              6553      // 0.1f [-] 定点数fixdt(0,16,16) 越小滤波越柔和 [0, 65535] = [0.0 - 1.0]
  #define SPEED_COEFFICIENT   16384     // 1.0f [-] 定点数fixdt(1,16,14) 越大越强 [0, 65535] = [-2.0 - 2.0]。此处16384 = 1.0 * 2^14
  #define STEER_COEFFICIENT   0         // 1.0f [-] 定点数fixdt(1,16,14) 越大越强 [0, 65535] = [-2.0 - 2.0]。如不需要转向请设为0。
  #define INVERT_R_DIRECTION            // 反转右电机
  #define INVERT_L_DIRECTION            // 反转左电机
  // #define SUPPORT_BUTTONS_LEFT       // 使用左传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT      // 使用右传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！
  // #define STANDSTILL_HOLD_ENABLE     // [-] 静止保持标志。到达静止时保持位置。仅在电压或扭矩模式下有效。

  #ifdef CONTROL_PWM_RIGHT
    #define DEBUG_SERIAL_USART2         // 左传感器线缆调试
  #else
    #define DEBUG_SERIAL_USART3         // 右传感器线缆调试
  #endif
#endif
// ############################# END OF VARIANT_SKATEBOARD SETTINGS ############################
// 滑板变体设置结束



// ########################### UART SETIINGS ############################
// UART设置
#if defined(FEEDBACK_SERIAL_USART2) || defined(CONTROL_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || \
    defined(FEEDBACK_SERIAL_USART3) || defined(CONTROL_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3)
  #define SERIAL_START_FRAME      0xABCD                  // [-] 串口命令起始帧定义
  #define SERIAL_BUFFER_SIZE      64                      // [字节] 串口接收缓冲区大小。确保始终大于结构体大小
  #define SERIAL_TIMEOUT          160                     // [-] 接收数据的串口超时。160 ≈ 0.8秒。计算：0.8秒 / 0.005秒
#endif
#if defined(FEEDBACK_SERIAL_USART2) || defined(CONTROL_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2)
  #ifndef USART2_BAUD
    #define USART2_BAUD           115200                  // UART2波特率（长线缆）
  #endif
  #define USART2_WORDLENGTH       UART_WORDLENGTH_8B      // UART_WORDLENGTH_8B 或 UART_WORDLENGTH_9B
#endif
#if defined(FEEDBACK_SERIAL_USART3) || defined(CONTROL_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3)
  #ifndef USART3_BAUD
    #define USART3_BAUD           115200                  // UART3波特率（短线缆）
  #endif
  #define USART3_WORDLENGTH       UART_WORDLENGTH_8B      // UART_WORDLENGTH_8B 或 UART_WORDLENGTH_9B
#endif
// ########################### UART SETIINGS ############################
// UART设置结束



// ############################### APPLY DEFAULT SETTINGS ###############################
// 应用默认设置
#ifndef RATE
  #define RATE DEFAULT_RATE
#endif
#ifndef FILTER
  #define FILTER DEFAULT_FILTER
#endif
#ifndef SPEED_COEFFICIENT
  #define SPEED_COEFFICIENT DEFAULT_SPEED_COEFFICIENT
#endif
#ifndef STEER_COEFFICIENT
  #define STEER_COEFFICIENT DEFAULT_STEER_COEFFICIENT
#endif
#if defined(PRI_INPUT1) && defined(PRI_INPUT2) && defined(AUX_INPUT1) && defined(AUX_INPUT2)
  #define INPUTS_NR               2
#else
  #define INPUTS_NR               1
#endif
// ########################### END OF APPLY DEFAULT SETTING ############################
// 应用默认设置结束



// ############################### VALIDATE SETTINGS ###############################
// 验证设置
#if !defined(VARIANT_ADC) && !defined(VARIANT_USART) && !defined(VARIANT_NUNCHUK) && !defined(VARIANT_PPM) && !defined(VARIANT_PWM) && \
    !defined(VARIANT_IBUS) && !defined(VARIANT_HOVERCAR) && !defined(VARIANT_HOVERBOARD) && !defined(VARIANT_TRANSPOTTER) && !defined(VARIANT_SKATEBOARD)
  #error 变体未定义！请检查platformio.ini或Inc/config.h中的可用变体。
#endif


// 通用检查
#if defined(CONTROL_SERIAL_USART2) && defined(SIDEBOARD_SERIAL_USART2)
  #error CONTROL_SERIAL_USART2 和 SIDEBOARD_SERIAL_USART2 不能同时使用，请选其一。
#endif

#if defined(CONTROL_SERIAL_USART3) && defined(SIDEBOARD_SERIAL_USART3)
  #error CONTROL_SERIAL_USART3 和 SIDEBOARD_SERIAL_USART3 不能同时使用，请选其一。
#endif

#if defined(DEBUG_SERIAL_USART2) && defined(FEEDBACK_SERIAL_USART2)
  #error DEBUG_SERIAL_USART2 和 FEEDBACK_SERIAL_USART2 不能同时使用，请选其一。
#endif

#if defined(DEBUG_SERIAL_USART3) && defined(FEEDBACK_SERIAL_USART3)
  #error DEBUG_SERIAL_USART3 和 FEEDBACK_SERIAL_USART3 不能同时使用，请选其一。
#endif

#if defined(DEBUG_SERIAL_USART2) && defined(DEBUG_SERIAL_USART3)
  #error DEBUG_SERIAL_USART2 和 DEBUG_SERIAL_USART3 不能同时使用，请选其一。
#endif

#if defined(CONTROL_PPM_LEFT) && defined(CONTROL_PPM_RIGHT)
  #error CONTROL_PPM_LEFT 和 CONTROL_PPM_RIGHT 不能同时使用，请选其一。
#endif

#if defined(CONTROL_PWM_LEFT) && defined(CONTROL_PWM_RIGHT)
  #error CONTROL_PWM_LEFT 和 CONTROL_PWM_RIGHT 不能同时使用，请选其一。
#endif

#if defined(SUPPORT_BUTTONS_LEFT) && defined(SUPPORT_BUTTONS_RIGHT)
  #error SUPPORT_BUTTONS_LEFT 和 SUPPORT_BUTTONS_RIGHT 不能同时使用，请选其一。
#endif


// 左线缆检查
#if defined(CONTROL_ADC) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error CONTROL_ADC 和 SERIAL_USART2 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_PPM_LEFT) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error CONTROL_PPM_LEFT 和 SERIAL_USART2 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_PWM_LEFT) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error CONTROL_PWM_LEFT 和 SERIAL_USART2 不能同时使用，它们在同一线缆上。
#endif

#if defined(SUPPORT_BUTTONS_LEFT) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error SUPPORT_BUTTONS_LEFT 和 SERIAL_USART2 不能同时使用，它们在同一线缆上。
#endif

#if defined(SUPPORT_BUTTONS_LEFT) && (defined(CONTROL_ADC) || defined(CONTROL_PPM_LEFT) || defined(CONTROL_PWM_LEFT))
  #error SUPPORT_BUTTONS_LEFT 和 (CONTROL_ADC 或 CONTROL_PPM_LEFT 或 CONTROL_PWM_LEFT) 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_ADC) && (defined(CONTROL_PPM_LEFT) || defined(CONTROL_PWM_LEFT))
  #error CONTROL_ADC 和 (CONTROL_PPM_LEFT 或 CONTROL_PWM_LEFT) 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_PPM_LEFT) && defined(CONTROL_PWM_LEFT)
  #error CONTROL_PPM_LEFT 和 CONTROL_PWM_LEFT 不能同时使用，它们在同一线缆上。
#endif


// 右线缆检查
#if defined(CONTROL_NUNCHUK) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error CONTROL_NUNCHUK 和 SERIAL_USART3 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_PPM_RIGHT) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error CONTROL_PPM_RIGHT 和 SERIAL_USART3 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_PWM_RIGHT) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error CONTROL_PWM_RIGHT 和 SERIAL_USART3 不能同时使用，它们在同一线缆上。
#endif

#if defined(DEBUG_I2C_LCD) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error DEBUG_I2C_LCD 和 SERIAL_USART3 不能同时使用，它们在同一线缆上。
#endif

#if defined(SUPPORT_BUTTONS_RIGHT) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error SUPPORT_BUTTONS_RIGHT 和 SERIAL_USART3 不能同时使用，它们在同一线缆上。
#endif

#if defined(SUPPORT_BUTTONS_RIGHT) && (defined(CONTROL_NUNCHUK) || defined(CONTROL_PPM_RIGHT) || defined(CONTROL_PWM_RIGHT) || defined(DEBUG_I2C_LCD))
  #error SUPPORT_BUTTONS_RIGHT 和 (CONTROL_NUNCHUK 或 CONTROL_PPM_RIGHT 或 CONTROL_PWM_RIGHT 或 DEBUG_I2C_LCD) 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_NUNCHUK) && (defined(CONTROL_PPM_RIGHT) || defined(CONTROL_PWM_RIGHT) || defined(DEBUG_I2C_LCD))
  #error CONTROL_NUNCHUK 和 (CONTROL_PPM_RIGHT 或 CONTROL_PWM_RIGHT 或 DEBUG_I2C_LCD) 不能同时使用，它们在同一线缆上。
#endif

#if defined(DEBUG_I2C_LCD) && (defined(CONTROL_PPM_RIGHT) || defined(CONTROL_PWM_RIGHT))
  #error DEBUG_I2C_LCD 和 (CONTROL_PPM_RIGHT 或 CONTROL_PWM_RIGHT) 不能同时使用，它们在同一线缆上。
#endif

#if defined(CONTROL_PPM_RIGHT) && defined(CONTROL_PWM_RIGHT)
  #error CONTROL_PPM_RIGHT 和 CONTROL_PWM_RIGHT 不能同时使用，它们在同一线缆上。
#endif


// 功能检查
#if (defined(CONTROL_PPM_LEFT) || defined(CONTROL_PPM_RIGHT)) && !defined(PPM_NUM_CHANNELS)
  #error 需要设置PPM通道总数
#endif
// ############################# END OF VALIDATE SETTINGS ############################
// 验证设置结束

#endif

