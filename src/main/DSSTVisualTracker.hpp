#ifndef SRC_MAIN_DSSTVISUALTRACKER_HPP_
#define SRC_MAIN_DSSTVISUALTRACKER_HPP_

//#include <opencv2/core/core.hpp>
#include <opencv2/core.hpp>
//#include <opencv2/features2d/features2d.hpp>
#include <opencv2/features2d.hpp>
#include "dsst_tracker_run.hpp"
//#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <string>

class DSSTVisualTracker {
public:
	DSSTVisualTracker();
	
	~DSSTVisualTracker();

	cv::Rect TrackMonocular(const cv::Mat &im);
	
private:
	void Init(const std::vector<std::string>& arguments, const cv::Rect& initialROI);
	void cleanup();

	DsstTrackerRun tracker;
};

#endif /* SRC_MAIN_DSSTVISUALTRACKER_HPP_ */
