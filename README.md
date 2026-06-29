# hoverboard-firmware-hack-FOC 卡丁车固件(VARIANT_HOVERCAR)

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

> **⚠️ 本主控固件需要配合扩展板固件一起使用：** [MY-hoverboard-sideboard-hack-STM](https://github.com/bombjinne/MY-hoverboard-sideboard-hack-STM)

> 本固件基于 [EFeru/hoverboard-firmware-hack-FOC](https://github.com/EFeru/hoverboard-firmware-hack-FOC) 修改，适配 **平衡车改卡丁车** 项目。原项目实现了基于 FOC（磁场定向控制）的平衡车主板固件。

---

## ⚙️ 硬件平台

| 项目 | 规格 |
|---|---|
| **主控芯片** | STM32F103RCT6 |
| **电池** | 36V 锂电（10串2并） |
| **电机** | 10寸蜘蛛轮 × 2，约 300W |
| **控制模式** | FOC 扭矩模式（TRQ_MODE） |

---

## 主板引脚说明图
<img width="3096" height="1599" alt="mainboard_pinout" src="https://github.com/user-attachments/assets/3f01622e-a0af-42f6-81f3-c17f5204e08e" />


### 左侧传感器板线缆（4-pin JST）

| 线色 | STM32引脚 | 本固件用途 | 原始功能 |
|---|---|---|---|
| 🔴 红 | **15V** | 不用，不可接大功率设备 | 15V 200mA max |
| 🔵 蓝 | **PA2** | 刹车踏板 ADC1 | TX / ADC1 / PWM1 |
| 🟢 绿 | **PA3** | 油门踏板 ADC2 | RX / ADC2 / PWM2 / PPM / iBUS |
| ⚫ 黑 | **GND** | 公共地 | GND |

### 右侧传感器板线缆（4-pin JST）

| 线色 | STM32引脚 | 本固件用途 | 原始功能 |
|---|---|---|---|
| 🔴 红 | **15V** | 不用，不可接大功率设备 | 15V 200mA max |
| 🔵 蓝 | **PB10** | 串口TX | TX / SCL / PWM1 |
| 🟢 绿 | **PB11** | 串口RX | RX / SDA / iBUS / PPM / PWM2 |
| ⚫ 黑 | **GND** | 公共地 | GND |

### SWD 调试接口（4-pin，PCB 焊盘，从上至下）

| 引脚 | 功能 | 最大电流 |
|---|---|---|
| **3.3V** | 目标供电 | 30mA max |
| **PA14 / SWCLK** | 时钟线 | - |
| **GND** | 地线 | - |
| **PA13 / SWDIO** | 数据线 | - |

### 主板其他引脚

| 功能 | 引脚 | 说明 |
|---|---|---|
| **电源按钮** | PA1 (Button) / PA5 (Latch) | 开关机 |
| **充电检测** | PA12 | 充电器检测 |
| **电池电压采样** | PC2 | 分压检测 |
| **左电机电流** | PA0 / PC3 | 相线 A / 相线 B |
| **右电机电流** | PC5 / PC4 | 相线 C / 相线 B |
| **DC母线电流** | PC0 / PC1 | 左/右电机 |
| **霍尔传感器左** | PB5 / PB6 / PB7 | U / V / W |
| **霍尔传感器右** | PC10 / PC11 / PC12 | U / V / W |

### ⚡ 供电说明（重要）

- 踏板从主板 **AMS1117-3.3V 稳压芯片** 的中间引脚（Vout）焊点取 3.3V 供电
- 踏板信号线（0-3.3V）直连 PA2/PA3，**无需分压**
- 音浪音箱、大灯等耗电设备不从主板取电，需从顶部电源入口取电，并视情况接入12V降压模块
- 霍尔传感器线缆红色提供 5V（最大 100mA），仅用于霍尔传感器


## 🎮 功能说明

| 功能 | 操作 | 反馈 |
|---|---|---|
| **档位切换** | 扩展板PC14 自复位按钮短接→GND | 蜂鸣提示：1声=M1慢速、2声=M2中速、3声=M3快速 |
| **前进/倒车** | 扩展板PA4 自锁钮子开关接通→GND | 仅静止时生效。倒车限速 M1（最慢档） |
| **加速** | 踩油门（PA3） | 线性加速，受当前档位限速 |
| **刹车** | 踩刹车（PA2） | 线性刹车，动能回收最大力度 80%（无机械刹车，完全靠电刹停） |
| **定速巡航** | 行驶中快速双击油门 | 蜂鸣 2 声，定速维持当前速度 |
| **取消定速巡航** | 轻踩刹车 | 自动取消巡航 |
| **动能回收** | 松开油门（不踩刹车） | 轻微回收发电（强度 50/500），几乎无阻力感 |
| **RF遥控锁车** | 扩展板接收433MHz遥控信号 | 锁车/解锁/M1/停车 |

### RF遥控命令

扩展板通过 USART2 将 RF 遥控命令发送给主板，使用 4 字节帧格式（`0xAA, cmd, 0x00, checksum`）：

| 命令 | 编码 | 主板动作 | 蜂鸣反馈 |
|---|---|---|---|
| **锁车** `RF_CMD_LOCK` | 0x01 | 禁用电机 + 锁定（油门无效） | 长鸣 3 声 |
| **解锁** `RF_CMD_UNLOCK` | 0x02 | 启用电机 + 解锁 | 短鸣 5+7 声 |
| **M1** `RF_CMD_MODE1` | 0x03 | 强制切换到 M1 档 | 短鸣 1 声 |
| **停车** `RF_CMD_STOP` | 0x04 | 禁用电机 | 长鸣 1 声 |
| **换挡** `RF_CMD_NEXT_MODE` | 0x05 | 循环 M1→M2→M3→M1 | 1/2/3 声短鸣 |
| **倒车开** `RF_CMD_REVERSE_ON` | 0x06 | 开启倒车（`backwardDrive=1`） | 短+长鸣 |
| **倒车关** `RF_CMD_REVERSE_OFF` | 0x07 | 关闭倒车（`backwardDrive=0`） | 长鸣 1 声 |

> RF遥控和扩展板物理按钮共用同一套命令协议，可同时使用。

### 档位速度对照

| 档位 | 蜂鸣 | 电机限速 | 电流限制 | 参考车速 |
|---|---|---|---|---|
| **M1 - 新手** | 1 声 | 180 RPM | 8 A | ≈ 8 km/h |
| **M2 - 中级** | 2 声 | 450 RPM | 12 A | ≈ 21 km/h |
| **M3 - 快速** | 3 声 | 1000 RPM | 15 A | ≈ 48 km/h |

> 实际速度取决于轮径和电池电压。M1/M2 适合儿童或狭小空间，M3 为全速模式。

---

## 踏板校准

首次烧录或更换踏板后，**必须执行一次校准**，否则电机不会使能。

### 校准步骤

1. **上电**，等待开机旋律响完（约3秒）
2. **长按电源键 > 5秒**，听到"滴"声后松手
3. 等待1秒，听到长"滴"声 → 进入校准模式
4. **反复将两个踏板踩到最大和最小位置**（20秒内多次来回）
5. **松开踏板到静止位置**
6. **短按电源键确认**（校准值自动保存到 Flash）
7. 重启后生效

### 校准原理

固件会自动检测踏板的 ADC 最小值、中间值和最大值，并将其保存到 Flash。校准后静止时踏板 cmd ≈ 0，电机才能使能。

### 重新校准

如需重新校准（例如更换踏板），再次执行上述步骤即可，新值会覆盖旧值。

---

## 固件烧录

### 环境要求
- [PlatformIO](https://platformio.org/) (推荐) 或 Keil uVision
- ST-Link 下载器（或 USB 串口 + bootloader）

### 编译烧录

```bash
# 打开项目目录
cd hoverboard-firmware-hack-FOC

# 编译并烧录
pio run -t upload
```

### PlatformIO 配置

`platformio.ini` 已默认启用 `VARIANT_HOVERCAR` 变体。如需切换其他变体，修改 `default_envs` 即可。

---

## 自定义配置

所有配置在 `Inc/config.h` 中（HOVERCAR 变体）：

### 电机参数

| 参数 | 默认值 | 说明 |
|---|---|---|
| `CTRL_TYP_SEL` | `FOC_CTRL` | 控制类型：FOC（磁场定向控制） |
| `CTRL_MOD_REQ` | `TRQ_MODE` | 控制模式：扭矩模式（松开油门自由滑行） |
| `I_MOT_MAX` | 15 A | 单电机最大相电流。**300W 电机不建议超过 15A**（300W/36V≈8.3A 额定，15A 已是 1.8 倍过载用于加速）|
| `I_DC_MAX` | 17 A | 直流母线总电流限制。建议保持 `I_DC_MAX = I_MOT_MAX + 2A` |
| `N_MOT_MAX` | 1000 RPM | 电机最大速度限制 |
| `FIELD_WEAK_ENA` | 0（关闭） | 弱磁/提前角，关闭可提高可靠性 |

### 动能回收与刹车

| 参数 | 默认值 | 说明 |
|---|---|---|
| `ELECTRIC_BRAKE_ENABLE` | 已启用 | 松开油门时电机发电，产生轻微阻力 |
| `ELECTRIC_BRAKE_MAX` | 50 | 动能回收强度（0-500），值越大松开油门时阻力越强 |
| `ELECTRIC_BRAKE_THRES` | 30 | 动能回收介入阈值 |
| `BRAKE_REGEN_PERCENT` | 80% | 刹车踏板最大回收力度（0-100）。80% 可完全刹停（无机械刹车）|
| `STANDSTILL_HOLD_ENABLE` | 已启用 | 坡道驻车，静止时保持位置不溜车 |

### 驾驶模式

| 参数 | M1（新手） | M2（中级） | M3（高级） |
|---|---|---|---|
| 最大转速 | 180 RPM | 450 RPM | 1000 RPM |
| 最大电流 | 8 A | 12 A | 15 A |
| 限速值 | 400 | 600 | 800 |
| 加速度 | 250 | 350 | 450 |
| 约计速度 | 8.6 km/h | 21.5 km/h | 48 km/h |
| 蜂鸣声数 | 1 声 | 2 声 | 3 声 |
| 开机默认 | ✅（默认启动） | ❌ | ❌ |

> 每次上电默认启动 M1（新手模式），可通过扩展板PC14按钮循环切换 M1 ↔ M2 ↔ M3。

### 控制输入

| 参数 | 默认值 | 说明 |
|---|---|---|
| `PRI_INPUT1` | `1, 0, 0, 4095, 0` | 刹车踏板（PA2），普通电位器类型，全 ADC 范围 |
| `PRI_INPUT2` | `1, 0, 0, 4095, 0` | 油门踏板（PA3），普通电位器类型，全 ADC 范围 |
| `CONTROL_ADC` | 0 | 使用 ADC 作为主输入 |
| `SUPPORT_BUTTONS_RIGHT` | 已禁用 | PB10/PB11 已改为 USART3 与扩展板通信，按钮功能不再使用 |
| `CRUISE_CONTROL_SUPPORT` | 已启用 | 油门双击激活定速巡航，踩刹车取消 |

### 电池

| 参数 | 默认值 | 说明 |
|---|---|---|
| `BAT_CELLS` | 10 | 串联电芯数（10S，36V 标称） |
| `BAT_LVL5` | 39.0 V | 绿色 LED（满电） |
| `BAT_LVL4` | 38.0 V | 黄色 LED |
| `BAT_LVL3` | 37.0 V | 黄色 LED 闪烁 |
| `BAT_LVL2` | 36.0 V | 红色 LED + 缓慢蜂鸣（已禁用） |
| `BAT_LVL1` | 35.0 V | 红色 LED 闪烁 + 快速蜂鸣（3.50 V/芯） |
| `BAT_DEAD` | 33.7 V | 欠压自动关机（3.37 V/芯） |

> 电压阈值为实际电压，自动根据 `BAT_CALIB_ADC`/`BAT_CALIB_REAL_VOLTAGE` 换算，无需手动校准。

### 其他

| 参数 | 默认值 | 说明 |
|---|---|---|
| `BUZZER_ENABLED` | 已启用 | 蜂鸣器 |
| `BEEPS_BACKWARD` | 1 | 倒车提示音 |
| `INACTIVITY_TIMEOUT` | 3 分钟 | 无人操作自动关机 |
| `BOARD_VARIANT` | 0 | 主板版本（0=默认，1=备用引脚映射）|
| `TEMP_WARNING_ENABLE` | 0（关闭） | 温度过高警告（需先校准温度传感器）|
| `TEMP_POWEROFF_ENABLE` | 0（关闭） | 温度过高自动关机（需先校准温度传感器）|

---

## ⚠️ 安全注意事项

1. **首次上电**：抬起车轮，确认电机旋转方向正确
2. **如果车轮反转**：在 `config.h` 中启用 `INVERT_R_DIRECTION` 或 `INVERT_L_DIRECTION`
3. **动能回收**：会产生轻微阻力，若拖拽感太强，减小 `ELECTRIC_BRAKE_MAX` 或禁用 `ELECTRIC_BRAKE_ENABLE`
4. **弱磁（Field Weakening）**：默认关闭，如需更高速度可启用 `FIELD_WEAK_ENA=1`，但注意功耗和热量会显著增加
5. **电池保护**：欠压自动关机（约 33.7V），请勿在关机后强行推车，以免 BMS 保护

---

## 📋 待实现功能（TODO）

以下功能已分析可行性，待后续开发：

### 1. 手机控制 + 数据查看（HC-05 / ESP8266）

| 项目 | 说明 |
|---|---|
| **可行性** | ✅ 高 |
| **方案** | USART1（PA9=TX, PA10=RX）完全空闲，固件已有完整的串口指令协议（`SerialCommand` 控制帧 + `SerialFeedback` 反馈帧 + `$GET/$SET/$WATCH` 文本协议），只需初始化 USART1 并路由数据即可 |
| **可查看数据** | 电池电压、电机速度、电机电流、主板温度、左右轮指令值 |
| **可控制功能** | 油门/方向指令、切换控制模式、修改参数（电流限制、速度限制等） |
| **硬件改动** | 需要在 MCU 的 PA9/PA10 引脚上焊接飞线（5-pin 侧边线缆未引出这两个引脚） |

### 2. 超声波急刹车（HC-SR04）

| 项目 | 说明 |
|---|---|
| **可行性** | ✅ 高 |
| **方案** | TIM4（完全空闲）+ PB8（Trigger）/ PB9（Echo 输入捕获），测距后低于阈值强制停机（`enable=0; pwml=pwmr=0`）|
| **硬件改动** | PB8/PB9 需焊接飞线；HC-SR04 Echo 输出 5V 需分压电阻（~3.3kΩ + 1.8kΩ）降至 3.3V |


### 3. ESP8266 网页端 OTA 固件刷入

| 项目 | 说明 |
|---|---|
| **可行性** | ⚠️ 可实现但较复杂 |
| **方案** | ESP8266（通过 USART1 连接 STM32）运行 Web 服务器，提供固件上传页面 → 通过 STM32 的 System Bootloader（USART1）或自定义 bootloader 写入固件 |
| **前置需求** | 需要完成上述 #1（ESP8266 接入 USART1）|
| **额外需求** | 需要实现 STM32 端 bootloader（引导程序），支持通过 UART 接收并烧录固件；或利用 STM32 内置的 System Memory Bootloader（需控制 BOOT0/BOOT1 引脚切换）|
| **硬件改动** | 同 #1（PA9/PA10 飞线），额外可能需要 BOOT0 引脚（PA5 或单独拉电阻）控制 |
| **工作量** | ~1-2 周（含 bootloader 开发 + ESP8266 Web 页面 + 测试）|
| **备注** | 如果只想要免拆机刷固件，更简单的方案是：在机壳上留一个 ST-Link 的 SWD 接口（PA13/PA14/SWIM 排针），插上即可烧录，无需拆机 |

---

## 原项目来源

- **原项目仓库**: [EFeru/hoverboard-firmware-hack-FOC](https://github.com/EFeru/hoverboard-firmware-hack-FOC)
- **原项目作者**: Emanuel FERU (aerdronix@gmail.com), Niklas Fauth, Rene Hopf, Nico Stute
- **开源协议**: [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0)

---

## 支持

如果你觉得这个项目有帮助，可以请我喝杯咖啡 ☕

<img width="400" height="500" alt="f4f1abd021209e73f794af94db1ec9db" src="https://github.com/user-attachments/assets/2c7a2516-6425-4a23-ab78-e2b9d30dcd29" />

