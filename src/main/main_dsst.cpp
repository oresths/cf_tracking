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

int main(int argc, const char** argv)
{
  cv::VideoCapture cap("/mnt/hgfs/Vision/Dataset UAV123/UAV123/data_seq/UAV123/bike1/%06d.jpg");
  // Check if video device can be opened with the given index
  if (!cap.isOpened())
    return 1;

  cv::Mat frame;

  cv::Rect init_ROI(707,362,40,97);
  eSensor camera = MONOCULAR;
  vector<string> args = {""};

  DSSTVisualTracker tracker;
  tracker.Init(args, camera, init_ROI);

  while (1)
  {
    cap >> frame;

    // Check if grabbed frame is actually full with some content
    if (!frame.empty())
    {
      //problem in fhog memory deallocation with 1-channel (gray)
    	tracker.TrackMonocular(frame, 1);
    }

    usleep(500);
  }

  return 0;
}
