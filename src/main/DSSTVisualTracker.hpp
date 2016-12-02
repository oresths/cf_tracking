#ifndef SRC_MAIN_DSSTVISUALTRACKER_HPP_
#define SRC_MAIN_DSSTVISUALTRACKER_HPP_

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <thread>
#include <mutex>
#include <fstream>
#include "../VisualTracker.hpp"
//#include "STRUCK/Config.h"
#include "dsst_tracker_run.hpp"

class DSSTVisualTracker: public VisualTracker {
public:
	DSSTVisualTracker();

	void Init(const vector<string> &arguments, const eSensor sensor,
			const cv::Rect& initialROI);

	void TrackMonocular(const cv::Mat &im, const double &timestamp);

	void TrackStereo(const cv::Mat &imLeft, const cv::Mat &imRight,
			const double &timestamp);

	void TrackRGBD(const cv::Mat &im, const cv::Mat &depthmap,
			const double &timestamp);

	void Shutdown();

	cv::Rect GetCurrentROI();

	bool isFinished();

private:

//	bool CheckNewFrames();
//	bool CheckFinish();
//	void SetFinish();

	DsstTrackerRun tracker;
//	std::ofstream outFile;

//	bool mbFinishRequested;
//	bool mbFinished;
//	std::mutex mMutexFinish;
//	cv::Mat frame;
//	std::mutex mMutexImg;
	cv::Rect targetROI;
	std::mutex mMutexTar;
//	int frame_number;
//	std::mutex mMutexSta;
	cv::Rect2f initBB;
};

#endif /* SRC_MAIN_DSSTVISUALTRACKER_HPP_ */
