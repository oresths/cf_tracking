#ifndef SLAMSYSTEM_H
#define SLAMSYSTEM_H

#include <string>
#include <vector>
#include <opencv2/core/core.hpp>

using namespace std;
// Input sensor
enum eSensor
{
    MONOCULAR=0,
    STEREO=1,
    RGBD=2
};

class SLAMSystem
{
	public:

		virtual void Init(const vector<string> &arguments, const eSensor sensor, const bool bUseViewer) = 0;
		virtual cv::Mat TrackMonocular(const cv::Mat &im, const double &timestamp) = 0;
		virtual cv::Mat TrackStereo(const cv::Mat &imLeft, const cv::Mat &imRight, const double &timestamp) = 0;
		virtual cv::Mat TrackRGBD(const cv::Mat &im, const cv::Mat &depthmap, const double &timestamp) = 0;
		virtual void Shutdown(void) = 0;

	protected:
	    // Input sensor
	    eSensor mSensor;
};

#endif //SLAMSYSTEM_H
