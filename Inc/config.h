// Define to prevent recursive inclusion // 防止递归包含
#ifndef CONFIG_H
#define CONFIG_H

#include "stm32f1xx_hal.h"

// ############################### VARIANT SELECTION (变体选择) ###############################
// PlatformIO: uncomment desired variant in platformio.ini // PlatformIO：在platformio.ini中取消注释所需变体
// Keil uVision: select desired variant from the Target drop down menu (to the right of the Load button) // Keil uVision：从Target下拉菜单（Load按钮右侧）中选择所需变体
// Ubuntu: define the desired build variant here if you want to use make in console // Ubuntu：如果要在控制台中使用make，请在此处定义所需的构建变体
// or use VARIANT environment variable for example like "make -e VARIANT=VARIANT_NUNCHUK". Select only one at a time. // 或使用VARIANT环境变量，例如"make -e VARIANT=VARIANT_NUNCHUK"。一次仅选择一个。
#if !defined(PLATFORMIO)
  //#define VARIANT_ADC         // Variant for control via ADC input // 通过ADC输入控制的变体
  //#define VARIANT_USART       // Variant for Serial control via USART3 input // 通过USART3串口控制的变体
  //#define VARIANT_NUNCHUK     // Variant for Nunchuk controlled vehicle build // 使用Nunchuk控制的车辆构建变体
  //#define VARIANT_PPM         // Variant for RC-Remote with PPM-Sum Signal // 使用PPM和信号遥控器的变体
  //#define VARIANT_PWM         // Variant for RC-Remote with PWM Signal // 使用PWM信号遥控器的变体
  //#define VARIANT_IBUS        // Variant for RC-Remotes with FLYSKY IBUS // 使用FLYSKY IBUS遥控器的变体
  #define VARIANT_HOVERCAR    // Variant for HOVERCAR build // 卡丁车构建变体
  //#define VARIANT_HOVERBOARD  // Variant for HOVERBOARD build // 平衡车构建变体
  //#define VARIANT_TRANSPOTTER // Variant for TRANSPOTTER build // TRANSPOTTER构建变体 https://github.com/NiklasFauth/hoverboard-firmware-hack/wiki/Build-Instruction:-TranspOtter https://hackaday.io/project/161891-transpotter-ng
  //#define VARIANT_SKATEBOARD  // Variant for SKATEBOARD build // 滑板构建变体
#endif
// ########################### END OF VARIANT SELECTION (变体选择结束) ############################


// ############################### DO-NOT-TOUCH SETTINGS (请勿修改的设置) ###############################
#define PWM_FREQ            16000     // PWM frequency in Hz / is also used for buzzer // PWM频率（Hz）/ 也用于蜂鸣器
#define DEAD_TIME              48     // PWM deadtime // PWM死区时间
#ifdef VARIANT_TRANSPOTTER
  #define DELAY_IN_MAIN_LOOP    2
#else
  #define DELAY_IN_MAIN_LOOP    5     // in ms. default 5. it is independent of all the timing critical stuff. do not touch if you do not know what you are doing. // 单位毫秒，默认5。与所有时序关键部分无关。如果不了解请勿修改。
#endif
#define TIMEOUT                20     // number of wrong / missing input commands before emergency off // 错误/丢失输入命令次数达到此值后紧急关闭
#define A2BIT_CONV             50     // A to bit for current conversion on ADC. Example: 1 A = 50, 2 A = 100, etc // ADC电流转换系数。例如：1A = 50，2A = 100等
// #define PRINTF_FLOAT_SUPPORT          // [-] Uncomment this for printf to support float on Serial Debug. It will increase code size! Better to avoid it! // 取消注释可使printf在串口调试中支持浮点数。会增加代码体积！最好避免使用！

// ADC conversion time definitions // ADC转换时间定义
#define ADC_CONV_TIME_1C5       (14)  //Total ADC clock cycles / conversion = (  1.5+12.5) // 总ADC时钟周期/转换
#define ADC_CONV_TIME_7C5       (20)  //Total ADC clock cycles / conversion = (  7.5+12.5)
#define ADC_CONV_TIME_13C5      (26)  //Total ADC clock cycles / conversion = ( 13.5+12.5)
#define ADC_CONV_TIME_28C5      (41)  //Total ADC clock cycles / conversion = ( 28.5+12.5)
#define ADC_CONV_TIME_41C5      (54)  //Total ADC clock cycles / conversion = ( 41.5+12.5)
#define ADC_CONV_TIME_55C5      (68)  //Total ADC clock cycles / conversion = ( 55.5+12.5)
#define ADC_CONV_TIME_71C5      (84)  //Total ADC clock cycles / conversion = ( 71.5+12.5)
#define ADC_CONV_TIME_239C5     (252) //Total ADC clock cycles / conversion = (239.5+12.5)

// This settings influences the actual sample-time. Only use definitions above // 此设置影响实际采样时间。仅使用上述定义
// This parameter needs to be the same as the ADC conversion for Current Phase of the FIRST Motor in setup.c // 此参数需要与setup.c中第一个电机的电流相位ADC转换相同
#define ADC_CONV_CLOCK_CYCLES   (ADC_CONV_TIME_7C5)

// Set the configured ADC divider. This parameter needs to be the same ADC divider as PeriphClkInit.AdcClockSelection (see main.c) // 设置已配置的ADC分频器。此参数需要与PeriphClkInit.AdcClockSelection中的ADC分频器相同（参见main.c）
#define ADC_CLOCK_DIV           (4)

// ADC Total conversion time: this will be used to offset TIM8 in advance of TIM1 to align the Phase current ADC measurement // ADC总转换时间：将用于使TIM8提前于TIM1偏移，以对齐相电流ADC测量
// This parameter is used in setup.c // 此参数在setup.c中使用
#define ADC_TOTAL_CONV_TIME     (ADC_CLOCK_DIV * ADC_CONV_CLOCK_CYCLES) // = ((SystemCoreClock / ADC_CLOCK_HZ) * ADC_CONV_CLOCK_CYCLES), where ADC_CLOCK_HZ = SystemCoreClock/ADC_CLOCK_DIV // 其中ADC_CLOCK_HZ = SystemCoreClock/ADC_CLOCK_DIV
// ########################### END OF  DO-NOT-TOUCH SETTINGS (请勿修改的设置结束) ############################

// ############################### BOARD VARIANT (主板变体) ###############################
/* Board Variant // 主板变体
 * 0 - Default board type // 默认主板类型
 * 1 - Alternate board type with different pin mapping for DCLINK, Buzzer and ON/OFF, Button and Charger // 备用主板类型，具有不同的DCLINK、蜂鸣器、开关、按钮和充电器引脚映射
*/
#define BOARD_VARIANT           0         // change if board with alternate pin mapping // 如果主板使用备用引脚映射则更改
// ######################## END OF BOARD VARIANT (主板变体结束) ###############################

// ############################### BATTERY (电池) ###############################
/* Battery voltage calibration: connect power source. // 电池电压校准：连接电源。
 * see How to calibrate. // 参见校准方法。
 * Write debug output value nr 5 to BAT_CALIB_ADC. make and flash firmware. // 将调试输出值5写入BAT_CALIB_ADC。编译并烧录固件。
 * Then you can verify voltage on debug output value 6 (to get calibrated voltage multiplied by 100). // 然后您可以在调试输出值6上验证电压（获取校准后的电压乘以100）。
*/
#define BAT_FILT_COEF           655       // battery voltage filter coefficient in fixed-point. coef_fixedPoint = coef_floatingPoint * 2^16. In this case 655 = 0.01 * 2^16 // 电池电压滤波系数（定点数）。coef_fixedPoint = coef_floatingPoint * 2^16。本例中655 = 0.01 * 2^16
#define BAT_CALIB_REAL_VOLTAGE  3970      // input voltage measured by multimeter (multiplied by 100). In this case 43.00 V * 100 = 4300 // 万用表测量的输入电压（乘以100）。本例中43.00V * 100 = 4300
#define BAT_CALIB_ADC           1492      // adc-value measured by mainboard (value nr 5 on UART debug output) // 主板测量的ADC值（UART调试输出上的值5）
#define BAT_CELLS               10        // battery number of cells. Normal Hoverboard battery: 10s // 电池串联电芯数。普通平衡车电池：10串
#define BAT_LVL2_ENABLE         0         // to beep or not to beep, 1 or 0 // 是否蜂鸣，1或0
#define BAT_LVL1_ENABLE         1         // to beep or not to beep, 1 or 0 // 是否蜂鸣，1或0
#define BAT_DEAD_ENABLE         1         // to poweroff or not to poweroff, 1 or 0 // 是否关机，1或0
#define BAT_BLINK_INTERVAL      80        // battery led blink interval (80 loops * 5ms ~= 400ms) // 电池LED闪烁间隔（80个循环 * 5毫秒 ≈ 400毫秒）
#define BAT_LVL5                (390 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 绿色闪烁：不蜂鸣
#define BAT_LVL4                (380 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 黄色：不蜂鸣
#define BAT_LVL3                (370 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 黄色闪烁：不蜂鸣 
#define BAT_LVL2                (360 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 红色：在此电压水平下轻柔蜂鸣。[V*100/电芯]。本例中3.60V/电芯
#define BAT_LVL1                (350 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 红色闪烁：快速蜂鸣。电池即将耗尽，请立即充电！[V*100/电芯]。本例中3.50V/电芯
#define BAT_DEAD                (337 * BAT_CELLS * BAT_CALIB_ADC) / BAT_CALIB_REAL_VOLTAGE    // 所有LED熄灭：欠压关机（非行驶状态下）。[V*100/电芯]。本例中3.37V/电芯
// ######################## END OF BATTERY (电池设置结束) ###############################



