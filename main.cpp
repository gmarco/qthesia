
#include <QtGui>
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
#include "midiout.h"
using namespace std;
#include "midimain.h"
#include "rawkeybdapp.h"

int main(int argc,char** argv)

{
	RawKeybdApp app(argc,argv);
#ifdef __APPLE__
	MacMidi macmidi;
#endif
	
	MidiMain *midimain=new MidiMain();
	midimain->setAttribute(Qt::WA_DeleteOnClose);
	midimain->show();

  return app.exec();

}

