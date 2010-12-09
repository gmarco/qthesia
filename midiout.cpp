#include <iostream>
#include <cstdlib>
#include "RtMidi.h"
#include <unistd.h>
#define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )

#include "jdksmidi/world.h"
#include "jdksmidi/track.h"
#include "jdksmidi/multitrack.h"
#include "jdksmidi/filereadmultitrack.h"
#include "jdksmidi/fileread.h"
#include "jdksmidi/fileshow.h"
#include "jdksmidi/sequencer.h"
using namespace jdksmidi;

#include <iostream>
#include "b.h"
using namespace std;

void PlayDumpSequencer( MIDISequencer *seq,RtMidiOut* midiout)
{
	std::vector<unsigned char> message(3);
	float pretend_clock_time = 0.0;
	float next_event_time = 0.0;
	MIDITimedBigMessage ev;
	int ev_track;
	seq->GoToTimeMs ( pretend_clock_time );

	if ( !seq->GetNextEventTimeMs ( &next_event_time ) )
	{

		return;
	}

	// simulate a clock going forward with 10 ms resolution for 1 hour
	float max_time = 3600. * 1000.;
	long mtime=0;
	for ( ; pretend_clock_time < max_time; pretend_clock_time += 10. )
	{
		// find all events that came before or a the current time

		while ( next_event_time <= pretend_clock_time )
		{
			mtime++;
			if (mtime <pretend_clock_time){
				//std::cout << mtime << " " << pretend_clock_time << std::endl;
				usleep(1000);
				continue;
			}

			if ( seq->GetNextEvent ( &ev_track, &ev ) )
			{
				// found the event!
				// show it to stdout
				//fprintf ( stdout, "tm=%06.0f : evtm=%06.0f :trk%02d : ",
				//          pretend_clock_time, next_event_time, ev_track );
				//DumpMIDITimedBigMessage ( &ev );
				MIDITimedBigMessage *msg=&ev;
				//std::cout << (int)msg->GetStatus() << " " << (int)msg->GetByte1() << std::endl;
				//std::cout << (int) msg->IsSystemExclusive() <<std::endl;
				//for (int i=0;i<  msg->GetLength() ; i++){
				if (msg->GetStatus()!=0 && msg->GetStatus()!= 255){

					message[0]=msg->GetStatus();
					message[1]=msg->GetByte1();
					message[2]=msg->GetByte2();
					message[3]=msg->GetByte3();
					message[4]=msg->GetByte4();
					message[5]=msg->GetByte5();
					try {
						midiout->sendMessage( &message );
					} catch (std::exception &e){
						std::cout << e.what() << std::endl;
					} catch ( ...) {
						std::cout << (int)msg->GetStatus() << " " << (int)msg->GetByte1() << std::endl;
					}

				}
				//SLEEP(50);
				//		 std::cout << msg->GetChannel( ) << " " << pretend_clock_time-next_event_time <<  " " <<  seq->GetNextEventTimeMs ( &next_event_time ) << std::endl;
				//}
				// now find the next message

				if ( !seq->GetNextEventTimeMs ( &next_event_time ) )
				{
					// no events left so end
					fprintf ( stdout, "End\n" );
					return;
				}
			}
		}
	}
}
RtMidiOut* createMidiOut(){
	RtMidiOut *midiout = new RtMidiOut();
	std::string portName;
	SLEEP(50);
	unsigned int nPorts = midiout->getPortCount();
	if ( nPorts == 0 ) {
		std::cout << "No ports available!\n";
		midiout->openVirtualPort();
		//goto cleanup;
	}
	std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
	for ( unsigned int i=0; i<nPorts; i++ ) {
		try {
			portName = midiout->getPortName(i);
		}
		catch (RtError &error) {
			error.printMessage();
			//goto cleanup;
		}
		std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
	}
	midiout->openPort(nPorts>1?1:0);                                                                                               midiout->openVirtualPort();


	return midiout;
}