// ############################### TEMPERATURE (温度) ###############################
/* Board overheat detection: the sensor is inside the STM/GD chip. // 主板过热检测：传感器位于STM/GD芯片内部。
 * It is very inaccurate without calibration (up to 45°C). So only enable this funcion after calibration! // 未经校准非常不准确（误差可达45°C）。因此仅在校准后启用此功能！
 * Let your board cool down. // 让主板冷却。
 * see <How to calibrate. // 参见校准方法。
 * Get the real temp of the chip by thermo cam or another temp-sensor taped on top of the chip and write it to TEMP_CAL_LOW_DEG_C. // 通过热成像仪或贴在芯片上的其他温度传感器获取芯片真实温度，写入TEMP_CAL_LOW_DEG_C。
 * Write debug output value 8 to TEMP_CAL_LOW_ADC. drive around to warm up the board. it should be at least 20°C warmer. repeat it for the HIGH-values. // 将调试输出值8写入TEMP_CAL_LOW_ADC。行驶使主板预热，应至少升温20°C。对HIGH值重复此操作。
 * Enable warning and/or poweroff and make and flash firmware. // 启用警告和/或关机，编译并烧录固件。
*/
#define TEMP_FILT_COEF          655       // temperature filter coefficient in fixed-point. coef_fixedPoint = coef_floatingPoint * 2^16. In this case 655 = 0.01 * 2^16 // 温度滤波系数（定点数）。coef_fixedPoint = coef_floatingPoint * 2^16。本例中655 = 0.01 * 2^16
#define TEMP_CAL_LOW_ADC        1655      // temperature 1: ADC value // 温度点1：ADC值
#define TEMP_CAL_LOW_DEG_C      358       // temperature 1: measured temperature [°C * 10]. Here 35.8 °C // 温度点1：测量温度[°C * 10]。此处35.8°C
#define TEMP_CAL_HIGH_ADC       1588      // temperature 2: ADC value // 温度点2：ADC值
#define TEMP_CAL_HIGH_DEG_C     489       // temperature 2: measured temperature [°C * 10]. Here 48.9 °C // 温度点2：测量温度[°C * 10]。此处48.9°C
#define TEMP_WARNING_ENABLE     0         // to beep or not to beep, 1 or 0, DO NOT ACTIVITE WITHOUT CALIBRATION! // 是否蜂鸣，1或0，未经校准请勿激活！
#define TEMP_WARNING            600       // annoying fast beeps [°C * 10].  Here 60.0 °C // 烦人的快速蜂鸣[°C * 10]。此处60.0°C
#define TEMP_POWEROFF_ENABLE    0         // to poweroff or not to poweroff, 1 or 0, DO NOT ACTIVITE WITHOUT CALIBRATION! // 是否关机，1或0，未经校准请勿激活！
#define TEMP_POWEROFF           650       // overheat poweroff. (while not driving) [°C * 10]. Here 65.0 °C // 过热关机（非行驶状态下）。[°C * 10]。此处65.0°C
// ######################## END OF TEMPERATURE (温度设置结束) ###############################



// ############################### MOTOR CONTROL (电机控制) #########################
/* GENERAL NOTES: // 通用说明：
 * 1. The parameters here are over-writing the default motor parameters. For all the available parameters check BLDC_controller_data.c // 1. 此处的参数将覆盖默认电机参数。所有可用参数请查看BLDC_controller_data.c
 * 2. The parameters are represented in fixed point data type for a more efficient code execution // 2. 参数使用定点数据类型表示，以实现更高效的代码执行
 * 3. For calibrating the fixed-point parameters use the Fixed-Point Viewer tool (see <https://github.com/EmanuelFeru/FixedPointViewer>) // 3. 使用Fixed-Point Viewer工具校准定点参数
 * 4. For more details regarding the parameters and the working principle of the controller please consult the Simulink model // 4. 有关参数和控制器工作原理的更多详情，请参阅Simulink模型
 * 5. A webview was created, so Matlab/Simulink installation is not needed, unless you want to regenerate the code. // 5. 已创建Web视图，因此除非您想重新生成代码，否则无需安装Matlab/Simulink
 * The webview is an html page that can be opened with browsers like: Microsoft Internet Explorer or Microsoft Edge // Web视图是一个html页面，可使用Microsoft Internet Explorer或Microsoft Edge等浏览器打开
 *
 * NOTES Field Weakening / Phase Advance: // 弱磁/提前角说明：
 * 1. The Field Weakening is a linear interpolation from 0 to FIELD_WEAK_MAX or PHASE_ADV_MAX (depeding if FOC or SIN is selected, respectively) // 1. 弱磁是从0到FIELD_WEAK_MAX或PHASE_ADV_MAX的线性插值（取决于选择FOC还是SIN）
 * 2. The Field Weakening starts engaging at FIELD_WEAK_LO and reaches the maximum value at FIELD_WEAK_HI // 2. 弱磁在FIELD_WEAK_LO开始介入，在FIELD_WEAK_HI达到最大值
 * 3. If you re-calibrate the Field Weakening please take all the safety measures! The motors can spin very fast! // 3. 如果重新校准弱磁，请采取所有安全措施！电机可能旋转得非常快！

   Inputs: // 输入：
    - input1[inIdx].cmd and input2[inIdx].cmd: normalized input values. INPUT_MIN to INPUT_MAX // 归一化的输入值。INPUT_MIN到INPUT_MAX
    - button1 and button2: digital input values. 0 or 1 // 数字输入值。0或1
    - adc_buffer.l_tx2 and adc_buffer.l_rx2: unfiltered ADC values (you do not need them). 0 to 4095 // 未滤波的ADC值（您不需要它们）。0到4095
   Outputs: // 输出：
    - cmdL and cmdR: normal driving INPUT_MIN to INPUT_MAX // 正常驱动INPUT_MIN到INPUT_MAX
*/
#define COM_CTRL        0               // [-] Commutation Control Type // 换向控制类型
#define SIN_CTRL        1               // [-] Sinusoidal Control Type // 正弦控制类型
#define FOC_CTRL        2               // [-] Field Oriented Control (FOC) Type // 磁场定向控制（FOC）类型

#define OPEN_MODE       0               // [-] OPEN mode // 开环模式
#define VLT_MODE        1               // [-] VOLTAGE mode // 电压模式
#define SPD_MODE        2               // [-] SPEED mode // 速度模式
#define TRQ_MODE        3               // [-] TORQUE mode // 扭矩模式

// Enable/Disable Motor // 启用/禁用电机
#define MOTOR_LEFT_ENA                  // [-] Enable LEFT motor.  Comment-out if this motor is not needed to be operational // 启用左侧电机。如果不需要该电机运行则注释掉
#define MOTOR_RIGHT_ENA                 // [-] Enable RIGHT motor. Comment-out if this motor is not needed to be operational // 启用右侧电机。如果不需要该电机运行则注释掉

// Control selections // 控制选择
#define CTRL_TYP_SEL    FOC_CTRL        // [-] Control type selection: COM_CTRL, SIN_CTRL, FOC_CTRL (default) // 控制类型选择：COM_CTRL、SIN_CTRL、FOC_CTRL（默认）
#define CTRL_MOD_REQ    VLT_MODE        // [-] Control mode request: OPEN_MODE, VLT_MODE (default), SPD_MODE, TRQ_MODE. Note: SPD_MODE and TRQ_MODE are only available for CTRL_FOC! // 控制模式请求：OPEN_MODE、VLT_MODE（默认）、SPD_MODE、TRQ_MODE。注意：SPD_MODE和TRQ_MODE仅适用于CTRL_FOC！
#define DIAG_ENA        1               // [-] Motor Diagnostics enable flag: 0 = Disabled, 1 = Enabled (default) // 电机诊断启用标志：0 = 禁用，1 = 启用（默认）

// Limitation settings // 限制设置
#define I_MOT_MAX       15              // [A] Maximum single motor current limit // 单电机最大电流限制
#define I_DC_MAX        17              // [A] Maximum stage2 DC Link current limit for Commutation and Sinusoidal types (This is the final current protection. Above this value, current chopping is applied. To avoid this make sure that I_DC_MAX = I_MOT_MAX + 2A) // 换向和正弦类型第二阶段直流母线最大电流限制（这是最终电流保护。超过此值将应用电流斩波。为避免此情况，请确保I_DC_MAX = I_MOT_MAX + 2A）
#define N_MOT_MAX       1000            // [rpm] Maximum motor speed limit // 电机最大转速限制

// Field Weakening / Phase Advance // 弱磁/提前角
#define FIELD_WEAK_ENA  0               // [-] Field Weakening / Phase Advance enable flag: 0 = Disabled (default), 1 = Enabled // 弱磁/提前角启用标志：0 = 禁用（默认），1 = 启用
#define FIELD_WEAK_MAX  5               // [A] Maximum Field Weakening D axis current (only for FOC). Higher current results in higher maximum speed. Up to 10A has been tested using 10" wheels. // 最大弱磁D轴电流（仅用于FOC）。电流越大最高速度越高。使用10英寸轮子已测试高达10A
#define PHASE_ADV_MAX   25              // [deg] Maximum Phase Advance angle (only for SIN). Higher angle results in higher maximum speed. // 最大提前角（仅用于SIN）。角度越大最高速度越高
#define FIELD_WEAK_HI   1000            // (1000, 1500] Input target High threshold for reaching maximum Field Weakening / Phase Advance. Do NOT set this higher than 1500. // 达到最大弱磁/提前角的输入目标高阈值。请勿设置高于1500
#define FIELD_WEAK_LO   750             // ( 500, 1000] Input target Low threshold for starting Field Weakening / Phase Advance. Do NOT set this higher than 1000. // 开始弱磁/提前角的输入目标低阈值。请勿设置高于1000

