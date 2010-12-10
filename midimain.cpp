#include "midimain.h"
#include "RtMidi.h"
#include "midiout.h"
#include  <vector>
#include "RtMidi.h"                                                                                                              
 #include <unistd.h>                                                                                                             
                                                                                                                                 
#include "midimain.moc"
#include "loadFile.h"
#include <QFileDialog>
#include "jdksmidi/msg.h"
#include <QThread>

//#include <QDebug>
using namespace jdksmidi;  

MidiMain::MidiMain(): QMainWindow(NULL){
	setupUi(this);
	midiout=createMidiOut();
	connect (&timer,SIGNAL(timeout()),this,SLOT(playMidiMS()) );
	connect (this,SIGNAL(showNoteOn(int,int)),vpiano,SLOT(showNoteOn(int,int)));
	connect (this,SIGNAL(showNoteOff(int,int)),vpiano,SLOT(showNoteOff(int,int)));

}
void MidiMain::playMidiMS(){
	MIDITimedBigMessage msg;
	while(m_iter != m_midilist.end() && m_iter->first< m_time_ms+10  )
	{
		msg=m_iter->second;
		
		std::vector<unsigned char> message(3);
		message[0]=msg.GetStatus();
		message[1]=msg.GetByte1();
		message[2]=msg.GetByte2();
		message[3]=msg.GetByte3();
		midiout->sendMessage(&message);

		if ( (message[0]  & 0xF0) == 0x80){
			emit (showNoteOff(message[1],message[2]));
		}
		if ( (message[0] & 0xF0 ) == 0x90 ){
			
			emit (showNoteOn(message[1],message[2]));
			if (message[2]==0){
			
				emit (showNoteOff(message[1],message[2]));
			}
		}
		m_iter++;
	}
	m_time_ms+=10;

}
void MidiMain::on_actionLaden_triggered(bool on){
	QString file=QFileDialog::getOpenFileName(this);
	seq=loadMIDIFile(file.toAscii().data());
	m_midilist=PlayDumpSequencer(seq,midiout);
	m_iter=m_midilist.begin();
}
void MidiMain::on_actionAbspielen_triggered(bool on){
	timer.start(10);
	m_time_ms=0;

}
