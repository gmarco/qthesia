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

#ifndef VPIANO_H
#define VPIANO_H

#include "pianokeybd.h"
#include <QtCore/QTime>

class VPiano : public QWidget, public PianoHandler
{
    Q_OBJECT

public:
    VPiano(QWidget *parent = 0);
    virtual ~VPiano() {};

public slots:
    void useFlats(bool b) { m_piano->setUseFlats(b); }
    void showLabels(bool b) { m_piano->setShowLabels(b); }
    void rawKeyboard(bool b) { m_piano->setRawKeyboardMode(b); }
    void velocity(int v) { m_piano->setVelocity(v); }
    void noteOn(const int midiNote);
    void noteOff(const int midiNote);
    void showNoteOn(int code,int vel);
    void showNoteOff(int code,int vel);
signals:
	void StartPlayTone(int code,int vel);
	void StopPlayTone(int code,int vel);

protected:
    void showEvent ( QShowEvent* ) { m_piano->grabKeyboard(); }

private:
    PianoKeybd *m_piano;
    QTime m_time;
};

#endif // VPIANO_H