// Extra functionality // 额外功能
#define STANDSTILL_HOLD_ENABLE          // 到达停止状态时保持位置的标志。仅适用于电压或扭矩模式。
#define ELECTRIC_BRAKE_ENABLE           // [-] Flag to enable electric brake and replace the motor "freewheel" with a constant braking when the input torque request is 0. Only available and makes sense for TORQUE mode. // 启用电子制动，当输入扭矩请求为0时用恒定制动代替电机"自由滑行"。仅适用于扭矩模式。
#define ELECTRIC_BRAKE_MAX    50       // (0, 500) Maximum electric brake to be applied when input torque request is 0 (pedal fully released). // 输入扭矩请求为0（踏板完全松开）时施加的最大电子制动
#define ELECTRIC_BRAKE_THRES  120       // (0, 500) Threshold below at which the electric brake starts engaging. // 电子制动开始介入的阈值（低于此值开始制动）
// ########################### END OF MOTOR CONTROL (电机控制结束) ########################



// ############################## DEFAULT SETTINGS (默认设置) ############################
// Default settings will be applied at the end of this config file if not set before // 如果之前未设置，默认设置在配置文件末尾应用
#define INACTIVITY_TIMEOUT        8       // Minutes of not driving until poweroff. it is not very precise. // 停止行驶后到自动关机的分钟数。不太精确
#define BEEPS_BACKWARD            1       // 0 or 1 // 0或1，倒车蜂鸣
#define ADC_MARGIN                100     // ADC input margin applied on the raw ADC min and max to make sure the MIN and MAX values are reached even in the presence of noise // ADC输入裕量，应用于原始ADC最小值和最大值，确保即使在噪声存在时也能达到最小值和最大值
#define ADC_PROTECT_TIMEOUT       100     // ADC Protection: number of wrong / missing input commands before safety state is taken // ADC保护：进入安全状态前允许的错误/丢失输入命令次数
#define ADC_PROTECT_THRESH        200     // ADC Protection threshold below/above the MIN/MAX ADC values // ADC保护阈值，低于/高于ADC最小/最大值
// #define AUTO_CALIBRATION_ENA              // Enable/Disable input auto-calibration by holding power button pressed. Un-comment this if auto-calibration is not needed. // 启用/禁用通过按住电源按钮进行输入自动校准。如果不需要自动校准则取消注释此项。

/* FILTER is in fixdt(0,16,16): VAL_fixedPoint = VAL_floatingPoint * 2^16. In this case 6553 = 0.1 * 2^16 // FILTER使用fixdt(0,16,16)格式：VAL_fixedPoint = VAL_floatingPoint * 2^16。本例中6553 = 0.1 * 2^16
 * Value of COEFFICIENT is in fixdt(1,16,14) // COEFFICIENT的值使用fixdt(1,16,14)格式
 * If VAL_floatingPoint >= 0, VAL_fixedPoint = VAL_floatingPoint * 2^14 // 如果VAL_floatingPoint >= 0，则VAL_fixedPoint = VAL_floatingPoint * 2^14
 * If VAL_floatingPoint < 0,  VAL_fixedPoint = 2^16 + floor(VAL_floatingPoint * 2^14). // 如果VAL_floatingPoint < 0，则VAL_fixedPoint = 2^16 + floor(VAL_floatingPoint * 2^14)
*/
// Value of RATE is in fixdt(1,16,4): VAL_fixedPoint = VAL_floatingPoint * 2^4. In this case 480 = 30 * 2^4 // RATE的值使用fixdt(1,16,4)格式：VAL_fixedPoint = VAL_floatingPoint * 2^4。本例中480 = 30 * 2^4
#define DEFAULT_RATE                480   // 30.0f [-] lower value == slower rate [0, 32767] = [0.0, 2047.9375]. Do NOT make rate negative (>32767) // 较低的值 == 较慢的速率[0, 32767] = [0.0, 2047.9375]。请勿使速率为负（>32767）
#define DEFAULT_FILTER              6553  // Default for FILTER 0.1f [-] lower value == softer filter [0, 65535] = [0.0 - 1.0]. // FILTER默认值0.1f，较低的值 == 较柔和的滤波[0, 65535] = [0.0 - 1.0]
#define DEFAULT_SPEED_COEFFICIENT   16384 // Default for SPEED_COEFFICIENT 1.0f [-] higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14 // SPEED_COEFFICIENT默认值1.0f，较高的值 == 强度更大。[0, 65535] = [-2.0 - 2.0]。本例中16384 = 1.0 * 2^14
#define DEFAULT_STEER_COEFFICIENT   8192  // Defualt for STEER_COEFFICIENT 0.5f [-] higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case  8192 = 0.5 * 2^14. If you do not want any steering, set it to 0. // STEER_COEFFICIENT默认值0.5f，较高的值 == 强度更大。[0, 65535] = [-2.0 - 2.0]。本例中8192 = 0.5 * 2^14。如果不需要转向，设为0
// ######################### END OF DEFAULT SETTINGS (默认设置结束) ##########################



// ############################## INPUT FORMAT (输入格式) ############################
/* ***_INPUT: TYPE, MIN, MID, MAX, DEADBAND // 类型，最小值，中点，最大值，死区
 * -----------------------------------------
 * TYPE:      0:Disabled, 1:Normal Pot, 2:Middle Resting Pot, 3:Auto-detect // 类型：0：禁用，1：普通电位器，2：中位回位电位器，3：自动检测
 * MIN:       min ADC1-value while poti at minimum-position (0 - 4095) // 电位器在最低位置时的最小ADC1值（0 - 4095）
 * MID:       mid ADC1-value while poti at mid-position (INPUT_MIN - INPUT_MAX) // 电位器在中间位置时的中点ADC1值（INPUT_MIN - INPUT_MAX）
 * MAX:       max ADC2-value while poti at maximum-position (0 - 4095) // 电位器在最高位置时的最大ADC2值（0 - 4095）
 * DEADBAND:  how much of the center position is considered 'center' (100 = values -100 to 100 are considered 0) // 中心位置的多少被视为"中心"（100 = -100到100的值被视为0）
 * 
 * Dual-inputs // 双输入
 * PRI_INPUT: Primary   Input. These limits will be used for the input with priority 0 // 主输入。这些限制将用于优先级0的输入
 * AUX_INPUT: Auxiliary Input. These limits will be used for the input with priority 1 // 辅助输入。这些限制将用于优先级1的输入
 * -----------------------------------------
*/
 // ############################## END OF INPUT FORMAT (输入格式说明结束) ############################



// ############################## CRUISE CONTROL SETTINGS (定速巡航设置) ############################
/* Cruise Control info: // 定速巡航信息
 * enable CRUISE_CONTROL_SUPPORT and (SUPPORT_BUTTONS_LEFT or SUPPORT_BUTTONS_RIGHT depending on which cable is the button installed) // 启用CRUISE_CONTROL_SUPPORT和（SUPPORT_BUTTONS_LEFT或SUPPORT_BUTTONS_RIGHT，取决于按钮安装在哪个线缆上）
 * can be activated/deactivated by pressing button1 (Blue cable) to GND // 可通过将button1（蓝色线）短接到GND来激活/停用
 * when activated, it maintains the current speed by switching to SPD_MODE. Acceleration is still possible via the input request, but when released it resumes to previous set speed. // 激活时，通过切换到SPD_MODE保持当前速度。仍可通过输入请求加速，但松开后恢复到之前设定的速度
 * when deactivated, it returns to previous control MODE and follows the input request. // 停用时，返回到之前的控制模式并跟随输入请求
*/
// #define CRUISE_CONTROL_SUPPORT
// #define SUPPORT_BUTTONS_LEFT              // Use button1 (Blue Left cable)  to activate/deactivate Cruise Control // 使用button1（蓝色左侧线缆）激活/停用定速巡航
// #define SUPPORT_BUTTONS_RIGHT             // Use button1 (Blue Right cable) to activate/deactivate Cruise Control // 使用button1（蓝色右侧线缆）激活/停用定速巡航

// ######################### END OF CRUISE CONTROL SETTINGS (定速巡航设置结束) ##########################



