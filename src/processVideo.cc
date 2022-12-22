#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/opencv_modules.hpp"
#include "opencv4/opencv2/videoio.hpp"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    // Open the video stream
    // Replace [IP_ADDRESS], [PORT], and [STREAM_URL] with the appropriate values for your stream
    //  VideoCapture cap("http://[IP_ADDRESS]:[PORT]/[STREAM_URL]"); 

    // Set the file path to the video file
    // string file_path = "${VIDEO_FILE_PATH}";

    // Open the video file
    // VideoCapture video(file_path);

    // mp4 file must be in the same directory as the executable
    // in the bin for this code
    VideoCapture video("traffic2.mp4");

    // Check if the video was opened successfully
    if (!video.isOpened()) {
        std::cout << "Error: Could not open video!" << std::endl;
        return 1;
    }

    // Get the video frame size
    Size frameSize = Size((int) video.get(CAP_PROP_FRAME_WIDTH),
                                  (int) video.get(CAP_PROP_FRAME_HEIGHT));

    // Create a window to display the video
    namedWindow("Video", cv::WINDOW_AUTOSIZE);

    // Read and display the video frames
    while (true) {
        Mat frame;
        video >> frame;

        if (frame.empty()) {
            break;
        }

        imshow("Video", frame);
        if (waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
}