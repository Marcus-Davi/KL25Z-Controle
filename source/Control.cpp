/*
 * Control.cpp
 *
 *  Created on: 13 de set de 2019
 *      Author: marcus
 */

#include <inc/Control.h>


void Control::setSamplingFrequency(float Hz){
	uint32_t usec = 1000000.0/Hz;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
}

void Control::setSamplingTime(float Ts){
	uint32_t usec = 1000000.0*Ts;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
}

void Control::start(){
	PIT_StartTimer(PIT, kPIT_Chnl_0);
	isRunning = true;
}

void Control::stop(){
	PIT_StopTimer(PIT, kPIT_Chnl_0);
	isRunning = false;
}

bool Control::getControlStatus(){
	return isRunning;
}


void Control::setControlLawHandle(FunPt callback){
	ControlHandle = callback;
}

void Control::runControl(){
	if(ControlHandle)
	ControlHandle();
}

//usar Canal 1
void Control::delay(uint32_t usec){
	PIT_SetTimerPeriod(PIT,kPIT_Chnl_1 , USEC_TO_COUNT(usec,CLOCK_GetBusClkFreq()));
	PIT_StartTimer(PIT, kPIT_Chnl_1);
	while(PIT_GetStatusFlags(PIT, kPIT_Chnl_1) != kPIT_TimerFlag);
	PIT_StopTimer(PIT, kPIT_Chnl_1);
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_1 , kPIT_TimerFlag);
}


Control::Control() {
}

Control::~Control() {
	// TODO Auto-generated destructor stub
}


// ADC METHODS

uint32_t Control::ADC::getConversion(){
	//while(ADC16_SetChannelConfig(ADC0, kADC16_ChannelMuxA, ChannelConfig))
	ADC16_SetChannelConfig(ADC0, kADC16_ChannelMuxA, &ChannelConfig);
    while (0U == (kADC16_ChannelConversionDoneFlag & ADC16_GetChannelStatusFlags(ADC0, kADC16_ChannelMuxA)))
    {}

	return ADC16_GetChannelConversionValue(ADC0, kADC16_ChannelMuxA);
}


FunPt Control::ControlHandle = nullptr;
bool Control::isRunning = false;
