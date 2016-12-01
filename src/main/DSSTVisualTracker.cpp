#include "DSSTVisualTracker.hpp"
#include <unistd.h>

DSSTVisualTracker::DSSTVisualTracker() //: mbFinishRequested(false), mbFinished(true)
{
}

cv::Rect DSSTVisualTracker::GetCurrentROI() {
	unique_lock < mutex > lock(mMutexTar);
	return targetR;
}

void DSSTVisualTracker::Init(const vector<string> &arguments,
		const eSensor sensor, const cv::Rect &initialROI) {
	this->mSensor = sensor;

	tracker.init();
/*//	frame_number = 0;
//	int previous_number = 0;
	string configPath = "config.txt";
	Config conf(configPath);
	if (conf.features.size() == 0) {
		cout << "Error: no features specified in config" << endl;
	}
	tracker = new Tracker(conf);

	if (conf.resultsPath != "") {
		outFile.open(conf.resultsPath.c_str(), ios::out);
		if (!outFile) {
			cout << "Error: could not open results file: " << conf.resultsPath
					<< endl;
		}
	}
	initBB = FloatRect(initialROI.x, initialROI.y, initialROI.width,
			initialROI.height);
//    mbFinished = false;
	bool first = false;
	cv::Mat currentFrame;

	while (1) {
		unique_lock < mutex > lock1(mMutexSta);
		if (previous_number != frame_number) {
			previous_number = frame_number;
			unique_lock < mutex > lock(mMutexImg);
			frame.copyTo(currentFrame);

			if (!first) {
				tracker->Initialise(currentFrame, initBB);
				first = true;
			}

			if (tracker->IsInitialised()) {
				tracker->Track(currentFrame);
				const FloatRect& bb = tracker->GetBB();
				unique_lock < mutex > lock2(mMutexTar);
				targetR = cv::Rect(bb.XMin(), bb.YMin(), bb.Width(),
						bb.Height());
				outFile << bb.XMin() << "," << bb.YMin() << "," << bb.Width()
						<< "," << bb.Height() << endl;
			}
		}
//       if(CheckFinish())
//           break;
//
//        usleep(5000);
	}*/

//    SetFinish();
}

void DSSTVisualTracker::TrackMonocular(const cv::Mat &im,
		const double &timestamp) {
	if (this->mSensor != MONOCULAR) {
		cerr
				<< "ERROR: you called TrackMonocular but input sensor was not set to Monocular."
				<< endl;
		exit(-1);
	}

	tracker.update(im);

//	unique_lock < mutex > lock1(mMutexImg);
////    im.copyTo(frame);
//	frame_number++;
}

void DSSTVisualTracker::TrackStereo(const cv::Mat &imLeft,
		const cv::Mat &imRight, const double &timestamp) {
	if (this->mSensor != STEREO) {
		cerr
				<< "ERROR: you called TrackStereo but input sensor was not set to STEREO."
				<< endl;
		exit(-1);
	}

	//STRUCK is a MONOCULAR visual tracker!
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

	//STRUCK is a MONOCULAR visual tracker!
	TrackMonocular(im, timestamp);
}

void DSSTVisualTracker::Shutdown() {
//    unique_lock<mutex> lock(mMutexFinish);
//    mbFinishRequested = true;
}

//bool DSSTVisualTracker::CheckFinish()
//{
//    unique_lock<mutex> lock(mMutexFinish);
//    return mbFinishRequested;
//}
//
//void DSSTVisualTracker::SetFinish()
//{
//    unique_lock<mutex> lock(mMutexFinish);
//    mbFinished = true;
//}
//
//bool DSSTVisualTracker::isFinished()
//{
//    unique_lock<mutex> lock(mMutexFinish);
//    return mbFinished;
//}
