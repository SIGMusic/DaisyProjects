#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;
using namespace daisy::seed;

DaisySeed hw;

bool rec = false;
bool play = false;


void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		out[0][i] = in[0][i];
		out[1][i] = in[1][i];
	}
}

int main(void)
{
	
	hw.Configure();
	hw.Init();
	Switch fs_A;
	
	bool led_state;
    led_state = true;

	hw.StartLog();
	fs_A.Init(hw.GetPin(25), 1000);

	hw.SetAudioBlockSize(4); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAudio(AudioCallback);

	while(1) {
		while (fs_A.Pressed()) {
				hw.SetLed(led_state);

				// Toggle the LED state for the next time around.
				led_state = !led_state;

				// Wait 500ms
				System::Delay(500);
			}
		// } else if (fs_A.Pressed() && rec == true) {
		// 	rec = false;
		// 	play = true;
		// }
		// if (fs_A.TimeHeldMs() > 2000) {
		// 	rec = false;
		// 	play = false;
		// }
	}
}