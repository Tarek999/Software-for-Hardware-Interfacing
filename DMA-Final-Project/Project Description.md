# Project name: 
A complete DMA driver

## Project description: 
Developing a complete software driver for the DMA peripheral in the STM32F401 MCU.

## The driver provide the following APIs:
1.	A function to initialize the DMA driver.
2.	A function to initialize the DMA channel parameters, DMA Peripheral ID, Trigger source, Source address, destination address, number of transfers, transfer item size, transfer mode, transfer type(Single or burst).
3.	A function to request from the driver to start software transfer (memory to memory).
4.	A function to check the transfer state.

You have to configure the DMA interrupt and in the DMA ISR you have to call an notification function for the DMA client.
Our test code is a dummy client that create two arrays of integers of size 100 elements. One of them is already initialized with numbers of 100,200, … till the end. This will be the source array.
The second one is the destination array with the same type and size and will be initialized by all zeros.
The DMA driver is used to copy the source array into the destination array.


## This Project is created by:
* Tarek Mohamed (https://github.com/Tarek999)
* Fatma Gad (https://github.com/FatmaGad25) 

