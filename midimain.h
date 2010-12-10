#ifndef __MIDIMAIN_H_
#define __MIDIMAIN_H_
#include <QWidget>
#include <QMainWindow>
#include <QTimer>
#include "ui_main.h"
#include <list>
#include "jdksmidi/msg.h"
namespace jdksmidi{
	class MIDISequencer;
};
class VPiano;
class RtMidiOut;
class MidiMain : public QMainWindow,private Ui_MainWindow{
	Q_OBJECT
	public:
		MidiMain();
	public slots:
		void playMidiMS();
		void on_actionLaden_triggered(bool);
		void on_actionAbspielen_triggered(bool);
	private:
		jdksmidi::MIDISequencer *seq;
		std::list<std::pair<unsigned int,jdksmidi::MIDITimedBigMessage> > m_midilist;
		std::list<std::pair<unsigned int,jdksmidi::MIDITimedBigMessage> >::iterator m_iter;
		RtMidiOut* midiout;
		QTimer timer;
		long m_time_ms;
signals:
		void showNoteOn(int,int);
		void showNoteOff(int,int);
};


#endif
