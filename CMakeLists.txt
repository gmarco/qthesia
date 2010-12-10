cmake_minimum_required(VERSION 2.8)
subdirs(vpiano)


FIND_PACKAGE(Qt4 4.5.0 COMPONENTS QtGui QtSvg QtCore REQUIRED)
INCLUDE(${QT_USE_FILE})

FILE(GLOB jmidi_SRC jmidi/*.cpp)
SET(QTHESIA_SRC
	midiout.cpp
	RtMidi.cpp
	main.cpp
	midimain.cpp
	loadFile.cpp
	${jmidi_SRC}
)
SET (UIS
	main.ui
)
QT4_AUTOMOC(MOC_SRCS midimain.cpp )
QT4_WRAP_UI( UI_SRC ${UIS} )

IF (APPLE)
	SET (QTHESIA_SRC b.cpp ${QTHESIA_SRC} )
	add_definitions(-D__MACOSX_CORE__)
	#link_libraries(-framework CoreMIDI -framework CoreFoundation -framework CoreAudio  -framework AudioUnit -framework AudioToolbox)
	FIND_LIBRARY(COREMIDI CoreMidi)
	FIND_LIBRARY(COREAUDIO CoreAudio)
	FIND_LIBRARY(COREFOUNDATION  CoreFoundation)
	FIND_LIBRARY(AUDIOUNIT  AudioUnit )
	FIND_LIBRARY(AUDIOTOOLBOX  AudioToolbox )
	FIND_LIBRARY(CARBON  Carbon )
	SET (ALLLIBS  ${COREMIDI} ${COREFOUNDATION} ${AUDIOUNIT} ${AUDIOTOOLBOX} ${COREAUDIO} ${CARBON} )
ELSE(APPLE)
	add_definitions(-D__LINUX_ALSASEQ__)
	SET(ALLLIBS asound)

ENDIF(APPLE)

#add_library(vpiano STATIC IMPORTED)
#set_property(TARGET vpiano PROPERTY IMPORTED_LOCATION vpiano/libpiano.a)

include_directories(jmidi/include vpiano)

add_executable(qthesia ${QTHESIA_SRC} ${MOC_SRC} ${UI_SRC} )
target_link_libraries(qthesia piano ${ALLLIBS} ${QT_LIBRARIES} ${QT_SVG_LIBRARY})
