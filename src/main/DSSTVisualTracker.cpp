#include "DSSTVisualTracker.hpp"
#include <unistd.h>

DSSTVisualTracker::DSSTVisualTracker() //: mbFinishRequested(false), mbFinished(true)
{
}

cv::Rect DSSTVisualTracker::GetCurrentROI() {
	unique_lock < mutex > lock(mMutexTar);
	return targetROI;
}

void DSSTVisualTracker::Init(const vector<string> &arguments,
		const eSensor sensor, const cv::Rect &initialROI) {
	this->mSensor = sensor;

	//Use false to hide visual output
	tracker.init(initialROI, arguments, true);
}

void DSSTVisualTracker::TrackMonocular(const cv::Mat &im,
		const double &timestamp) {
	if (this->mSensor != MONOCULAR) {
		cerr
				<< "ERROR: you called TrackMonocular but input sensor was not set to Monocular."
				<< endl;
		exit(-1);
	}

	cv::Rect bounding_box;

	double fps = tracker.update(im, bounding_box);

	unique_lock <mutex> lock(mMutexTar);
	targetROI = bounding_box;
}

void DSSTVisualTracker::TrackStereo(const cv::Mat &imLeft,
		const cv::Mat &imRight, const double &timestamp) {
	if (this->mSensor != STEREO) {
		cerr
				<< "ERROR: you called TrackStereo but input sensor was not set to STEREO."
				<< endl;
		exit(-1);
	}

	//DSST is a MONOCULAR visual tracker!
	TrackMonocular(imLeft, timestamp);
}

void DSSTVisualTracker::TrackRGBD(const cv::Mat &im, const cv::Mat &depthmap,
		const double &timestamp) {
	if (this->mSensor != RGBD) {
		cerr
				<< "ERROR: you called TrackRGBD but input sensor was not set to RGBD."
				<< endl;
		exit(-1);
	}

	//DSST is a MONOCULAR visual tracker!
	TrackMonocular(im, timestamp);
}

void DSSTVisualTracker::Shutdown() {

}

