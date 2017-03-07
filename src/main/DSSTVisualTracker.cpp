#include "DSSTVisualTracker.hpp"
//#include <unistd.h>

DSSTVisualTracker::DSSTVisualTracker()
{
	cv::Rect init_ROI(707, 362, 40, 97);
	std::vector<std::string> args;

	args.push_back("1.6"); //padding around the target - padding
	args.push_back("0.05"); //spatial bandwitdh of the target - outputSigmaFactor
	args.push_back("0.01"); //regularization factor - lambda
	args.push_back("0.012"); //interpolation factor for learning - learningRate
	args.push_back("2"); //cell size of fhog - cellSize
	args.push_back("0.25"); //spatial bandwitdh of the target(scale) - scaleSigmaFactor
	args.push_back("1.02"); //scale_step - scaleStep
	args.push_back("4"); //cell size of fhog (scale filter) - scaleCellSize
	args.push_back("33"); //number of scale steps - numberOfScales
	args.push_back("13.5"); //if psr is lower than psr threshold, tracking will stop - psrThreshold
	args.push_back("1"); //amount of pixels that are deleted for psr calculation around the peak (1 means that a window
	//of 3 by 3 is deleted; 0 means that max response is deleted; 2 * peak_del + 1 pixels are deleted)
	// - psrPeakDel
	args.push_back("100"); //template size - templateSize

	args.push_back("true"); //enableTrackingLossDetection
	args.push_back("true"); //Use the original parameters found in the DSST paper. Performance is close,
	//but differences do still exist! - originalVersion

	Init(args, init_ROI);
}

DSSTVisualTracker::~DSSTVisualTracker()
{
	cleanup();
}

void DSSTVisualTracker::Init(const std::vector<std::string> &arguments, const cv::Rect &initialROI) {

	//Use false to hide visual output
	tracker.init(initialROI, arguments, false);
}

cv::Rect DSSTVisualTracker::TrackMonocular(const cv::Mat &im) {

	cv::Rect bounding_box;

	double fps = tracker.update(im, bounding_box);

	return bounding_box;
}

void DSSTVisualTracker::cleanup()
{
		
}