// ############################### DEBUG SERIAL (调试串口) ###############################
/* Connect GND and RX of a 3.3v uart-usb adapter to the left (USART2) or right sensor board cable (USART3) // 将3.3V UART-USB适配器的GND和RX连接到左侧（USART2）或右侧传感器板线缆（USART3）
 * Be careful not to use the red wire of the cable. 15v will destroy everything. // 注意不要使用线缆的红色线。15V会损坏一切。
 * If you are using VARIANT_NUNCHUK, disable it temporarily. // 如果您正在使用VARIANT_NUNCHUK，请暂时禁用它。
 * enable DEBUG_SERIAL_USART3 or DEBUG_SERIAL_USART2 // 启用DEBUG_SERIAL_USART3或DEBUG_SERIAL_USART2
 *
 *
 * DEBUG ASCII output is: // 调试ASCII输出如下：
 * // "in1:345 in2:1337 cmdL:0 cmdR:0 BatADC:0 BatV:0 TempADC:0 Temp:0\r\n"
 *
 * in1:     (int16_t)input1[inIdx].raw);                                        raw input1: ADC1, UART, PWM, PPM, iBUS // 原始输入1：ADC1、UART、PWM、PPM、iBUS
 * in2:     (int16_t)input2[inIdx].raw);                                        raw input2: ADC2, UART, PWM, PPM, iBUS // 原始输入2：ADC2、UART、PWM、PPM、iBUS
 * cmdL:    (int16_t)cmdL);                                                     output command Left: [-1000, 1000] // 左侧输出命令：[-1000, 1000]
 * cmdR:    (int16_t)cmdR);                                                     output command Right: [-1000, 1000] // 右侧输出命令：[-1000, 1000]
 * BatADC:  (int16_t)adc_buffer.batt1);                                         Battery adc-value measured by mainboard // 主板测量的电池ADC值
 * BatV:    (int16_t)(batVoltage * BAT_CALIB_REAL_VOLTAGE / BAT_CALIB_ADC));    Battery calibrated voltage multiplied by 100 for verifying battery voltage calibration // 电池校准电压乘以100，用于验证电池电压校准
 * TempADC: (int16_t)board_temp_adcFilt);                                       for board temperature calibration // 用于主板温度校准
 * Temp:    (int16_t)board_temp_deg_c);                                         Temperature in celcius for verifying board temperature calibration // 摄氏度温度，用于验证主板温度校准
 *
*/

// #define DEBUG_SERIAL_USART2          // left sensor board cable, disable if ADC or PPM is used! // 左侧传感器板线缆，如果使用ADC或PPM则禁用！
// #define DEBUG_SERIAL_USART3          // right sensor board cable, disable if I2C (nunchuk or lcd) is used! // 右侧传感器板线缆，如果使用I2C（nunchuk或lcd）则禁用！
// #define DEBUG_SERIAL_PROTOCOL        // uncomment this to send user commands to the board, change parameters and print specific signals (see comms.c for the user commands) // 取消注释可向主板发送用户命令、更改参数并打印特定信号（用户命令见comms.c）
// ########################### END OF DEBUG SERIAL (调试串口设置结束) ############################



// ############################### DEBUG LCD (调试LCD) ###############################
// #define DEBUG_I2C_LCD                // standard 16x2 or larger text-lcd via i2c-converter on right sensor board cable // 通过右侧传感器板线缆上的I2C转换器连接标准16x2或更大的文本LCD
// ########################### END OF DEBUG LCD (调试LCD设置结束) ############################


// ############################### BUZZER ENABLE / DISABLE (蜂鸣器启用/禁用) ###############################
#define BUZZER_ENABLED              // If enabled the buzzer will buzz, otherwise not. // 如果启用则蜂鸣器会响，否则不响。
// ########################### END OF BUZZER ENABLE / DISABLE (蜂鸣器启用/禁用结束) ############################



// ################################# VARIANT_ADC SETTINGS (ADC变体设置) ############################
#ifdef VARIANT_ADC
/* CONTROL VIA TWO POTENTIOMETERS // 通过两个电位器控制
 * Connect potis to left sensor board cable (0 to 3.3V) (do NOT use the red 15V wire!) // 将电位器连接到左侧传感器板线缆（0至3.3V）（请勿使用红色15V线！）
 *
 * Auto-calibration of the ADC Limit to finds the Minimum, Maximum, and Middle for the ADC input // ADC限制自动校准，查找ADC输入的最小值、最大值和中间值
 * Procedure: // 步骤：
 * - press the power button for more than 5 sec and release after the beep sound // - 按住电源按钮超过5秒，听到蜂鸣后松开
 * - move the potentiometers freely to the min and max limits repeatedly // - 自由移动电位器反复到最小和最大限制
 * - release potentiometers to the resting postion // - 将电位器松开到静止位置
 * - press the power button to confirm or wait for the 20 sec timeout // - 按电源按钮确认或等待20秒超时
 * The Values will be saved to flash. Values are persistent if you flash with platformio. To erase them, make a full chip erase. // 值将保存到闪存。如果使用platformio烧录，值会持久保存。要擦除它们，请执行全芯片擦除。
 *
 * After calibration you can optionally write the values to the following defines // 校准后，您可以选择将值写入以下定义
 * Procedure: // 步骤：
 * - connect gnd, rx and tx of a usb-uart converter in 3.3V mode to the right sensor board cable (do NOT use the red 15V wire!) // - 将USB-UART转换器的GND、RX和TX以3.3V模式连接到右侧传感器板线缆（请勿使用红色15V线！）
 * - readout values using a serial terminal in 115200 baud rate // - 使用115200波特率的串行终端读取值
 * - turn the potis to minimum position, write value in1 to PRI_INPUT1 MIN and value in2 to PRI_INPUT2 MIN // - 将电位器转到最小位置，将值in1写入PRI_INPUT1 MIN，值in2写入PRI_INPUT2 MIN
 * - turn the potis to maximum position, write value in1 to PRI_INPUT1 MAX and value in2 to PRI_INPUT2 MAX // - 将电位器转到最大位置，将值in1写入PRI_INPUT1 MAX，值in2写入PRI_INPUT2 MAX
 * - for middle resting potis: Let the potis in the middle resting position, write value in1 to PRI_INPUT1 MID and value in2 to PRI_INPUT2 MID // - 对于中位回位电位器：将电位器置于中间静止位置，将值in1写入PRI_INPUT1 MID，值in2写入PRI_INPUT2 MID
*/
  #define CONTROL_ADC           0         // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2! // 使用ADC作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART2、FEEDBACK_SERIAL_USART2、DEBUG_SERIAL_USART2！

  // #define DUAL_INPUTS                     //  ADC*(Primary) + UART(Auxiliary). Uncomment this to use Dual-inputs // ADC*(主) + UART(辅)。取消注释以使用双输入
  #define PRI_INPUT1            3, 0, 0, 4095, 0      // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section // 类型、最小值、中点、最大值、死区。参见输入格式部分
  #define PRI_INPUT2            3, 0, 0, 4095, 0      // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY     0x1101    // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h // 闪存写入密钥。更改此密钥可忽略闪存中的输入校准并使用config.h中的设置
    // #define SIDEBOARD_SERIAL_USART3 1
    #define CONTROL_SERIAL_USART3 1       // right sensor board cable. Number indicates priority for dual-input. Disable if I2C (nunchuk or lcd) is used! For Arduino control check the hoverSerial.ino // 右侧传感器板线缆。数字表示双输入中的优先级。如果使用I2C（nunchuk或lcd）则禁用！Arduino控制请查看hoverSerial.ino
    #define FEEDBACK_SERIAL_USART3        // right sensor board cable, disable if I2C (nunchuk or lcd) is used! // 右侧传感器板线缆，如果使用I2C（nunchuk或lcd）则禁用！
    #define AUX_INPUT1          3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2          3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY     0x1001    // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define DEBUG_SERIAL_USART3           // right sensor board cable, disable if I2C (nunchuk or lcd) is used! // 右侧传感器板线缆，如果使用I2C（nunchuk或lcd）则禁用！
  #endif

  // #define TANK_STEERING                   // use for tank steering, each input controls each wheel // 用于坦克式转向，每个输入控制每个轮子 
  // #define ADC_ALTERNATE_CONNECT           // use to swap ADC inputs // 用于交换ADC输入
  // #define SUPPORT_BUTTONS_LEFT            // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2! // 使用左侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT           // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3! // 使用右侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！
#endif
// ############################# END OF VARIANT_ADC SETTINGS (ADC变体设置结束) #########################



// ############################ VARIANT_USART SETTINGS (USART变体设置) ############################
#ifdef VARIANT_USART
  // #define SIDEBOARD_SERIAL_USART2 0
  #define CONTROL_SERIAL_USART2  0    // left sensor board cable, disable if ADC or PPM is used! For Arduino control check the hoverSerial.ino // 左侧传感器板线缆，如果使用ADC或PPM则禁用！Arduino控制请查看hoverSerial.ino
  #define FEEDBACK_SERIAL_USART2      // left sensor board cable, disable if ADC or PPM is used! // 左侧传感器板线缆，如果使用ADC或PPM则禁用！

  // #define SIDEBOARD_SERIAL_USART3 0
  // #define CONTROL_SERIAL_USART3  0    // right sensor board cable. Number indicates priority for dual-input. Disable if I2C (nunchuk or lcd) is used! For Arduino control check the hoverSerial.ino // 右侧传感器板线缆。数字表示双输入中的优先级。如果使用I2C（nunchuk或lcd）则禁用！Arduino控制请查看hoverSerial.ino
  // #define FEEDBACK_SERIAL_USART3      // right sensor board cable, disable if I2C (nunchuk or lcd) is used! // 右侧传感器板线缆，如果使用I2C（nunchuk或lcd）则禁用！
 
  // #define DUAL_INPUTS                 //  UART*(Primary) + SIDEBOARD(Auxiliary). Uncomment this to use Dual-inputs // UART*(主) + 侧板(辅)。取消注释以使用双输入
  #define PRI_INPUT1             3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #define PRI_INPUT2             3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY      0x1102  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define SIDEBOARD_SERIAL_USART2 1   // left sideboard // 左侧侧板
    #define SIDEBOARD_SERIAL_USART3 1   // right sideboard // 右侧侧板
    #define AUX_INPUT1           3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2           3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY      0x1002  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
  #endif

  // #define TANK_STEERING              // use for tank steering, each input controls each wheel // 用于坦克式转向，每个输入控制每个轮子 
  // #define SUPPORT_BUTTONS_LEFT       // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2! // 使用左侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT      // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3! // 使用右侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！
