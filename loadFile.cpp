
#include <iostream>
#include <cstdlib>
 #include <unistd.h>

#include "jdksmidi/world.h"
#include "jdksmidi/track.h"
#include "jdksmidi/multitrack.h"
#include "jdksmidi/filereadmultitrack.h"
#include "jdksmidi/fileread.h"
#include "jdksmidi/fileshow.h"
#include "jdksmidi/sequencer.h"
using namespace jdksmidi;

#include <iostream>
using namespace std;

MIDISequencer* loadMIDIFile (std::string file)

{
        const char *infile_name = file.c_str();

        MIDIFileReadStreamFile *rs=new MIDIFileReadStreamFile( infile_name );
        MIDIMultiTrack *tracks=new MIDIMultiTrack;
        MIDIFileReadMultiTrack *track_loader=new MIDIFileReadMultiTrack( tracks );
        MIDIFileRead *reader=new MIDIFileRead( rs, track_loader );

        // set amount of tracks equal to midifile
        tracks->ClearAndResize( reader->ReadNumTracks() );

//      MIDISequencerGUIEventNotifierText notifier( stdout );
//      MIDISequencer seq( &tracks, &notifier );
        MIDISequencer *seq =new MIDISequencer( tracks );

        // load the midifile into the multitrack object
        if ( !reader->Parse() )
        {
            cerr << "\nError parse file " << infile_name << endl;
        }
		return seq;

	
}

