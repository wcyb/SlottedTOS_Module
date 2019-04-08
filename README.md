# Slotted TOS Module
Library that allows receiving and handling data from slotted TOS (Transmissive Optical Sensor) module.
* Uses interrupts to deliver information in real-time
* Demo sketch is included, so you can see how to use this library
* To know which pin you can use for connecting slotted TOS module, check this documentation - [attachInterrupt()](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/) - and use values from "Digital Pins Usable For Interrupts" column for your board

If you don't need real-time informations from module, then you can simply connect OUT pin from TOS module to any digital pin on Arduino and then use [digitalRead()](https://www.arduino.cc/reference/en/language/functions/digital-io/digitalread/) to check if some object is passing through sensor.  
Usually on these modules logic 1 means *object is passing through*, logic 0 means *nothing detected*.

### Only for non-commercial use.
