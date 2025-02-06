#ifndef SimpleISA_h
#define SimpleISA_h

/*  This library supports the ISA Scale IVT Modular current/voltage sensor device.  These devices measure current, up to three voltages, and provide temperature compensation.

    This library was written by Jack Rickard of EVtv - http://www.evtv.me copyright 2016
    You are licensed to use this library for any purpose, commercial or private,
    without restriction.

*/
#include <Arduino.h>
#include "can_common.h"

// add the following define in your code to print out current, voltages and temperatures
// #define DEBUG_ISA_DATA

// add the following define to print out CAN frames sent to the IVT-S
// #define DEBUG_ISA_OUTPUT

class ISA : public CANListener
{

public:
  ISA(CAN_COMMON *port, int enablePin = -1);
  ~ISA();
  void initialize();
  void begin(int speed);
  void initCurrent();
  void sendSTORE();
  void CPLUS();
  void CMINUS();
  void VPLUS();
  void VMINUS();
  void STOP();
  void START();
  void RESTART();
  void deFAULT();

  float Amperes; // Floating point with current in Amperes
  double AH;     // Floating point with accumulated ampere-hours
  double KW;
  double KWH;

  double Voltage;
  double Voltage1;
  double Voltage2;
  double Voltage3;
  double VoltageHI;
  double Voltage1HI;
  double Voltage2HI;
  double Voltage3HI;
  double VoltageLO;
  double Voltage1LO;
  double Voltage2LO;
  double Voltage3LO;

  double Temperature;

  bool firstframe;
  int framecount;
  unsigned long timestamp;
  double milliamps;
  long watt;
  long As;
  long lastAs;
  long wh;
  long lastWh;
  CAN_COMMON *port;
  int canSpeed;
  uint8_t page;

private:
  CAN_FRAME frame;
  unsigned long elapsedtime;
  double ampseconds;
  int milliseconds;
  int seconds;
  int minutes;
  int hours;
  char buffer[9];
  char bigbuffer[90];
  uint32_t inbox;
  CAN_FRAME outframe;
  int enablePin;
  int interruptPin;

  void gotFrame(CAN_FRAME *frame, int mailbox); // CAN interrupt service routine
  void printCAN(CAN_FRAME *frame);
  void handle521(CAN_FRAME *frame);
  void handle522(CAN_FRAME *frame);
  void handle523(CAN_FRAME *frame);
  void handle524(CAN_FRAME *frame);
  void handle525(CAN_FRAME *frame);
  void handle526(CAN_FRAME *frame);
  void handle527(CAN_FRAME *frame);
  void handle528(CAN_FRAME *frame);
};

#endif /* SimpleISA_h */
