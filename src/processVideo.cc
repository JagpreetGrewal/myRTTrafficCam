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
    string file_path = "${VIDEO_FILE_PATH}";

    // for videos
    VideoCapture cap(file_path, CAP_FFMPEG);
    
    // for streaming
    // VideoCapture cap(file_path, CAP_V4L2); // 0 indicates the default camera
    if (!cap.isOpened())
    {
        cerr << "ERROR: Unable to open the video" << endl;
        return -1;
    }

    // Set the video resolution
    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 480);

    // Create a window to display the video
    namedWindow("Traffic", WINDOW_AUTOSIZE);

    // Process the video stream
    while (true)
    {
        // Get the next frame from the video stream
        Mat frame;
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty())
        {
            cerr << "ERROR: Unable to grab from the video" << endl;
            break;
        }

        // Display the frame in the window
        imshow("Traffic", frame);

        // Check if the user pressed 'q' to quit
        char c = (char)waitKey(10);
        if (c == 'q')
        {
            break;
        }
    }

    // Close the video stream and the window
    cap.release();
    destroyAllWindows();

    return 0;
}