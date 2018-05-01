This is a very simple Lithium/IOn battery tester, it discharges the battery to compute its capacity.
It does constant current discharge and uses a large TFT screen (ILI9341).
It is powered by a stm32F1, an atmel chip is not powerful enough to drive such a screen.
The control is done through a rotary encoder.

Shopping list :
* ST32F1 aka bluepill
* MCP4725 i2c DAC
* INA219 high side current
* ILI9341 touch screen (we dont use the touch part)
* IRLZ44N power mosfet
* LM358 dual opamp

The schematics are in the schematics folder