#endif
// ######################## END OF VARIANT_USART SETTINGS (USART变体设置结束) #########################



// ################################# VARIANT_NUNCHUK SETTINGS (NUNCHUK变体设置) ############################
#ifdef VARIANT_NUNCHUK
  /* on Right sensor cable // 在右侧传感器线缆上
   * keep cable short, use shielded cable, use ferrits, stabalize voltage in nunchuk, // 保持线缆短，使用屏蔽线缆，使用磁珠，稳定nunchuk中的电压
   * use the right one of the 2 types of nunchuks, add i2c pullups. // 使用两种nunchuk类型中的正确一种，添加I2C上拉电阻
   * use original nunchuk. most clones does not work very well. // 使用原装nunchuk。大多数克隆版效果不佳。
   * Recommendation: Nunchuk Breakout Board https://github.com/Jan--Henrik/hoverboard-breakout // 推荐：Nunchuk分线板
  */
  #define CONTROL_NUNCHUK         0       // use nunchuk as input. Number indicates priority for dual-input. Disable FEEDBACK_SERIAL_USART3, DEBUG_SERIAL_USART3! // 使用nunchuk作为输入。数字表示双输入中的优先级。禁用FEEDBACK_SERIAL_USART3、DEBUG_SERIAL_USART3！

  // #define DUAL_INPUTS                     // Nunchuk*(Primary) + UART(Auxiliary). Uncomment this to use Dual-inputs // Nunchuk*(主) + UART(辅)。取消注释以使用双输入
  #define PRI_INPUT1              2, -1024, 0, 1024, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #define PRI_INPUT2              2, -1024, 0, 1024, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1103  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define SIDEBOARD_SERIAL_USART2 1
    #define CONTROL_SERIAL_USART2 1       // left sensor board cable, disable if ADC or PPM is used! For Arduino control check the hoverSerial.ino // 左侧传感器板线缆，如果使用ADC或PPM则禁用！Arduino控制请查看hoverSerial.ino
    #define FEEDBACK_SERIAL_USART2        // left sensor board cable, disable if ADC or PPM is used! // 左侧传感器板线缆，如果使用ADC或PPM则禁用！
    #define AUX_INPUT1            3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 0     // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1003  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define DEBUG_SERIAL_USART2           // left sensor cable debug // 左侧传感器线缆调试
  #endif

  // # maybe good for ARMCHAIR # // 也许适合扶手椅
  #define FILTER                  3276    //  0.05f
  #define SPEED_COEFFICIENT       8192    //  0.5f
  #define STEER_COEFFICIENT       62259   // -0.2f
  // #define SUPPORT_BUTTONS                 // Define for Nunchuk buttons support // 定义以支持Nunchuk按钮
#endif
// ############################# END OF VARIANT_NUNCHUK SETTINGS (NUNCHUK变体设置结束) #########################



// ################################# VARIANT_PPM SETTINGS (PPM变体设置) ##############################
#ifdef VARIANT_PPM
/* ###### CONTROL VIA RC REMOTE ###### // 通过遥控器控制
 * Right sensor board cable. Channel 1: steering, Channel 2: speed. // 右侧传感器板线缆。通道1：转向，通道2：速度。
 * https://gist.github.com/peterpoetzi/1b63a4a844162196613871767189bd05
*/
  // #define DUAL_INPUTS                     // ADC*(Primary) + PPM(Auxiliary). Uncomment this to use Dual-inputs // ADC*(主) + PPM(辅)。取消注释以使用双输入
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1104  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_ADC           0       // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2! // 使用ADC作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART2、FEEDBACK_SERIAL_USART2、DEBUG_SERIAL_USART2！
    #define CONTROL_PPM_RIGHT     1       // use PPM-Sum as input on the RIGHT cable. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART3! // 在右侧线缆上使用PPM和信号作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART3！
    #define PRI_INPUT1            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1004  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define CONTROL_PPM_LEFT      0       // use PPM-Sum as input on the LEFT cable. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2! // 在左侧线缆上使用PPM和信号作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART2！
    #define CONTROL_PPM_RIGHT     0       // use PPM-Sum as input on the RIGHT cable. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART3! // 在右侧线缆上使用PPM和信号作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART3！
    #define PRI_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #endif
  #define PPM_NUM_CHANNELS        6       // total number of PPM channels to receive, even if they are not used. // 要接收的PPM通道总数，即使未使用

  // #define TANK_STEERING                   // use for tank steering, each input controls each wheel // 用于坦克式转向，每个输入控制每个轮子 
  // #define SUPPORT_BUTTONS                 // Define for PPM buttons support // 定义以支持PPM按钮
  // #define SUPPORT_BUTTONS_LEFT            // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2! // 使用左侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT           // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3! // 使用右侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！

  #if defined(CONTROL_PPM_RIGHT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART2           // left sensor cable debug // 左侧传感器线缆调试
  #elif defined(CONTROL_PPM_LEFT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART3           // right sensor cable debug // 右侧传感器线缆调试
  #endif
#endif
// ############################# END OF VARIANT_PPM SETTINGS (PPM变体设置结束) ############################


// ################################# VARIANT_PWM SETTINGS (PWM变体设置) ##############################
#ifdef VARIANT_PWM
/* ###### CONTROL VIA RC REMOTE ###### // 通过遥控器控制
 * Right sensor board cable. Connect PA2 to channel 1 and PA3 to channel 2 on receiver. // 右侧传感器板线缆。将PA2连接到接收器的通道1，PA3连接到通道2。
 * Channel 1: steering, Channel 2: speed. // 通道1：转向，通道2：速度
*/
  // #define DUAL_INPUTS                     // ADC*(Primary) + PWM(Auxiliary). Uncomment this to use Dual-inputs // ADC*(主) + PWM(辅)。取消注释以使用双输入
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1105  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_ADC           0       // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2! // 使用ADC作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART2、FEEDBACK_SERIAL_USART2、DEBUG_SERIAL_USART2！
    #define CONTROL_PWM_RIGHT     1       // use RC PWM as input on the RIGHT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3! // 在右侧线缆上使用RC PWM作为输入。数字表示双输入中的优先级。禁用DEBUG_SERIAL_USART3！
    #define PRI_INPUT1            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3,     0, 0, 4095,   0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1005  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    // #define CONTROL_PWM_LEFT      0       // use RC PWM as input on the LEFT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART2! // 在左侧线缆上使用RC PWM作为输入。数字表示双输入中的优先级。禁用DEBUG_SERIAL_USART2！
    #define CONTROL_PWM_RIGHT     0       // use RC PWM as input on the RIGHT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3! // 在右侧线缆上使用RC PWM作为输入。数字表示双输入中的优先级。禁用DEBUG_SERIAL_USART3！
    #define PRI_INPUT1            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3, -1000, 0, 1000, 100  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #endif

  #define FILTER                  6553    // 0.1f [-] fixdt(0,16,16) lower value == softer filter [0, 65535] = [0.0 - 1.0]. // 较低的值 == 较柔和的滤波
  #define SPEED_COEFFICIENT       16384   // 1.0f [-] fixdt(1,16,14) higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14 // 较高的值 == 强度更大
  #define STEER_COEFFICIENT       16384   // 1.0f [-] fixdt(1,16,14) higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14. If you do not want any steering, set it to 0. // 较高的值 == 强度更大。如果不需要转向，设为0
  // #define TANK_STEERING                   // use for tank steering, each input controls each wheel // 用于坦克式转向，每个输入控制每个轮子 
  // #define INVERT_R_DIRECTION
  // #define INVERT_L_DIRECTION
  // #define SUPPORT_BUTTONS_LEFT            // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2! // 使用左侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT           // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3! // 使用右侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！

  #if defined(CONTROL_PWM_RIGHT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART2           // left sensor cable debug // 左侧传感器线缆调试
  #elif defined(CONTROL_PWM_LEFT) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART3           // right sensor cable debug // 右侧传感器线缆调试
  #endif
#endif
// ############################# END OF VARIANT_PWM SETTINGS (PWM变体设置结束) ############################



