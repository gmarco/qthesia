#ifndef __MIDIMAIN_H_
#define __MIDIMAIN_H_
#include <QWidget>
#include <QMainWindow>
#include "ui_main.h"
namespace jdksmidi{
	class MIDISequencer;
};
class RtMidiOut;
class MidiMain : public QMainWindow,private Ui_MainWindow{
	Q_OBJECT
	public:
		MidiMain();
		bool underMouse();
	public slots:
		void on_actionLaden_triggered(bool);
		void on_actionAbspielen_triggered(bool);
	private:
		jdksmidi::MIDISequencer *seq;
		RtMidiOut* midiout;
};


#endif
