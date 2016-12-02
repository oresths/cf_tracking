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
	DsstTrackerRun tracker;

	cv::Rect targetROI;
	cv::Rect2f initBB;

	std::mutex mMutexTar;
};

#endif /* SRC_MAIN_DSSTVISUALTRACKER_HPP_ */