// ################################# VARIANT_IBUS SETTINGS (IBUS变体设置) ##############################
#ifdef VARIANT_IBUS
/* CONTROL VIA RC REMOTE WITH FLYSKY IBUS PROTOCOL // 通过FLYSKY IBUS协议遥控器控制
* Connected to Right sensor board cable. Channel 1: steering, Channel 2: speed. // 连接到右侧传感器板线缆。通道1：转向，通道2：速度
*/
  #define CONTROL_IBUS                    // use IBUS as input. Number indicates priority for dual-input. // 使用IBUS作为输入。数字表示双输入中的优先级。
  #define IBUS_NUM_CHANNELS       14      // total number of IBUS channels to receive, even if they are not used. // 要接收的IBUS通道总数，即使未使用
  #define IBUS_LENGTH             0x20
  #define IBUS_COMMAND            0x40
  #define USART3_BAUD             115200

  // #define DUAL_INPUTS                     // ADC*(Primary) + iBUS(Auxiliary). Uncomment this to use Dual-inputs // ADC*(主) + iBUS(辅)。取消注释以使用双输入
  #ifdef DUAL_INPUTS
    #define FLASH_WRITE_KEY       0x1106  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_ADC           0       // use ADC as input. Number indicates priority for dual-input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2! // 使用ADC作为输入。数字表示双输入中的优先级。禁用CONTROL_SERIAL_USART2、FEEDBACK_SERIAL_USART2、DEBUG_SERIAL_USART2！
    #define CONTROL_SERIAL_USART3 1       // use RC iBUS input on the RIGHT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3! // 在右侧线缆上使用RC iBUS输入。数字表示双输入中的优先级。禁用DEBUG_SERIAL_USART3！
    #define FEEDBACK_SERIAL_USART3        // right sensor board cable, disable if ADC or PPM is used! // 右侧传感器板线缆，如果使用ADC或PPM则禁用！
    #define PRI_INPUT1            3,     0, 0, 4095, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3,     0, 0, 4095, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT1            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define AUX_INPUT2            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #else
    #define FLASH_WRITE_KEY       0x1006  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
    #define CONTROL_SERIAL_USART3 0       // use RC iBUS input on the RIGHT cable, disable if ADC or PPM is used! // 在右侧线缆上使用RC iBUS输入，如果使用ADC或PPM则禁用！
    #define FEEDBACK_SERIAL_USART3        // right sensor board cable, disable if ADC or PPM is used! // 右侧传感器板线缆，如果使用ADC或PPM则禁用！
    #define PRI_INPUT1            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
    #define PRI_INPUT2            3, -1000, 0, 1000, 0  // TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section
  #endif

  // #define TANK_STEERING                // use for tank steering, each input controls each wheel // 用于坦克式转向，每个输入控制每个轮子 

  #if defined(CONTROL_SERIAL_USART3) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART2           // left sensor cable debug // 左侧传感器线缆调试
  #elif defined(DEBUG_SERIAL_USART2) && !defined(DUAL_INPUTS)
    #define DEBUG_SERIAL_USART3           // right sensor cable debug // 右侧传感器线缆调试
  #endif
#endif
// ############################# END OF VARIANT_IBUS SETTINGS (IBUS变体设置结束) ############################



// ############################ VARIANT_HOVERCAR SETTINGS (卡丁车变体设置) ############################
#ifdef VARIANT_HOVERCAR
  #define FLASH_WRITE_KEY         0x1107  // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
  #undef  CTRL_MOD_REQ
  #define CTRL_MOD_REQ            TRQ_MODE  // HOVERCAR works best in TORQUE Mode. // 卡丁车在扭矩模式下效果最佳。松开油门自由滑行，刹车和电子刹车提供动能回收。
  #define CONTROL_ADC             0         // use ADC as input. Disable CONTROL_SERIAL_USART2, FEEDBACK_SERIAL_USART2, DEBUG_SERIAL_USART2! // 使用ADC作为输入。禁用CONTROL_SERIAL_USART2、FEEDBACK_SERIAL_USART2、DEBUG_SERIAL_USART2！
  #define SUPPORT_BUTTONS_RIGHT             // use right sensor board cable for button inputs (PB10=Button1, PB11=Button2). Disable SIDEBOARD_SERIAL_USART3! // 使用右侧传感器板线缆作为按钮输入（PB10=按钮1，PB11=按钮2）。禁用SIDEBOARD_SERIAL_USART3！

  #define PRI_INPUT1              1,  0, 0, 4095, 0    // Pedal Brake (PA2)  TYPE=1 Normal Pot, full range // 刹车踏板（PA2），类型=1普通电位器，全范围
  #define PRI_INPUT2              1,  0, 0, 4095, 0    // Pedal Accel (PA3)  TYPE=1 Normal Pot, full range // 油门踏板（PA3），类型=1普通电位器，全范围

  // #define DEBUG_SERIAL_USART2               // left sensor board cable debug // 左侧传感器板线缆调试（与ADC冲突，已禁用）

  #define SPEED_COEFFICIENT       16384     // 1.0f
  #define STEER_COEFFICIENT       8192      // 0.5f Only active in Sideboard input // 仅在侧板输入中激活
  // #define ADC_ALTERNATE_CONNECT             // use to swap ADC inputs // 用于交换ADC输入
  // #define INVERT_R_DIRECTION                // Invert rotation of right motor // 反转右侧电机旋转方向
  // #define INVERT_L_DIRECTION                // Invert rotation of left motor // 反转左侧电机旋转方向
  // #define DEBUG_SERIAL_USART3               // right sensor board cable, disable if I2C (nunchuk or lcd) is used! // 右侧传感器板线缆，如果使用I2C（nunchuk或lcd）则禁用！

  // Extra functionality // 额外功能
  #define CRUISE_CONTROL_SUPPORT            // [-] Flag to enable Cruise Control support. Activation by throttle double-tap, deactivation by brake pedal press. // 启用定速巡航支持。双击油门激活，踩刹车取消。
  #define STANDSTILL_HOLD_ENABLE            // 到达停止状态时保持位置的标志。仅适用于电压或扭矩模式。
  #define ELECTRIC_BRAKE_ENABLE             // 启用电子制动（动能回收）。松开油门时电机发电给电池充电，产生轻微阻力。
  #define ELECTRIC_BRAKE_MAX    50          // (0, 500) Maximum electric brake to be applied when input torque request is 0 (pedal fully released). 50 = gentle regen // 动能回收强度。值越大回收越强，松开油门时的阻力也越大。
  #define ELECTRIC_BRAKE_THRES  120         // (0, 500) Threshold below which the electric brake starts engaging. // 电子制动开始介入的阈值（低于此值开始介入）
  #define BRAKE_REGEN_PERCENT   80          // (0-100) Brake pedal max regen strength in percent. 80 = strong enough to stop without mechanical brakes // 刹车踏板最大动能回收百分比。80 = 足以完全刹停（无机械刹车）

  #define MULTI_MODE_DRIVE                  // This option enables driving modes cycled via PB10 button (see main.c for mode switching logic) // 此选项启用通过PB10按钮循环切换驾驶模式（模式切换逻辑见main.c）
  #ifdef MULTI_MODE_DRIVE
      // MODE 1 - Slow (新手模式 - 慢速，≈ 8.6 km/h)
      #define MULTI_MODE_DRIVE_M1_MAX   400
      #define MULTI_MODE_DRIVE_M1_RATE  250
      #define MULTI_MODE_M1_I_MOT_MAX   8
      #define MULTI_MODE_M1_N_MOT_MAX   180

      // MODE 2 - Medium (中级模式 - 中速，≈ 21.5 km/h)
      #define MULTI_MODE_DRIVE_M2_MAX   700
      #define MULTI_MODE_DRIVE_M2_RATE  350
      #define MULTI_MODE_M2_I_MOT_MAX   12
      #define MULTI_MODE_M2_N_MOT_MAX   450

      // MODE 3 - Fast (高级模式 - 快速)
      #define MULTI_MODE_DRIVE_M3_MAX   1000
      #define MULTI_MODE_DRIVE_M3_RATE  450
      #define MULTI_MODE_M3_I_MOT_MAX   I_MOT_MAX
      #define MULTI_MODE_M3_N_MOT_MAX   N_MOT_MAX

      // MODE 4 - Turbo (极速模式) - 注释掉，防止电流过大烧毁控制板
      // #define MULTI_MODE_DRIVE_M4_MAX   1500
      // #define MULTI_MODE_DRIVE_M4_RATE  600
      // #define MULTI_MODE_M4_I_MOT_MAX   I_MOT_MAX
      // #define MULTI_MODE_M4_N_MOT_MAX   2000
  #endif

#endif

// Multiple tap detection: default DOUBLE Tap on Brake pedal (4 pulses) // 多次点击检测：默认为刹车踏板双击（4个脉冲）
#define MULTIPLE_TAP_NR           2 * 2       // [-] Define tap number: MULTIPLE_TAP_NR = number_of_taps * 2, number_of_taps = 1 (for single taping), 2 (for double tapping), 3 (for triple tapping), etc... // 定义点击次数：MULTIPLE_TAP_NR = 点击次数 * 2，点击次数 = 1（单击）、2（双击）、3（三击）等
#define MULTIPLE_TAP_HI           600         // [-] Multiple tap detection High hysteresis threshold // 多次点击检测高滞后阈值
#define MULTIPLE_TAP_LO           200         // [-] Multiple tap detection Low hysteresis threshold // 多次点击检测低滞后阈值
#define MULTIPLE_TAP_TIMEOUT      2000        // [ms] Multiple tap detection Timeout period. The taps need to happen within this time window to be accepted. // 多次点击检测超时时间。点击需要在此时间窗口内发生才会被接受。
// ######################## END OF VARIANT_HOVERCAR SETTINGS (卡丁车变体设置结束) #########################



// ############################ VARIANT_HOVERBOARD SETTINGS (平衡车变体设置) ############################
// Communication:         [DONE] // 通信：[已完成]
// Balancing controller:  [TODO] // 平衡控制器：[待办]
#ifdef VARIANT_HOVERBOARD
  #define FLASH_WRITE_KEY     0x1008          // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
  #define SIDEBOARD_SERIAL_USART2 1           // left sensor board cable. Number indicates priority for dual-input. Disable if ADC or PPM is used! // 左侧传感器板线缆。数字表示双输入中的优先级。如果使用ADC或PPM则禁用！
  #define FEEDBACK_SERIAL_USART2
  #define SIDEBOARD_SERIAL_USART3 0           // right sensor board cable. Number indicates priority for dual-input. Disable if I2C (nunchuk or lcd) is used! // 右侧传感器板线缆。数字表示双输入中的优先级。如果使用I2C（nunchuk或lcd）则禁用！
  #define FEEDBACK_SERIAL_USART3

  // If an iBUS RC receiver is connected to either Left Sideboard (AUX_INPUT) or Right Sideboard (PRI_INPUT) // 如果iBUS RC接收器连接到左侧板（AUX_INPUT）或右侧板（PRI_INPUT）
  // PRIMARY INPUT:          TYPE, MIN, MID, MAX, DEADBAND /* TYPE: 0:Disabled, 1:Normal Pot, 2:Middle Resting Pot, 3:Auto-detect */ // 主输入：类型、最小值、中点、最大值、死区 /* 类型：0：禁用，1：普通电位器，2：中位回位电位器，3：自动检测 */
  #define PRI_INPUT1          3, -1000, 0, 1000, 0  // Priority Sideboard can be used to send commands via an iBUS Receiver connected to the sideboard // 优先侧板可通过连接到侧板的iBUS接收器发送命令
  #define PRI_INPUT2          3, -1000, 0, 1000, 0  // Priority Sideboard can be used to send commands via an iBUS Receiver connected to the sideboard
  #define AUX_INPUT1          3, -1000, 0, 1000, 0  // not used // 未使用
  #define AUX_INPUT2          3, -1000, 0, 1000, 0  // not used // 未使用
