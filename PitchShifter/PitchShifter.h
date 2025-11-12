#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;
using namespace daisy::seed;

namespace PitchShifter
{
	// placeholders
	enum AdcChannel
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
	*  Then, converts semitones to appropriate freq scaling ratio
	*	  
	*/
	int paramToFreqRatio(float param);
};