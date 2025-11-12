#include "PitchShifter.h"

float value;
DaisySeed hw;
using namespace PitchShifter;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
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
		value = hw.adc.GetFloat(0);
		paramToFreqRatio(value, 1);
		System::Delay(500);
	}
}

float PitchShifter::paramToFreqRatio(float param, int sign)
{
	int semi = static_cast<int>(round(param * 12));
	// hw.PrintLine("Interval (semitones): %d", semi);
	float freqRatio = pow(2, (semi / 12));
	if (sign < 0)
	{
		return 1 / freqRatio;
	}
	if (sign > 0)
	{
		return freqRatio;
	}
	return 1;
}