#endif
// ######################## END OF VARIANT_HOVERBOARD SETTINGS (平衡车变体设置结束) #########################



// ################################# VARIANT_TRANSPOTTER SETTINGS (TRANSPOTTER变体设置) ############################
//TODO ADD VALIDATION // 待办：添加验证
#ifdef VARIANT_TRANSPOTTER
  #define FLASH_WRITE_KEY     0x1009    // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
  #define CONTROL_GAMETRAK
  #define SUPPORT_LCD
  // #define SUPPORT_NUNCHUK
  #define GAMETRAK_CONNECTION_NORMAL    // for normal wiring according to the wiki instructions // 按照维基说明的标准接线
  // #define GAMETRAK_CONNECTION_ALTERNATE // use this define instead if you messed up the gametrak ADC wiring (steering is speed, and length of the wire is steering) // 如果接错了gametrak ADC线（转向变成了速度，线的长度变成了转向），改用此定义
  #define ROT_P               1.2       // P coefficient for the direction controller. Positive / Negative values to invert gametrak steering direction. // 方向控制器的P系数。正值/负值用于反转gametrak转向方向
  // during nunchuk control (only relevant when activated) // 在nunchuk控制期间（仅在激活时相关）
  #define SPEED_COEFFICIENT   14746     // 0.9f - higher value == stronger. 0.0 to ~2.0? // 较高的值 == 强度更大。0.0到约2.0？
  #define STEER_COEFFICIENT   8192      // 0.5f - higher value == stronger. if you do not want any steering, set it to 0.0; 0.0 to 1.0 // 较高的值 == 强度更大。如果不需要转向，设为0.0；0.0到1.0
  #define INVERT_R_DIRECTION            // Invert right motor // 反转右侧电机
  #define INVERT_L_DIRECTION            // Invert left motor // 反转左侧电机
  #define PRI_INPUT1          2, -1000, 0, 1000, 0  // dummy input, TRANSPOTTER does not use input limitations // 虚拟输入，TRANSPOTTER不使用输入限制
  #define PRI_INPUT2          2, -1000, 0, 1000, 0  // dummy input, TRANSPOTTER does not use input limitations
#endif
// ############################# END OF VARIANT_TRANSPOTTER SETTINGS (TRANSPOTTER变体设置结束) ########################


// ################################# VARIANT_SKATEBOARD SETTINGS (滑板变体设置) ##############################
#ifdef VARIANT_SKATEBOARD
/* ###### CONTROL VIA RC REMOTE ###### // 通过遥控器控制
 * right sensor board cable. Connect PB10 to channel 1 and PB11 to channel 2 on receiver. // 右侧传感器板线缆。将PB10连接到接收器的通道1，PB11连接到通道2。
 * Channel 1: steering, Channel 2: speed. // 通道1：转向，通道2：速度
*/
  #define FLASH_WRITE_KEY     0x1010    // Flash memory writing key. Change this key to ignore the input calibrations from the flash memory and use the ones in config.h
  #undef  CTRL_MOD_REQ
  #define CTRL_MOD_REQ        TRQ_MODE  // SKATEBOARD works best in TORQUE Mode // 滑板在扭矩模式下效果最佳
  // #define CONTROL_PWM_LEFT    0         // use RC PWM as input on the LEFT cable. Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART2! // 在左侧线缆上使用RC PWM作为输入。数字表示双输入中的优先级。禁用DEBUG_SERIAL_USART2！
  #define CONTROL_PWM_RIGHT   0         // use RC PWM as input on the RIGHT cable.  Number indicates priority for dual-input. Disable DEBUG_SERIAL_USART3! // 在右侧线缆上使用RC PWM作为输入。数字表示双输入中的优先级。禁用DEBUG_SERIAL_USART3！

  #define PRI_INPUT1          0, -1000, 0, 1000,   0    // Disabled. TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section // 已禁用。类型、最小值、中点、最大值、死区。参见输入格式部分
  #define PRI_INPUT2          2,  -800, 0,  700, 100    // Active.   TYPE, MIN, MID, MAX, DEADBAND. See INPUT FORMAT section // 已激活。类型、最小值、中点、最大值、死区。参见输入格式部分
  #define INPUT_BRK           -400      // (-1000 - 0) Change this value to adjust the braking amount // 更改此值以调整制动力度

  #define FILTER              6553      // 0.1f [-] fixdt(0,16,16) lower value == softer filter [0, 65535] = [0.0 - 1.0]. // 较低的值 == 较柔和的滤波
  #define SPEED_COEFFICIENT   16384     // 1.0f [-] fixdt(1,16,14) higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14 // 较高的值 == 强度更大
  #define STEER_COEFFICIENT   0         // 1.0f [-] fixdt(1,16,14) higher value == stronger. [0, 65535] = [-2.0 - 2.0]. In this case 16384 = 1.0 * 2^14. If you do not want any steering, set it to 0. // 较高的值 == 强度更大。如果不需要转向，设为0。
  #define INVERT_R_DIRECTION
  #define INVERT_L_DIRECTION
  // #define SUPPORT_BUTTONS_LEFT       // use left sensor board cable for button inputs.  Disable DEBUG_SERIAL_USART2! // 使用左侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART2！
  // #define SUPPORT_BUTTONS_RIGHT      // use right sensor board cable for button inputs. Disable DEBUG_SERIAL_USART3! // 使用右侧传感器板线缆作为按钮输入。禁用DEBUG_SERIAL_USART3！
  #define STANDSTILL_HOLD_ENABLE     // 驻车功能，到达停止状态时保持位置的标志。仅适用于电压或扭矩模式。

  #ifdef CONTROL_PWM_RIGHT
    #define DEBUG_SERIAL_USART2         // left sensor cable debug // 左侧传感器线缆调试
  #else
    #define DEBUG_SERIAL_USART3         // right sensor cable debug // 右侧传感器线缆调试
  #endif
#endif
// ############################# END OF VARIANT_SKATEBOARD SETTINGS (滑板变体设置结束) ############################



// ########################### UART SETIINGS (UART设置) ############################
#if defined(FEEDBACK_SERIAL_USART2) || defined(CONTROL_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || \
    defined(FEEDBACK_SERIAL_USART3) || defined(CONTROL_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3)
  #define SERIAL_START_FRAME      0xABCD                  // [-] Start frame definition for serial commands // 串口命令起始帧定义
  #define SERIAL_BUFFER_SIZE      64                      // [bytes] Size of Serial Rx buffer. Make sure it is always larger than the structure size // 串口接收缓冲区大小（字节）。确保始终大于结构体大小
  #define SERIAL_TIMEOUT          160                     // [-] Serial timeout duration for the received data. 160 ~= 0.8 sec. Calculation: 0.8 sec / 0.005 sec // 接收数据的串口超时时间。160 ≈ 0.8秒。计算：0.8秒 / 0.005秒
#endif
#if defined(FEEDBACK_SERIAL_USART2) || defined(CONTROL_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2)
  #ifndef USART2_BAUD
    #define USART2_BAUD           115200                  // UART2 baud rate (long wired cable) // UART2波特率（长线缆）
  #endif
  #define USART2_WORDLENGTH       UART_WORDLENGTH_8B      // UART_WORDLENGTH_8B or UART_WORDLENGTH_9B // UART_WORDLENGTH_8B或UART_WORDLENGTH_9B
#endif
#if defined(FEEDBACK_SERIAL_USART3) || defined(CONTROL_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3)
  #ifndef USART3_BAUD
    #define USART3_BAUD           115200                  // UART3 baud rate (short wired cable) // UART3波特率（短线缆）
  #endif
  #define USART3_WORDLENGTH       UART_WORDLENGTH_8B      // UART_WORDLENGTH_8B or UART_WORDLENGTH_9B
#endif
// ########################### UART SETIINGS (UART设置结束) ############################



// ############################### APPLY DEFAULT SETTINGS (应用默认设置) ###############################
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
// ########################### END OF APPLY DEFAULT SETTING (应用默认设置结束) ############################



// ############################### VALIDATE SETTINGS (验证设置) ###############################
#if !defined(VARIANT_ADC) && !defined(VARIANT_USART) && !defined(VARIANT_NUNCHUK) && !defined(VARIANT_PPM) && !defined(VARIANT_PWM) && \
    !defined(VARIANT_IBUS) && !defined(VARIANT_HOVERCAR) && !defined(VARIANT_HOVERBOARD) && !defined(VARIANT_TRANSPOTTER) && !defined(VARIANT_SKATEBOARD)
  #error Variant not defined! Please check platformio.ini or Inc/config.h for available variants. // 错误：变体未定义！请检查platformio.ini或Inc/config.h中的可用变体
