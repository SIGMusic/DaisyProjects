#include "daisy_seed.h"
#include "daisysp.h"

using namespace std;
using namespace daisy;
using namespace daisysp;
using namespace daisy::seed;

namespace PitchShifter
{
	/* Potentiometer ADC Channels -
	 * 0 - semitones: controls the pitch-shifted interval of the harmony
	 * 1 - knob2: placeholder
	 * 2 - knob3: placeholder
	 * 3 - knob4: placeholder
	 * 4 - knob5: placeholder
	 * 5 - knob6: placeholder
	 * 6 - NUM_ADC_CHANNELS: the number of potentiometers, used for config initialization
	 */
	enum ADCChannel
	{
		semitones = 0,
		knob2,
		knob3,
		knob4,
		knob5,
		knob6,
		NUM_ADC_CHANNELS,
	};

	/* Maps ADC float parameter first to a semitone range (0 to 12)
	 * Then, converts semitones to appropriate freq scaling ratio, using direction specified
	 * by sign.
	 *
	 * @param float param, the ADC input float from the potentiometer
	 * @param int sign, the direction in which to scale frequencies, from the 3-way switch.
	 * 				the middle position of the switch is 0, which works like a bypass. 
	 *
	 * @return float, the ratio by which to scale given frequencies
	 */
	float paramToFreqRatio(float param, int sign);
};