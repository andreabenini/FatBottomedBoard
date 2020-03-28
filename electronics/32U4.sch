EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ProMicro:ProMicro U1
U 1 1 5E755F83
P 3300 3100
F 0 "U1" H 3300 4137 60  0000 C CNN
F 1 "Pro Micro 32U4 USB" H 3300 4031 60  0000 C CNN
F 2 "" H 3400 2050 60  0000 C CNN
F 3 "" H 3400 2050 60  0000 C CNN
	1    3300 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E757802
P 4550 3250
F 0 "R?" V 4343 3250 50  0001 C CNN
F 1 "330" V 4550 3250 50  0000 C CNN
F 2 "" V 4480 3250 50  0001 C CNN
F 3 "~" H 4550 3250 50  0001 C CNN
	1    4550 3250
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E758D3E
P 4550 3350
F 0 "R?" V 4343 3350 50  0001 C CNN
F 1 "1K" V 4550 3350 50  0000 C CNN
F 2 "" V 4480 3350 50  0001 C CNN
F 3 "~" H 4550 3350 50  0001 C CNN
	1    4550 3350
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E758FB4
P 4550 3450
F 0 "R?" V 4343 3450 50  0001 C CNN
F 1 "1K" V 4550 3450 50  0000 C CNN
F 2 "" V 4480 3450 50  0001 C CNN
F 3 "~" H 4550 3450 50  0001 C CNN
	1    4550 3450
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E759510
P 4550 3550
F 0 "R?" V 4343 3550 50  0001 C CNN
F 1 "1K" V 4550 3550 50  0000 C CNN
F 2 "" V 4480 3550 50  0001 C CNN
F 3 "~" H 4550 3550 50  0001 C CNN
	1    4550 3550
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5E75982D
P 4550 3650
F 0 "R?" V 4343 3650 50  0001 C CNN
F 1 "1K" V 4550 3650 50  0000 C CNN
F 2 "" V 4480 3650 50  0001 C CNN
F 3 "~" H 4550 3650 50  0001 C CNN
	1    4550 3650
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic_MountingPin:Conn_01x07_MountingPin 1.8"
U 1 1 5E75A7AF
P 5500 3450
F 0 "1.8\"" H 6150 3450 50  0000 L CNN
F 1 "TFT LCD ST7735S" H 5950 3300 50  0000 L CNN
F 2 "" H 5500 3450 50  0001 C CNN
F 3 "~" H 5500 3450 50  0001 C CNN
	1    5500 3450
	1    0    0    -1  
$EndComp
$Comp
L Converter_DCDC:ITX2405SA D-SUN_PS1
U 1 1 5E7617A4
P 4550 4200
F 0 "D-SUN_PS1" H 4550 4567 50  0000 C CNN
F 1 "5v -> 3.3v" H 4550 4476 50  0000 C CNN
F 2 "Converter_DCDC:Converter_DCDC_XP_POWER-ITXxxxxSA_THT" H 3500 3950 50  0001 L CNN
F 3 "https://www.xppower.com/pdfs/SF_ITX.pdf" H 5600 3900 50  0001 L CNN
	1    4550 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2650 2400 2650
Wire Wire Line
	2400 2650 2400 4250
$Comp
L power:GNDREF GND
U 1 1 5E768202
P 2400 4250
F 0 "GND" H 2400 4050 50  0000 C CNN
F 1 "GNDREF" H 2400 4000 50  0001 C CNN
F 2 "" H 2400 4250 50  0001 C CNN
F 3 "" H 2400 4250 50  0001 C CNN
	1    2400 4250
	1    0    0    -1  
$EndComp
Connection ~ 2400 4250
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5E771D4E
P 1950 4250
F 0 "J1" H 1868 3925 50  0000 C CNN
F 1 "Input 5v" H 1868 4016 50  0000 C CNN
F 2 "" H 1950 4250 50  0001 C CNN
F 3 "~" H 1950 4250 50  0001 C CNN
	1    1950 4250
	-1   0    0    1   
$EndComp
Wire Wire Line
	2150 4250 2400 4250
