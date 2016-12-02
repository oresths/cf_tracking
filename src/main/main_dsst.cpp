/*
 // License Agreement (3-clause BSD License)
 // Copyright (c) 2015, Klaus Haag, all rights reserved.
 // Third party copyrights and patents are property of their respective owners.
 //
 // Redistribution and use in source and binary forms, with or without modification,
 // are permitted provided that the following conditions are met:
 //
 // * Redistributions of source code must retain the above copyright notice,
 //   this list of conditions and the following disclaimer.
 //
 // * Redistributions in binary form must reproduce the above copyright notice,
 //   this list of conditions and the following disclaimer in the documentation
 //   and/or other materials provided with the distribution.
 //
 // * Neither the names of the copyright holders nor the names of the contributors
 //   may be used to endorse or promote products derived from this software
 //   without specific prior written permission.
 //
 // This software is provided by the copyright holders and contributors "as is" and
 // any express or implied warranties, including, but not limited to, the implied
 // warranties of merchantability and fitness for a particular purpose are disclaimed.
 // In no event shall copyright holders or contributors be liable for any direct,
 // indirect, incidental, special, exemplary, or consequential damages
 // (including, but not limited to, procurement of substitute goods or services;
 // loss of use, data, or profits; or business interruption) however caused
 // and on any theory of liability, whether in contract, strict liability,
 // or tort (including negligence or otherwise) arising in any way out of
 // the use of this software, even if advised of the possibility of such damage.
 */

#include <unistd.h>

#include "DSSTVisualTracker.hpp"

int main(int argc, const char** argv) {
	cv::VideoCapture cap(
			"/mnt/hgfs/Vision/Dataset UAV123/UAV123/data_seq/UAV123/bike1/%06d.jpg");
	// Check if video device can be opened with the given index
	if (!cap.isOpened())
		return 1;

	cv::Mat frame;

	cv::Rect init_ROI(707, 362, 40, 97);
	eSensor camera = MONOCULAR;
	vector<string> args;

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
	args.push_back("false"); //Use the original parameters found in the DSST paper. Performance is close,
							 //but differences do still exist! - originalVersion

	DSSTVisualTracker tracker;
	tracker.Init(args, camera, init_ROI);

	while (1) {
		cap >> frame;

		// Check if grabbed frame is actually full with some content
		if (!frame.empty()) {
			//problem in fhog memory deallocation with 1-channel (gray)
			tracker.TrackMonocular(frame, 1);
		}

		usleep(500);
	}

	return 0;
}
