
#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "RtMidi.h"

#include "jdksmidi/world.h"
#include "jdksmidi/track.h"
#include "jdksmidi/multitrack.h"
#include "jdksmidi/filereadmultitrack.h"
#include "jdksmidi/fileread.h"
#include "jdksmidi/fileshow.h"
#include "jdksmidi/filewritemultitrack.h"
#include "time.h"

using namespace jdksmidi;

#include <iostream>
using namespace std;

bool done;
static void finish(int ignore){ done = true; }
double tt=0;
unsigned long start=0,now=0;
void mycallback(double deltatime, std::vector< unsigned char > *message, void *userData ) {
	unsigned int nBytes = message->size();
	MIDIMultiTrack *tracks=(MIDIMultiTrack*)userData;
	for ( unsigned int i=0; i<nBytes; i++ )
		std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
	if ( nBytes > 0 )
		std::cout << "stamp = " << deltatime << std::endl;
	else
		std::cout << "other = " << deltatime << std::endl;

	MIDITimedBigMessage m;
	if (start==0)
		start=clock();
	int track=0;
	if ( nBytes>2 && (message->at(0)&0xE0 )==0x80 ){
		track=1+(message->at(0)&0x0F);
		std::cout << track << "-" << tt << std::endl;

		if ( (message->at(0)&0xF0 )==0x80 )
		m.SetNoteOff(message->at(0),message->at(1),message->at(2));
		else
		m.SetNoteOn(message->at(0),message->at(1),message->at(2));
		if (deltatime<10)
			m.SetTime(tt+=deltatime*100.0);
		//m.SetTime(100000*(double(clock() - start)/CLOCKS_PER_SEC));
		//std::cout <<  (double(clock() - start)/CLOCKS_PER_SEC) << std::endl;
		MIDITrack* tr=tracks->GetTrack( track );
		if (tr)
			tr->PutEvent( m );
	}
}

int main()
{
	 int return_code = -1;
  RtMidiIn *midiin = new RtMidiIn();
  	midiin->openVirtualPort("marco midiin");
  std::vector<unsigned char> message;
  int nBytes, i;
  double stamp;

  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if ( nPorts == 0 ) {
    std::cout << "No ports available!\n";
    //goto cleanup;
  }
  //midiin->openPort( 0 );

  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes( false, false, false );

  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);
 //MIDITimedBigMessage m; // the object for individual midi events
 MIDITimedBigMessage m; // the object for individual midi events
    unsigned char chan, // internal midi channel number 0...15 (named 1...16)
      note, velocity, ctrl, val;

    MIDIClockTime t; // time in midi ticks
    MIDIClockTime dt = 1; // time interval (1 second)
    int clks_per_beat = 100; // number of ticks in crotchet (1...32767)

    int num_tracks = 16; // tracks 0 and 1
    MIDIMultiTrack tracks( num_tracks );  // the object which will hold all the tracks
    int trk; // track number, 0 or 1

    t = 0;
	for (int i=0;i<16;i++){
		m.SetTime( t );

		// track 0 is used for tempo and time signature info, and some other stuff

		trk = 0;

		m.SetTimeSig( 4, 2 ); // measure 4/4 (default values for time signature)
		tracks.GetTrack( trk )->PutEvent( m );

		int tempo = 1000000; // set tempo to 1 000 000 usec = 1 sec in crotchet
		// with value of clks_per_beat (100) result 10 msec in 1 midi tick

		// m.SetTime( t ); // do'nt need, because previous time is not changed
		m.SetTempo( tempo );
		tracks.GetTrack( trk )->PutEvent( m );
	}
    // META_TRACK_NAME text in track 0 music notation software like Sibelius uses as headline of the music
    tracks.GetTrack( trk )->PutTextEvent(t, META_TRACK_NAME, "LibJDKSmidi create_midifile.cpp example by VRM");

    // create cannal midi events and add them to a track 1

    trk = 1;
	tracks.GetTrack( trk )->PutTextEvent(t, META_TRACK_NAME, "Church Organ");

  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";
	midiin->setCallback(&mycallback,&tracks);
  while ( !done ) {
    /*stamp = midiin->getMessage( &message );
    nBytes = message.size();
    for ( i=0; i<nBytes; i++ )
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
   if ( nBytes > 0 )
      std::cout << "stamp = " << stamp << std::endl;
  
   if (nBytes>0){
	   //m.SetTime(t);
	   m.SetTime(t);
   	m.SetNoteOn(message[0],message[1],message[2]);
   	tracks.GetTrack( trk )->PutEvent( m );
   }
	   if (stamp< 10){
   t+=stamp*200;
   }*/
    // Sleep for 10 milliseconds ... platform-dependent.
    usleep( 100000 );
  }
    const char *outfile_name = "create_midifile.mid";
    MIDIFileWriteStreamFileName out_stream( outfile_name );

	if( out_stream.IsValid() )
    {
        // the object which takes the midi tracks and writes the midifile to the output stream
        MIDIFileWriteMultiTrack writer( &tracks, &out_stream );

        // write the output file
        if ( writer.Write( num_tracks, clks_per_beat ) )
        {
            cout << "\nOK writing file " << outfile_name << endl;
            return_code = 0;
        }
        else
        {
            cerr << "\nError writing file " << outfile_name << endl;
        }
    }
    else
    {
        cerr << "\nError opening file " << outfile_name << endl;
    }



  // Clean up
 cleanup:
  delete midiin;

  return 0;
}

