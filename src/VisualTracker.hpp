#ifndef VISUALTRACKER_H
#define VISUALTRACKER_H

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include "SLAMSystem.hpp"

using namespace std;

class VisualTracker
{
	public:

	    virtual void Init(const vector<string> &arguments, const eSensor sensor, const cv::Rect &initialROI) = 0;

	    virtual void TrackMonocular(const cv::Mat &im, const double &timestamp) = 0;

	    virtual void TrackStereo(const cv::Mat &imLeft, const cv::Mat &imRight, const double &timestamp) = 0;

	    virtual void TrackRGBD(const cv::Mat &im, const cv::Mat &depthmap, const double &timestamp) = 0;

	    virtual void Shutdown() = 0;

	    virtual cv::Rect GetCurrentROI() = 0;

	protected:
	    // Input sensor
	    eSensor mSensor;
};

#endif //VISUALTRACKER_H
