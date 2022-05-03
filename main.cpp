//#include "SLABCP2112.h"
///#include "smbus.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "smbus.h"

using namespace std;


int main(/*int argc, char* argv[]*/)
{
    HID_SMBUS_DEVICE    m_hidSmbus;

    // ====================================== Open device =====================================
    if(SMBus_Open(&m_hidSmbus) != 0)
    {
        fprintf(stderr,"ERROR: Could not open device.\r\n");
        SMBus_Close(m_hidSmbus);
        return -1;
    }
    fprintf(stderr,"Device successfully opened.\r\n");



    // ====================================== Configure GPIO 0 =====================================
    BOOL opened;

    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        BYTE direction;
        BYTE mode;
        BYTE function;

        direction = 0x01; //00000001
        mode = 0x01; //00000001
        function = 0x00; //no TX TOGGLE, No RX_TOGGLE, No CLK_OUTPUT

        auto status = HidSmbus_SetGpioConfig(m_hidSmbus, direction, mode, function, 0);
        if(status == HID_SMBUS_SUCCESS)
        {
            cout << "Configuration was Set successfully" << endl;
        }

    }

    // ====================================== Write GPIO 0 latch =====================================
    if (HidSmbus_IsOpened(m_hidSmbus, &opened) == HID_SMBUS_SUCCESS && opened)
    {
        BYTE latchOffValue = 0x01;
        BYTE latchOnValue = 0x00;
        BYTE mask = 0xff;

        // Get the latchValue and mask bitmasks from the control states
        //latchValue = GetLatchValue(mask);

        // Write GPIO latch value
        HID_SMBUS_STATUS status = -1;
        status = HidSmbus_WriteLatch(m_hidSmbus, latchOffValue, mask);
        if(status == HID_SMBUS_SUCCESS)
        {
            cout << "writing 0 to latch was completed successfully: power Off Done" << endl;
        }

        cout << "waiting 1 second" << endl;
        sleep(1);

        status = -1;
        status = HidSmbus_WriteLatch(m_hidSmbus, latchOnValue, mask);
        if(status == HID_SMBUS_SUCCESS)
        {
            cout << "writing 1 to latch was completed successfully: power On Done" << endl;
        }

    }


    // Success
    fprintf(stderr, "Done! Exiting...\r\n");
    SMBus_Close(m_hidSmbus);
    return 0;
}


