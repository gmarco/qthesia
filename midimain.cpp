#include "midimain.h"
#include "RtMidi.h"
#include "midiout.h"
#include  <vector>
#include "RtMidi.h"                                                                                                              
 #include <unistd.h>                                                                                                             
                                                                                                                                 
#include "midimain.moc"
#include "loadFile.h"
#include <QFileDialog>
#include <QDebug>
using namespace jdksmidi;  

MidiMain::MidiMain(): QMainWindow(NULL){
	setupUi(this);
	midiout=createMidiOut();
}

bool MidiMain::underMouse(){


}
void MidiMain::on_actionLaden_triggered(bool on){
	QString file=QFileDialog::getOpenFileName(this);
	seq=loadMIDIFile(file.toAscii().data());
}
void MidiMain::on_actionAbspielen_triggered(bool on){
 	PlayDumpSequencer(seq,midiout);
}
