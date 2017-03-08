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

#include "DSSTVisualTracker.hpp"
#include "vot.hpp"

int main(int argc, const char** argv) {
	
	//load region, images and prepare for output
    VOT vot_io("region.txt", "images.txt", "output.txt");
	
	//img = firts frame, initPos = initial position in the first frame
    cv::Rect init_rect = vot_io.getInitRectangle();
	
	cv::Mat image;

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
	args.push_back("false"); //Use the original parameters found in the DSST paper. Performance is close,
							 //but differences do still exist! - originalVersion

	DSSTVisualTracker tracker(args, init_rect);

	double avg_time = 0.;
    int frames = 0;
	cv::Rect bounding_box;
    while (vot_io.getNextImage(image) == 1){
		double time_profile_counter = cv::getCPUTickCount();
		
		//problem in fhog memory deallocation with 1-channel (gray)
		bounding_box = tracker.TrackMonocular(image);
			
		time_profile_counter = cv::getCPUTickCount() - time_profile_counter;
        //std::cout << "  -> speed : " <<  time_profile_counter/((double)cvGetTickFrequency()*1000) << "ms. per frame" << std::endl;
        avg_time += time_profile_counter/((double)cvGetTickFrequency()*1000);
        frames++;
		
		vot_io.outputBoundingBox(bounding_box);
	}
	
	std::cout << "Average processing speed " << avg_time/frames <<  "ms. (" << 1./(avg_time/frames)*1000 << " fps)" << std::endl;

	std::string output = "fps.txt";
	std::ofstream fps_ofstream;

	fps_ofstream.open(output.c_str());
	if (!fps_ofstream.is_open())
		std::cerr << "Error opening output file " << output << "!" << std::endl;

	fps_ofstream << 1. / (avg_time / frames) * 1000 << std::endl;

	fps_ofstream.close();

	return EXIT_SUCCESS;
}
