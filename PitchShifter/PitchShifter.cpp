#include "PitchShifter.h"

using namespace PitchShifter;

float semiFloat;
int shiftDir;
bool bypass;

#define MAX_DELAY static_cast<size_t>(48000 * 0.75f)
static DelayLine<float, MAX_DELAY> del;

DaisySeed hw;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	if (bypass)
	{
		for (size_t i = 0; i < size; i++)
		{
			out[0][i] = in[0][i];
			out[1][i] = in[1][i];
		}
	}
	else
	{
		for (size_t i = 0; i < size; i++) // placeholder; need to apply FFT, pitch shift, then IFFT here
		{
			float unshifted = in[0][i];
			float shifted = ps.Process(unshifted);

			float del_out = del.Read();
			float sig_out = del_out + shifted * 0.5 + unshifted * 0.5;

			float feedback = (del_out * 0.2f) + shifted * 0.5 + unshifted * 0.5;
			del.Write(feedback);

			out[0][i] = sig_out;
			out[1][i] = sig_out;
		}
	}
}

int main(void)
{
	hw.Init();

	hw.StartLog();
	hw.SetAudioBlockSize(4);
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);

	del.Init();
	del.SetDelay(hw.AudioSampleRate() * 0.55f);

	ps.Init(hw.AudioSampleRate());
	ps.SetDelSize(4096);
	ps.SetTransposition(7);

	pots[SEMITONES].InitSingle(A1);
	pots[KNOB_2].InitSingle(A2);
	pots[KNOB_3].InitSingle(A3);
	pots[KNOB_4].InitSingle(A4);
	pots[KNOB_5].InitSingle(A5);
	pots[KNOB_6].InitSingle(A6);
	hw.adc.Init(pots, NUM_POTS);

	switches[SHIFT_INTERVAL_DIR].Init(D14, D13);
	switches[SWITCH_2].Init(D7, D11);
	switches[SWITCH_3].Init(D2, D4);

	buttons[TOGGLE_BYPASS].Init(D25, 1000, Switch::TYPE_TOGGLE, Switch::POLARITY_INVERTED, Switch::PULL_UP);
	buttons[BUTTON_2].Init(D26, 1000);

	hw.adc.Start();
	hw.StartAudio(AudioCallback);
	hw.SetLed(!bypass);

	while (1)
	{
		buttons[TOGGLE_BYPASS].Debounce();
		buttons[BUTTON_2].Debounce();

		if (buttons[TOGGLE_BYPASS].RisingEdge())
		{
			bypass = !bypass;
			hw.SetLed(!bypass);
		}

		semiFloat = hw.adc.GetFloat(0);
		shiftDir = switches[SHIFT_INTERVAL_DIR].Read();
		paramToFreqRatio(semiFloat, shiftDir);
	}
}

float PitchShifter::paramToFreqRatio(float param, int dir)
{
	int semi = static_cast<int>(round(param * 12));
	// hw.PrintLine("Interval (semitones): %d", semi);
	float freqRatio = pow(2, (semi / 12));
	if (dir == Switch3::POS_DOWN)
	{
		ps.SetTransposition(semi * -1);
		// hw.PrintLine("Shift dir: DOWN");
		return 1 / freqRatio;
	}
	if (dir == Switch3::POS_UP)
	{
		ps.SetTransposition(semi);
		// hw.PrintLine("Shift dir: UP");
		return freqRatio;
	}
	ps.SetTransposition(0);
	return 1;
}
