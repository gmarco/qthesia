#include <vector>
#include <list>
#include "jdksmidi/msg.h"
namespace jdksmidi{
class MIDISequencer;
};
class RtMidiOut;
struct MidiTone{
	int code;
	int vel;
};
std::list<std::pair<unsigned int,jdksmidi::MIDITimedBigMessage> > PlayDumpSequencer( jdksmidi::MIDISequencer *seq,RtMidiOut* midiout);
RtMidiOut* createMidiOut();