Wire Wire Line
	2150 4150 2550 4150
Wire Wire Line
	4000 3150 4400 3150
Wire Wire Line
	4700 3250 5300 3250
Wire Wire Line
	5150 3150 5300 3150
Wire Wire Line
	4700 3350 5300 3350
Wire Wire Line
	4700 3450 5300 3450
Wire Wire Line
	2600 3350 2450 3350
Wire Wire Line
	2600 3450 2550 3450
Wire Wire Line
	2550 3450 2550 3650
Wire Wire Line
	4700 3550 5300 3550
Wire Wire Line
	4700 3650 5300 3650
Wire Wire Line
	2450 3350 2450 3550
Wire Notes Line style solid rgb(132, 0, 0)
	5550 2950 5550 4000
Wire Notes Line style solid rgb(132, 0, 0)
	5550 4000 6900 4000
Wire Notes Line style solid rgb(132, 0, 0)
	6900 4000 6900 2950
Wire Notes Line style solid rgb(132, 0, 0)
	6900 2950 5550 2950
Text Notes 5600 3750 0    51   ~ 0
LED\nSCK\nSDA\nA0\nRESET\nCS\nGND\nVCC
Wire Wire Line
	4400 3150 4400 3250
Wire Wire Line
	5250 3750 5300 3750
Wire Wire Line
	4000 3350 4400 3350
Wire Wire Line
	4000 3450 4400 3450
Wire Wire Line
	2450 3550 4400 3550
Wire Wire Line
	2550 3650 4400 3650
Wire Wire Line
	2400 4250 2550 4250
Wire Wire Line
	2550 4150 2550 4100
Wire Wire Line
	2550 4100 4150 4100
Wire Wire Line
	2550 4250 2550 4300
Wire Wire Line
	2550 4300 4150 4300
Wire Wire Line
	4150 4100 4150 2350
Wire Wire Line
	4150 2350 4000 2350
Connection ~ 4150 4100
Wire Wire Line
	4000 2650 5250 2650
Wire Wire Line
	5250 2650 5250 3750
Wire Wire Line
	5150 3150 5150 4100
Wire Wire Line
	5150 4100 4950 4100
Wire Wire Line
	4950 4300 5150 4300
Wire Wire Line
	5150 4300 5150 4450
Wire Wire Line
	5150 4450 4150 4450
Wire Wire Line
	4150 4450 4150 4300
Connection ~ 4150 4300
$Comp
L Device:Rotary_Encoder_Switch Control
U 1 1 5E7EB2C9
P 1300 2850
F 0 "Control" H 1300 2575 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 1300 3126 50  0001 C CNN
F 2 "" H 1150 3010 50  0001 C CNN
F 3 "~" H 1300 3125 50  0001 C CNN
	1    1300 2850
	-1   0    0    1   
$EndComp
Text Notes 1650 2950 0    57   ~ 0
CLK\nDT\nSW
Wire Wire Line
	1600 2750 2600 2750
Wire Wire Line
	1600 2850 2600 2850
Wire Wire Line
	1600 2950 2600 2950
Wire Wire Line
	1000 2750 800  2750
Wire Wire Line
	800  2500 1600 2500
Wire Wire Line
	1600 2500 1600 2650
Wire Wire Line
	1600 2650 2400 2650
Connection ~ 2400 2650
Wire Wire Line
	1000 2950 700  2950
Wire Wire Line
	700  2950 700  1900
Wire Wire Line
	700  1900 5250 1900
Wire Wire Line
	5250 1900 5250 2650
Connection ~ 5250 2650
Wire Wire Line
	800  2500 800  2750
Text Notes 7400 7500 0    50   ~ 0
Display Controller
Text Notes 7300 7250 0    50   ~ 0
1
Text Notes 7400 7250 0    50   ~ 0
1
Text Notes 7050 6950 0    50   ~ 0
AVR 32U4        Keyboard Controller\nLCD TFT Display\nRotary Encoders
Text Notes 1000 2950 2    57   ~ 0
GND\n\nVcc
$EndSCHEMATC
