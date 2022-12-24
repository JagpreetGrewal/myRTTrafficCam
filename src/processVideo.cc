#include "opencv4/opencv2/opencv.hpp"
#include "opencv4/opencv2/opencv_modules.hpp"
#include "opencv4/opencv2/videoio.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    // Open the video 
    // The video must be in the same directory as the startStream.sh script
    // If running the processVideo executable directly, put the video in the bin directory
    VideoCapture video("trafficStream.mp4");

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

    // Set up the background subtractor
    Ptr<BackgroundSubtractor> bgSubtractor = createBackgroundSubtractorMOG2();

    // Set up the blob detector
    Ptr<SimpleBlobDetector> blobDetector = SimpleBlobDetector::create();

    // Set up the keypoint drawers
    Mat drawFrame;
    vector<KeyPoint> keypoints;

    // Initialize the counters
    int frameCounter = 0;
    int carCounter = 0;

    // Read and display the video frames
    while (true) {
        Mat frame;
        video >> frame;

        if (frame.empty()) {
            break;
        }

        // Convert the frame to grayscale
        Mat grayFrame;
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        // Subtract the background
        Mat fgMask;
        bgSubtractor->apply(grayFrame, fgMask);

        // Detect blobs
        blobDetector->detect(fgMask, keypoints);

        // Draw the keypoints on the frame
        drawKeypoints(frame, keypoints, drawFrame, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Update the counters
        frameCounter++;
        carCounter += keypoints.size();

        imshow("Video", frame);
        if (waitKey(30) >= 0) {
            break;
        }
    }

    // Calculate the average number of cars per frame
    double avgCarsPerFrame = (double) carCounter / frameCounter;

    // Print the results
    cout << "Number of frames: " << frameCounter << endl;
    cout << "Number of cars detected: " << carCounter << endl;
    cout << "Average number of cars per frame: " << avgCarsPerFrame << endl;


    // Print the results to the text file
    std::ofstream outfile;
    outfile.open("../bin/trafficResults.txt", std::ios::app); // open the file in append mode

    // Include the current time for the text file
    time_t t = time(nullptr);
    tm tm = *std::localtime(&t);
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm);

    outfile << "Current time: " << time_str << endl;
    outfile << "Number of frames: " << frameCounter << endl;
    outfile << "Number of cars detected: " << carCounter << endl;
    outfile << "Average number of cars per frame: " << avgCarsPerFrame << endl;
    outfile << "******************************************\n";

    outfile.close();

    return 0;
}