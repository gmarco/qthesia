/*
    Virtual Piano Widget for Qt4
    Copyright (C) 2008-2010, Pedro Lopez-Cabanillas <plcl@users.sf.net>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; If not, see <http://www.gnu.org/licenses/>.
*/

#include "vpiano.h"
#include <QtGui/QLayout>
#include <QtGui/QCheckBox>
#include <QtGui/QSlider>
#include <QtGui/QLabel>
#include <QtCore/QTextStream>

static QTextStream cout(stdout, QIODevice::WriteOnly);

VPiano::VPiano(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QCheckBox *chkFlats = new QCheckBox(this);
    QCheckBox *chkLabels = new QCheckBox(this);
    QCheckBox *chkRaw = new QCheckBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal, this);
    chkFlats->setText("Use Flats");
    chkLabels->setText("Show Labels");
    chkRaw->setText("Raw Keyboard");
    slider->setRange(1, 127);
    slider->setValue(100);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(10);
    hbox->addWidget(chkLabels);
    hbox->addWidget(chkFlats);
    hbox->addWidget(chkRaw);
    hbox->addWidget(new QLabel("Velocity", this));
    hbox->addWidget(slider);
    connect(chkFlats, SIGNAL(toggled(bool)), SLOT(useFlats(bool)));
    connect(chkLabels, SIGNAL(toggled(bool)), SLOT(showLabels(bool)));
    connect(chkRaw, SIGNAL(toggled(bool)), SLOT(rawKeyboard(bool)));
    connect(slider, SIGNAL(valueChanged(int)), SLOT(velocity(int)));

    m_piano = new PianoKeybd(this);  // base octave = 3, num. octaves = 5
	connect (this,SIGNAL(StartPlayTone(int,int)),m_piano,SLOT(showNoteOn(int,int))) ;
	connect (this,SIGNAL(StopPlayTone(int,int)),m_piano,SLOT(showNoteOff(int,int)));

    /* set a color for pressed keys (default is QPalette::Highlight) */
    m_piano->setKeyPressedColor(Qt::red);

    /* m_piano = new PianoKeybd(2, 7, this); // ctor. with base and num. octaves */
    /* m_piano->setRotation(270);   // vertical orientation */
    m_piano->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    // Option 1: use signals and slots to connect the note events and handler methods
    // connect(m_piano, SIGNAL(noteOn(int)), SLOT(noteOn(int)));
    // connect(m_piano, SIGNAL(noteOff(int)), SLOT(noteOff(int)));

    // Option 2: use a PianoHandler class to provide the handler methods
    m_piano->setPianoHandler(this);

    layout->addWidget(m_piano);
    layout->addLayout(hbox);
    layout->setSpacing(1);
    layout->setContentsMargins(2,2,2,2);
    setLayout(layout);
    m_time.start();
}

void VPiano::noteOn(int midiNote)
{
    cout << "NoteOn " << midiNote << " time: " << m_time.elapsed() << endl;
}

void VPiano::noteOff(int midiNote)
{
    cout << "NoteOff " << midiNote << " time: " << m_time.elapsed() << endl;
}
void VPiano::showNoteOn(int code,int vel){
	emit (StartPlayTone(code,vel));
}

void VPiano::showNoteOff(int code,int vel){
	emit StopPlayTone(code,vel);
}
#include "vpiano.moc"
