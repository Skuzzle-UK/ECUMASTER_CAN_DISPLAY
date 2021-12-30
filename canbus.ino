#include <Vector.h>

//////////////////////////////////////////////////////////////

#define CAN_ANALOG_INPUTS 0x400
#define CAN_PAGE_1 0X500
#define CAN_PAGE_2 0X501

//////////////////////////////////////////////////////////////

Vector<int> canSendQueue;

//////////////////////////////////////////////////////////////

void SetupCANBUS(){
  SPI.begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

//////////////////////////////////////////////////////////////

void ReadCANBUS() {
  if (!ecm.LOCKED()){
    struct can_frame readMsg;
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
}

//////////////////////////////////////////////////////////////

void WriteCANBUS() {
  if (!ecm.LOCKED()){
    if (canSendQueue.size() > 0){
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
  }
}

//////////////////////////////////////////////////////////////