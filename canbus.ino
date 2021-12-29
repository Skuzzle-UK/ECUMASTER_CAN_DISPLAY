#include <Vector.h>

//////////////////////////////////////////////////////////////

#define can_page1 0X500
#define can_page2 0X501

//////////////////////////////////////////////////////////////

struct can_frame canMsg;
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
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK){
      switch (canMsg.can_id){
        case can_page1:{
          ecm.RPM(canMsg.data[0], canMsg.data[1]);
          ecm.AIT(canMsg.data[2]);
          ecm.MAP(canMsg.data[3]);
          ecm.SPEED(canMsg.data[4], canMsg.data[5]);
          ecm.BARO(canMsg.data[6]);
          ecm.OIL_PRESSURE(canMsg.data[7]);
          break;
        }
        case can_page2:{
          ecm.CLT(canMsg.data[0]);
          ecm.LAMBDA(canMsg.data[1]);
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
      //Serial.println("Write CAN");
    }
  }
}

//////////////////////////////////////////////////////////////