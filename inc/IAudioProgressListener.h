/*
 * IAudioProgressListener.h
 *
 *  Created on: Nov 20, 2013
 *      Author: wolong
 */

#ifndef IAUDIOPROGRESSLISTENER_H_
#define IAUDIOPROGRESSLISTENER_H_


class IAudioProgressListener {
public:
	virtual ~IAudioProgressListener() {};
	virtual void OnAudioProgress(long duration, long position) = 0;
};

#endif /* IAUDIOPROGRESSLISTENER_H_ */