#endif


// General checks // 常规检查
#if defined(CONTROL_SERIAL_USART2) && defined(SIDEBOARD_SERIAL_USART2)
  #error CONTROL_SERIAL_USART2 and SIDEBOARD_SERIAL_USART2 not allowed, choose one. // 错误：CONTROL_SERIAL_USART2和SIDEBOARD_SERIAL_USART2不允许同时存在，请选择一个
#endif

#if defined(CONTROL_SERIAL_USART3) && defined(SIDEBOARD_SERIAL_USART3)
  #error CONTROL_SERIAL_USART3 and SIDEBOARD_SERIAL_USART3 not allowed, choose one. // 错误：CONTROL_SERIAL_USART3和SIDEBOARD_SERIAL_USART3不允许同时存在，请选择一个
#endif

#if defined(DEBUG_SERIAL_USART2) && defined(FEEDBACK_SERIAL_USART2)
  #error DEBUG_SERIAL_USART2 and FEEDBACK_SERIAL_USART2 not allowed, choose one. // 错误：DEBUG_SERIAL_USART2和FEEDBACK_SERIAL_USART2不允许同时存在，请选择一个
#endif

#if defined(DEBUG_SERIAL_USART3) && defined(FEEDBACK_SERIAL_USART3)
  #error DEBUG_SERIAL_USART3 and FEEDBACK_SERIAL_USART3 not allowed, choose one. // 错误：DEBUG_SERIAL_USART3和FEEDBACK_SERIAL_USART3不允许同时存在，请选择一个
#endif

#if defined(DEBUG_SERIAL_USART2) && defined(DEBUG_SERIAL_USART3)
  #error DEBUG_SERIAL_USART2 and DEBUG_SERIAL_USART3 not allowed, choose one. // 错误：DEBUG_SERIAL_USART2和DEBUG_SERIAL_USART3不允许同时存在，请选择一个
#endif

#if defined(CONTROL_PPM_LEFT) && defined(CONTROL_PPM_RIGHT)
  #error CONTROL_PPM_LEFT and CONTROL_PPM_RIGHT not allowed, choose one. // 错误：CONTROL_PPM_LEFT和CONTROL_PPM_RIGHT不允许同时存在，请选择一个
#endif

#if defined(CONTROL_PWM_LEFT) && defined(CONTROL_PWM_RIGHT)
  #error CONTROL_PWM_LEFT and CONTROL_PWM_RIGHT not allowed, choose one. // 错误：CONTROL_PWM_LEFT和CONTROL_PWM_RIGHT不允许同时存在，请选择一个
#endif

#if defined(SUPPORT_BUTTONS_LEFT) && defined(SUPPORT_BUTTONS_RIGHT)
  #error SUPPORT_BUTTONS_LEFT and SUPPORT_BUTTONS_RIGHT not allowed, choose one. // 错误：SUPPORT_BUTTONS_LEFT和SUPPORT_BUTTONS_RIGHT不允许同时存在，请选择一个
#endif


// LEFT cable checks // 左侧线缆检查
#if defined(CONTROL_ADC) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error CONTROL_ADC and SERIAL_USART2 not allowed. It is on the same cable. // 错误：CONTROL_ADC和SERIAL_USART2不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_PPM_LEFT) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error CONTROL_PPM_LEFT and SERIAL_USART2 not allowed. It is on the same cable. // 错误：CONTROL_PPM_LEFT和SERIAL_USART2不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_PWM_LEFT) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error CONTROL_PWM_LEFT and SERIAL_USART2 not allowed. It is on the same cable. // 错误：CONTROL_PWM_LEFT和SERIAL_USART2不允许，它们在同一条线缆上
#endif

#if defined(SUPPORT_BUTTONS_LEFT) && (defined(CONTROL_SERIAL_USART2) || defined(SIDEBOARD_SERIAL_USART2) || defined(FEEDBACK_SERIAL_USART2) || defined(DEBUG_SERIAL_USART2))
  #error SUPPORT_BUTTONS_LEFT and SERIAL_USART2 not allowed. It is on the same cable. // 错误：SUPPORT_BUTTONS_LEFT和SERIAL_USART2不允许，它们在同一条线缆上
#endif

#if defined(SUPPORT_BUTTONS_LEFT) && (defined(CONTROL_ADC) || defined(CONTROL_PPM_LEFT) || defined(CONTROL_PWM_LEFT))
  #error SUPPORT_BUTTONS_LEFT and (CONTROL_ADC or CONTROL_PPM_LEFT or CONTROL_PWM_LEFT) not allowed. It is on the same cable. // 错误：SUPPORT_BUTTONS_LEFT和（CONTROL_ADC或CONTROL_PPM_LEFT或CONTROL_PWM_LEFT）不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_ADC) && (defined(CONTROL_PPM_LEFT) || defined(CONTROL_PWM_LEFT))
  #error CONTROL_ADC and (CONTROL_PPM_LEFT or CONTROL_PWM_LEFT) not allowed. It is on the same cable. // 错误：CONTROL_ADC和（CONTROL_PPM_LEFT或CONTROL_PWM_LEFT）不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_PPM_LEFT) && defined(CONTROL_PWM_LEFT)
  #error CONTROL_PPM_LEFT and CONTROL_PWM_LEFT not allowed. It is on the same cable. // 错误：CONTROL_PPM_LEFT和CONTROL_PWM_LEFT不允许，它们在同一条线缆上
#endif


// RIGHT cable checks // 右侧线缆检查
#if defined(CONTROL_NUNCHUK) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error CONTROL_NUNCHUK and SERIAL_USART3 not allowed. It is on the same cable. // 错误：CONTROL_NUNCHUK和SERIAL_USART3不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_PPM_RIGHT) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error CONTROL_PPM_RIGHT and SERIAL_USART3 not allowed. It is on the same cable. // 错误：CONTROL_PPM_RIGHT和SERIAL_USART3不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_PWM_RIGHT) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error CONTROL_PWM_RIGHT and SERIAL_USART3 not allowed. It is on the same cable. // 错误：CONTROL_PWM_RIGHT和SERIAL_USART3不允许，它们在同一条线缆上
#endif

#if defined(DEBUG_I2C_LCD) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error DEBUG_I2C_LCD and SERIAL_USART3 not allowed. It is on the same cable. // 错误：DEBUG_I2C_LCD和SERIAL_USART3不允许，它们在同一条线缆上
#endif

#if defined(SUPPORT_BUTTONS_RIGHT) && (defined(CONTROL_SERIAL_USART3) || defined(SIDEBOARD_SERIAL_USART3) || defined(FEEDBACK_SERIAL_USART3) || defined(DEBUG_SERIAL_USART3))
  #error SUPPORT_BUTTONS_RIGHT and SERIAL_USART3 not allowed. It is on the same cable. // 错误：SUPPORT_BUTTONS_RIGHT和SERIAL_USART3不允许，它们在同一条线缆上
#endif

#if defined(SUPPORT_BUTTONS_RIGHT) && (defined(CONTROL_NUNCHUK) || defined(CONTROL_PPM_RIGHT) || defined(CONTROL_PWM_RIGHT) || defined(DEBUG_I2C_LCD))
  #error SUPPORT_BUTTONS_RIGHT and (CONTROL_NUNCHUK or CONTROL_PPM_RIGHT or CONTROL_PWM_RIGHT or DEBUG_I2C_LCD) not allowed. It is on the same cable. // 错误：SUPPORT_BUTTONS_RIGHT和（CONTROL_NUNCHUK或CONTROL_PPM_RIGHT或CONTROL_PWM_RIGHT或DEBUG_I2C_LCD）不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_NUNCHUK) && (defined(CONTROL_PPM_RIGHT) || defined(CONTROL_PWM_RIGHT) || defined(DEBUG_I2C_LCD))
  #error CONTROL_NUNCHUK and (CONTROL_PPM_RIGHT or CONTROL_PWM_RIGHT or DEBUG_I2C_LCD) not allowed. It is on the same cable. // 错误：CONTROL_NUNCHUK和（CONTROL_PPM_RIGHT或CONTROL_PWM_RIGHT或DEBUG_I2C_LCD）不允许，它们在同一条线缆上
#endif

#if defined(DEBUG_I2C_LCD) && (defined(CONTROL_PPM_RIGHT) || defined(CONTROL_PWM_RIGHT))
  #error DEBUG_I2C_LCD and (CONTROL_PPM_RIGHT or CONTROL_PWM_RIGHT) not allowed. It is on the same cable. // 错误：DEBUG_I2C_LCD和（CONTROL_PPM_RIGHT或CONTROL_PWM_RIGHT）不允许，它们在同一条线缆上
#endif

#if defined(CONTROL_PPM_RIGHT) && defined(CONTROL_PWM_RIGHT)
  #error CONTROL_PPM_RIGHT and CONTROL_PWM_RIGHT not allowed. It is on the same cable. // 错误：CONTROL_PPM_RIGHT和CONTROL_PWM_RIGHT不允许，它们在同一条线缆上
#endif


// Functional checks // 功能检查
#if (defined(CONTROL_PPM_LEFT) || defined(CONTROL_PPM_RIGHT)) && !defined(PPM_NUM_CHANNELS)
  #error Total number of PPM channels needs to be set // 错误：需要设置PPM通道总数
#endif
// ############################# END OF VALIDATE SETTINGS (验证设置结束) ############################

#endif
