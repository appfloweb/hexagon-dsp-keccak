# Hexagon DSP-Keccak #

Android platform uses Hexagon DSP to accelerate KECCAK operation

KECCAK is a SHA-3 standard hash algorithm. Ethereum uses KECCAK-256-function in many places.

Qualcomm Hexagon Compute DSP (CDSP) is a hardware acceleration unit specially used for general -purpose computing on the Qualcomm platform. HEXAGON DSP's HVX supports SIMD instructions, the computing bit width is 1024bits.

This project uses assembly language programming and uses DSP's VLIW and SIMD features to accelerate KECCAK operations. (HVX version is v66)

In order to fully use the register and minimize the access to memory, each time 16 sets of data is performed at the same time KECCAK operations.

In order to reduce the context switch from the CPU to DSP, the function call each time is 16*400 sets of data for KECCAK operations, and the length of each group of data is fixed.

# Function description #

Each group of input data is 40 bytes, the output data length is 64 bytes, a total of 16*400 groups:

    keccak512_40_64

Each group of input data length is 40 bytes, and the output data length is 96 bytes (valid data 64 bytes, and the remaining 32 bytes are supplemented by 0), a total of 16*400 groups:

    keccak512_40_96

Each group of input data is 64 bytes, the output data length is 64 bytes, a total of 16*400 groups:
    
    keccak512_64_64

Each group of input data is 96 bytes, the output data length is 32 bytes, a total of 16*400 groups:

    keccak256_96_32

# Run directly #

1. Connect to the phone, push dsp/hexagon_release_toolv84_v66/ship/libcalculator_skel.so to the mobile phone directory

	    
	    adb shell
	    mkdir /data/local/tmp/dsp
	    adb push hexagon_Release_toolv84_v66\ship\libcalculator_skel.so /data/local/tmp/dsp


2. Install and run app/release/app-release.apk

![Screenshot](/png/Screenshot.png)

# Compile and install #


1. Official website download and install **Qualcomm Hexagon SDK 4.3.0.0**
2. Command line run **setup\_sdk\_env.cmd**
3. Command line switch to the **dsp** directory, run

		make hexagon BUILD=Release DSP_ARCH=v66

4. Connect to the mobile phone, the **libcalculator_skel.so** file push to the mobile phone directory
	    
	    adb shell
	    mkdir /data/local/tmp/dsp
	    adb push hexagon_Release_toolv84_v66\ship\libcalculator_skel.so /data/local/tmp/dsp


5. Modify the project **NDK LOCATION**:Hexagon_SDK\4.3.0.0\tools\android-ndk-r19c

6. Modify **CMakeLists.txt** file **HEXAGON\_SDK\_ROOT** path

7. Compile running app

# Hexagon DSP-Keccak #

Android平台使用Hexagon DSP加速Keccak运算

Keccak是一种被选定为SHA-3标准的单向散列函数算法。以太坊在许多地方使用_Keccak-256_加密哈希函数。

Qualcomm Hexagon Compute DSP (cDSP)是高通平台上专门用来做通用计算的硬件加速单元。Hexagon DSP的HVX支持SIMD指令，计算位宽为1024bits。


本项目使用汇编语言编程，利用DSP的VLIW与SIMD特性来加速Keccak运算。（HVX版本为V66）

为充分使用寄存器，尽量减少对内存的访问，每次16组数据同时进行keccak运算，

为减少cpu到dsp的上下文切换，每次函数调用会为16*400组数据进行keccak运算，每组数据的长度为固定值。

# 函数说明 #
每组输入数据长度40字节，输出数据长度64字节，总共16*400组：

    keccak512_40_64

每组输入数据长度40字节，输出数据长度96字节（有效数据64字节，剩余32字节补0），总共16*400组：

    keccak512_40_96

每组输入数据长度64字节，输出数据长度64字节，总共16*400组：

    keccak512_64_64

每组输入数据长度96字节，输出数据长度32字节，总共16*400组：

    keccak256_96_32


# 直接运行 #

1.连接手机，将dsp/hexagon_Release_toolv84_v66/ship/libcalculator_skel.so文件push到手机

    adb shell
    mkdir /data/local/tmp/dsp
    adb push hexagon_Release_toolv84_v66\ship\libcalculator_skel.so /data/local/tmp/dsp

2.安装运行 app/release/app-release.apk

![Screenshot](/png/Screenshot.png)


# 编译安装 #

1.官网下载安装 **Qualcomm Hexagon SDK 4.3.0.0**

2.命令行运行**setup\_sdk\_env.cmd**

3.命令行切换到**dsp**目录，运行

    make hexagon BUILD=Release DSP_ARCH=v66

4.连接手机，将生成的libcalculator_skel.so文件push到手机

    adb shell
    mkdir /data/local/tmp/dsp
    adb push hexagon_Release_toolv84_v66\ship\libcalculator_skel.so /data/local/tmp/dsp

5.修改项目**NDK location**：Hexagon_SDK\4.3.0.0\tools\android-ndk-r19c

6.修改**CMakeLists.txt**文件**HEXAGON\_SDK\_ROOT**路径

7.编译运行app
