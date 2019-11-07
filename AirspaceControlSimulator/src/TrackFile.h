#ifndef TRACKFILE_H_
#define TRACKFILE_H_

#include <cstddef>

class TrackFile{
	public:
		TrackFile(){}
		
		virtual ~TrackFile() { delete trackfile; } 
		
		static void createInstance(){ trackfile = new TrackFile(); }
		static TrackFile* getTrackFile(){ return trackfile;	}

	private:
		static TrackFile* trackfile;
};

#endif /*TRACKFILE_H_*/
