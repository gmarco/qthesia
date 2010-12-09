#include <vector>

namespace jdksmidi{
class MIDISequencer;
};
class RtMidiOut;

void PlayDumpSequencer( jdksmidi::MIDISequencer *seq,RtMidiOut* midiout);
RtMidiOut* createMidiOut();
