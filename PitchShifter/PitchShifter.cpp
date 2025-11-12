#include "PitchShifter.h"

float value;
DaisySeed hw;
using namespace PitchShifter;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	value = hw.adc.GetFloat(0);
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i] * value;
		out[1][i] = in[1][i] * value;
	}
}

int main(void)
{
	hw.Init();

	hw.StartLog();
	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	AdcChannelConfig adcConfig[NUM_ADC_CHANNELS];

	// placeholders
	adcConfig[semitones].InitSingle(A1);
	adcConfig[knob2].InitSingle(A2);
	adcConfig[knob3].InitSingle(A3);
	adcConfig[knob4].InitSingle(A4);
	adcConfig[knob5].InitSingle(A5);
	adcConfig[knob6].InitSingle(A6);

	hw.adc.Init(adcConfig, NUM_ADC_CHANNELS);
	hw.adc.Start();

	hw.StartAudio(AudioCallback);
	while (1)
	{
	}
}

int PitchShifter::paramToHz(float param)
{
	return 0;
}
