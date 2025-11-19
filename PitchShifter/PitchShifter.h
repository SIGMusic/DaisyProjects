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
	 * 6 - NUM_ADC_CHANNELS: the number of potentiometers, used for config/initialization
	 */
	enum Pots
	{
		SEMITONES = 0,
		KNOB_2,
		KNOB_3,
		KNOB_4,
		KNOB_5,
		KNOB_6,
		NUM_POTS,
	};

	/* Switches - channels managed through libDaisy's Switch3 class
	 * 0 - shiftIntervalDirection: negative if pitch shifting lower, positive if higher, 0 if no shift.
	 * 1 - switch2: placeholder
	 * 2 - switch3: placeholder
	 * 3 - NUM_SWITCHES: the number of switches, used for config/initialization
	 */
	enum Switches
	{
		SHIFT_INTERVAL_DIR = 0,
		SWITCH_2,
		SWITCH_3,
		NUM_SWITCHES,
	};

	/* Buttons - channels managed through libDaisy's Switch class
	 * 0 - toggle: toggles between bypass and active
	 * 1 - button2: placeholder
	 * 2 - NUM_BUTTONS: the number of buttons, used for config/initialization
	 */
	enum Buttons
	{
		TOGGLE_BYPASS = 0,
		BUTTON_2,
		NUM_BUTTONS,
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
	float paramToFreqRatio(float param, int dir);

	AdcChannelConfig pots[NUM_POTS];
	vector<Switch3> switches(NUM_SWITCHES, Switch3());
	vector<Switch> buttons(NUM_BUTTONS, Switch());

	daisysp::PitchShifter ps;
};