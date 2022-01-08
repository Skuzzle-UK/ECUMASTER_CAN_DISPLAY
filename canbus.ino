// @TODO Check engine packets and display to show failure of sensors etc.

#define CAN_PAGE_1 0X500
#define CAN_PAGE_2 0X501
#define CAN_ANALOG_INPUTS 0x502

//////////////////////////////////////////////////////////////

void SetupCANBUS(){
  SPI.begin();
  SetupMaskFilter();
  mcp2515.reset(); // @TODO look at this line. Is it needed or in the correct place.
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

//////////////////////////////////////////////////////////////

// @TODO test this filtering. 

// HARDWARE FILTERING of CAN ID
// Mask address of 0x0500 means that every ID from range 0x500 - 0x5FF is accepted and placed in RXB0 (RX Buffer). Anything else is passed to mask 2.
// If we wanted specific address rather than a range we could set mask to 0x05FF and the use filer of 0x502 for example. This would accept only
// ID of 0x502.
// If using masks, we must set both mask registers even if we dont care how the passed on packets are dealt with. In this case setting mask 2
// to match mask 1 means that it wont collect any packets due to them all already being caught by mask 1.
// All of our useful CAN packets are now in RXB0 for reading.

void SetupMaskFilter(){
  mcp2515.setFilterMask(0, 0, 0x0500); // bits of zero are ignored in mask so accepted range 0x500 - 0x5FF
  mcp2515.setFilterMask(1, 0, 0x0500); // because both mask registers require setting
  mcp2515.setFilter(0, 0, 0x500);
}

//////////////////////////////////////////////////////////////

void ReadCANBUS() {
    struct can_frame readMsg;
    /*
    // May require a change to the code below on testing as we have sent our range using mask 0 to RXB0
    // Test this but I believe that the method without the buffer overload will read from all buffers so should work fine.
    //
    if (mcp2515.readMessage(mcp2515.RXB0(), &readMsg) == MCP2515::ERROR_OK) {
      // frame contains received from RXB0 message
    }*/

    if (mcp2515.readMessage(&readMsg) == MCP2515::ERROR_OK){
      switch (readMsg.can_id){
        case CAN_PAGE_1:{
          ecm.RPM(readMsg.data[0], readMsg.data[1]);
          ecm.AIT(readMsg.data[2]);
          ecm.MAP(readMsg.data[3]);
          ecm.SPEED(readMsg.data[4], readMsg.data[5]);
          ecm.BARO(readMsg.data[6]);
          ecm.OIL_PRESSURE(readMsg.data[7]);
          break;
        }
        case CAN_PAGE_2:{
          ecm.CLT(readMsg.data[0]);
          ecm.LAMBDA(readMsg.data[1]);
          break;
        }
      }
    }
}

//////////////////////////////////////////////////////////////

void WriteCANBUS() {
      struct can_frame sendMsg;
      sendMsg.can_id = CAN_ANALOG_INPUTS;
      sendMsg.can_dlc = 8;
      sendMsg.data[0] = ecm.IGNITION_SWITCH_CAN_OUT();
      sendMsg.data[1] = ecm.BOOST_PRESSURE_CAN_OUT();
      sendMsg.data[2] = 0x00;
      sendMsg.data[3] = 0x00;
      sendMsg.data[4] = 0x00;
      sendMsg.data[5] = 0x00;
      sendMsg.data[6] = 0x00;
      sendMsg.data[7] = 0x00;
      mcp2515.sendMessage(&sendMsg);
}

//////////////////////////////////////////////////////////////
