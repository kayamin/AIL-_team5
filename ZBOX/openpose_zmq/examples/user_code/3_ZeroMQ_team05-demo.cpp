// ------------------------- OpenPose Library Tutorial - Pose - Example 1 - Extract from Image -------------------------
// This first example shows the user how to:
// 1. Load an image (`filestream` module)
// 2. Extract the pose of that image (`pose` module)
// 3. Render the pose on a resized copy of the input image (`pose` module)
// 4. Display the rendered pose (`gui` module)
// In addition to the previous OpenPose modules, we also need to use:
// 1. `core` module: for the Array<float> class that the `pose` module needs
// 2. `utilities` module: for the error & logging functions, i.e. op::error & op::log respectively

// 3rdparty dependencies
// GFlags: DEFINE_bool, _int32, _int64, _uint64, _double, _string
#include <gflags/gflags.h>
// Allow Google Flags in Ubuntu 14
#ifndef GFLAGS_GFLAGS_H_
namespace gflags = google;
#endif
// OpenPose dependencies
#include <openpose/core/headers.hpp>
#include <openpose/filestream/headers.hpp>
#include <openpose/gui/headers.hpp>
#include <openpose/pose/headers.hpp>
#include <openpose/utilities/headers.hpp>

#include <iostream>
// #include <zmq.hpp>
#include <fstream>
#include <string>
#include <vector>
#include "./svm.h"

// See all the available parameter options withe the `--help` flag. E.g. `build/examples/openpose/openpose.bin --help`
// Note: This command will show you flags for other unnecessary 3rdparty files. Check only the flags for the OpenPose
// executable. E.g. for `openpose.bin`, look for `Flags from examples/openpose/openpose.cpp:`.
// Debugging/Other
DEFINE_int32(logging_level, 3, "The logging level. Integer in the range [0, 255]. 0 will output any log() message, while"
                               " 255 will not output any. Current OpenPose library messages are in the range 0-4: 1 for"
                               " low priority messages and 4 for important ones.");
// Producer
//DEFINE_string(image_path,               "examples/media/COCO_val2014_000000000192.jpg",     "Process the desired image.");
//DEFINE_string(image_path,               "/home/omron/deep-learning-lecture/team5/openpose-work/1.jpg",     "Process the desired image.");
DEFINE_string(image_path, "/home/team05/Downloads/livecount_tf/frame.png", "Process the desired image.");
//DEFINE_string(output_image,             "/home/omron/deep-learning-lecture/team5/openpose-work/2.jpg",     "output image.");
DEFINE_string(output_image, "/home/team05/Downloads/livecount_tf/frame_pose.png", "output image.");

// OpenPose
DEFINE_string(model_pose, "COCO", "Model to be used. E.g. `COCO` (18 keypoints), `MPI` (15 keypoints, ~10% faster), "
                                  "`MPI_4_layers` (15 keypoints, even faster but less accurate).");
DEFINE_string(model_folder, "models/", "Folder path (absolute or relative) where the models (pose, face, ...) are located.");
DEFINE_string(net_resolution, "-1x368", "Multiples of 16. If it is increased, the accuracy potentially increases. If it is"
                                        " decreased, the speed increases. For maximum speed-accuracy balance, it should keep the"
                                        " closest aspect ratio possible to the images or videos to be processed. Using `-1` in"
                                        " any of the dimensions, OP will choose the optimal aspect ratio depending on the user's"
                                        " input value. E.g. the default `-1x368` is equivalent to `656x368` in 16:9 resolutions,"
                                        " e.g. full HD (1980x1080) and HD (1280x720) resolutions.");
DEFINE_string(output_resolution, "-1x-1", "The image resolution (display and output). Use \"-1x-1\" to force the program to use the"
                                          " input image resolution.");
DEFINE_int32(num_gpu_start, 0, "GPU device start number.");
DEFINE_double(scale_gap, 0.3, "Scale gap between scales. No effect unless scale_number > 1. Initial scale is always 1."
                              " If you want to change the initial scale, you actually want to multiply the"
                              " `net_resolution` by your desired initial scale.");
DEFINE_int32(scale_number, 1, "Number of scales to average.");
// OpenPose Rendering
DEFINE_bool(disable_blending, false, "If enabled, it will render the results (keypoint skeletons or heatmaps) on a black"
                                     " background, instead of being rendered into the original image. Related: `part_to_show`,"
                                     " `alpha_pose`, and `alpha_pose`.");
DEFINE_double(render_threshold, 0.05, "Only estimated keypoints whose score confidences are higher than this threshold will be"
                                      " rendered. Generally, a high threshold (> 0.5) will only render very clear body parts;"
                                      " while small thresholds (~0.1) will also output guessed and occluded keypoints, but also"
                                      " more false positives (i.e. wrong detections).");
DEFINE_double(alpha_pose, 0.6, "Blending factor (range 0-1) for the body part rendering. 1 will show it completely, 0 will"
                               " hide it. Only valid for GPU rendering.");

class MenuSVM
{
  public:
    svm_model *model;

    MenuSVM(std::string model_path)
    {
        if ((this->model = svm_load_model(model_path.c_str())) == NULL)
        {
            op::error("Couldn't load svm_model: " + model_path, __LINE__, __FUNCTION__, __FILE__);
        }
    }

    void test(const op::Array<float> poseKeypoints)
    {
        const auto numberBodyParts = poseKeypoints.getSize(1);
        const int person = 0;
        for (int part = 0; part < numberBodyParts; part++)
        {
            const auto x = poseKeypoints[{person, part, 0}];
            const auto y = poseKeypoints[{person, part, 1}];
            const auto score = poseKeypoints[{person, part, 2}];
            std::cout << x << ",";
            std::cout << y << ",";
            std::cout << score << ",";
        }
        std::cout << std::endl;
    }

    int predict(const op::Array<float> poseKeypoints, const float conf_thresh = .05f)
    {
        /*
        Predict if the person is doing pushup or situp
        Returns:
        -1: Error
         0: Pushup
         1: Situp
        */
        if (poseKeypoints.empty())
        {
            op::log("***NO PERSON IN VISION***");
            return -1;
        }

        // ------------------------- NORMALIZATION -------------------------
        std::vector<float> full_x_coord, full_y_coord, full_conf;
        std::vector<float> feature;
        float x, y, conf;
        float x_max = 0, x_min = 1e6, y_max = 0, y_min = 1e6;
        const int person = 0;

        for (auto bodyPart = 0; bodyPart < poseKeypoints.getSize(1); bodyPart++)
        {
            x = poseKeypoints[{person, bodyPart, 0}];
            y = poseKeypoints[{person, bodyPart, 1}];
            conf = poseKeypoints[{person, bodyPart, 2}];

            if (x_max < x)
            {
                x_max = x;
            }
            if (x_min > x && conf > 0.05)
            {
                x_min = x;
            }
            if (y_max < y)
            {
                y_max = y;
            }
            if (y_min > y && conf > 0.05)
            {
                y_min = y;
            }

            full_x_coord.push_back(x);
            full_y_coord.push_back(y);
            full_conf.push_back(conf);
        }

        for (auto i = 0; i < (int)full_x_coord.size(); i++)
        {
            if (full_conf[i] < conf_thresh)
            {
                feature.push_back(-1.f);
                feature.push_back(-1.f);
            }
            else
            {
                feature.push_back((full_x_coord[i] - x_min) / (x_max - x_min));
                feature.push_back((full_y_coord[i] - y_min) / (y_max - y_min));
            }
        }

        if (feature.size() != 36)
        {
            op::error("feature.size has to be 36", __LINE__, __FUNCTION__, __FILE__);
            return -1;
        }

        // ------------------------- PREDICTION -------------------------
        std::vector<svm_node> svm_input;
        featureToNode(feature, svm_input);
        double pred_label = svm_predict(this->model, &svm_input[0]);
        return (int)pred_label;
    }

  private:
    void featureToNode(std::vector<float> &feature, std::vector<svm_node> &node)
    {
        for (int i = 0; i < (int)feature.size(); i++)
        {
            node.push_back(svm_node());
            node[i].index = i + 1;
            node[i].value = feature[i];
        }
        node.push_back(svm_node());
        node.end()->index = -1;
    }
};

int openPoseTutorialPose1()
{
    //op::log("OpenPose Library Tutorial - Example 1.", op::Priority::High);
    // ------------------------- INITIALIZATION -------------------------
    // Step 1 - Set logging level
    // - 0 will output all the logging messages
    // - 255 will output nothing
    op::check(0 <= FLAGS_logging_level && FLAGS_logging_level <= 255, "Wrong logging_level value.",
              __LINE__, __FUNCTION__, __FILE__);
    op::ConfigureLog::setPriorityThreshold((op::Priority)FLAGS_logging_level);
    op::log("", op::Priority::Low, __LINE__, __FUNCTION__, __FILE__);
    // Step 2 - Read Google flags (user defined configuration)
    // outputSize
    const auto outputSize = op::flagsToPoint(FLAGS_output_resolution, "-1x-1");
    // netInputSize
    const auto netInputSize = op::flagsToPoint(FLAGS_net_resolution, "-1x368");
    // poseModel
    const auto poseModel = op::flagsToPoseModel(FLAGS_model_pose);
    // Check no contradictory flags enabled
    if (FLAGS_alpha_pose < 0. || FLAGS_alpha_pose > 1.)
        op::error("Alpha value for blending must be in the range [0,1].", __LINE__, __FUNCTION__, __FILE__);
    if (FLAGS_scale_gap <= 0. && FLAGS_scale_number > 1)
        op::error("Incompatible flag configuration: scale_gap must be greater than 0 or scale_number = 1.",
                  __LINE__, __FUNCTION__, __FILE__);
    // Enabling Google Logging
    const bool enableGoogleLogging = true;
    // Logging
    op::log("", op::Priority::Low, __LINE__, __FUNCTION__, __FILE__);
    // Step 3 - Initialize all required classes
    op::ScaleAndSizeExtractor scaleAndSizeExtractor(netInputSize, outputSize, FLAGS_scale_number, FLAGS_scale_gap);
    op::CvMatToOpInput cvMatToOpInput;
    op::CvMatToOpOutput cvMatToOpOutput;
    op::PoseExtractorCaffe poseExtractorCaffe{poseModel, FLAGS_model_folder, FLAGS_num_gpu_start, {}, op::ScaleMode::ZeroToOne, enableGoogleLogging};
    op::PoseCpuRenderer poseRenderer{poseModel, (float)FLAGS_render_threshold, !FLAGS_disable_blending,
                                     (float)FLAGS_alpha_pose};
    op::OpOutputToCvMat opOutputToCvMat;
    op::FrameDisplayer frameDisplayer{"OpenPose Tutorial - Example 1", outputSize};
    // Step 4 - Initialize resources on desired thread (in this case single thread, i.e. we init resources here)
    poseExtractorCaffe.initializationOnThread();
    poseRenderer.initializationOnThread();

    // Step 5 (ADDITIONAL) - Initialize Files
    cv::Mat inputImage, outputImage;
    std::ifstream ifs;
    std::ofstream ofs;
    std::string str;
    int flag = 0;
    int result = -1;
    int frame_count = 0;
    MenuSVM predictor("MenuSVM.model");

    // Initialize trigger files
    ofs.open("new_image.txt", std::ios::out);
    ofs << "0";
    ofs.close();

    ofs.open("estimated.txt", std::ios::out);
    ofs << "0" << std::endl
        << "-1";
    ofs.close();

    std::cout << "Server Ready to Go" << std::endl;

    while (1)
    {
        // Check new_image.txt
        ifs.open("new_image.txt", std::ios::in);
        if (ifs)
        {
            std::getline(ifs, str);
            flag = std::atoi(str.c_str());
        }
        else
        {
            std::cout << "Failed to open new_image.txt" << std::endl;
        }
        ifs.close();

        if (!flag)
        {
            continue;
        }
        else{
            std::cout << "Start Estimation: " << frame_count  << std::endl;

            // If new image has been uploaded
            // std::cout << "new_image_flag is true" << std::endl;
            // Flush flag
            ofs.open("new_image.txt", std::ios::out);
            ofs << "0";
            ofs.close();
            // Get image
            inputImage = cv::imread("hub.png");
            cv::resize(inputImage, outputImage, cv::Size(0, 0), 0.1, 0.1);
            //cv::imshow("", outputImage);
            //cv::waitKey(1);
            // result = 1 - result;
            flag = 0;

            // ------------------------- POSE ESTIMATION AND RENDERING -------------------------
            // Step 1 - Read and load image, error if empty (possibly wrong path)
            // Alternative: cv::imread(FLAGS_image_path, CV_LOAD_IMAGE_COLOR);
            // cv::Mat inputImage = op::loadImage(FLAGS_image_path, CV_LOAD_IMAGE_COLOR);
            if (inputImage.empty())
                op::error("Could not open or find the image: " + FLAGS_image_path, __LINE__, __FUNCTION__, __FILE__);
            const op::Point<int> imageSize{inputImage.cols, inputImage.rows};
            // Step 2 - Get desired scale sizes
            std::vector<double> scaleInputToNetInputs;
            std::vector<op::Point<int>> netInputSizes;
            double scaleInputToOutput;
            op::Point<int> outputResolution;
            std::tie(scaleInputToNetInputs, netInputSizes, scaleInputToOutput, outputResolution) = scaleAndSizeExtractor.extract(imageSize);
            // Step 3 - Format input image to OpenPose input and output formats
            const auto netInputArray = cvMatToOpInput.createArray(inputImage, scaleInputToNetInputs, netInputSizes);
            auto outputArray = cvMatToOpOutput.createArray(inputImage, scaleInputToOutput, outputResolution);
            // Step 4 - Estimate poseKeypoints
            poseExtractorCaffe.forwardPass(netInputArray, imageSize, scaleInputToNetInputs);
            const auto poseKeypoints = poseExtractorCaffe.getPoseKeypoints();
            // Step 5 - Render poseKeypoints
            poseRenderer.renderPose(outputArray, poseKeypoints, scaleInputToOutput);
            // Step 6 - OpenPose output format to cv::Mat
            auto outputImage = opOutputToCvMat.formatToCvMat(outputArray);

            //cv::Mat outputImage2;
            //cv::resize(outputImage, outputImage2, cv::Size(0, 0), 0.1, 0.1);
            //cv::imshow("OUTPUT", outputImage2);
            //cv::waitKey(10);
            result = predictor.predict(poseKeypoints);

            // Output estimation result
            ofs.open("estimated.txt");
            ofs << "1" << std::endl
                << result;
            ofs.close();
            // std::cout << "Replied estimation result" << std::endl;
            frame_count++;
        }
    }
    // Return successful message
    return 0;
}

int main(int argc, char *argv[])
{
    // Parsing command line flags
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    // Running openPoseTutorialPose1
    return openPoseTutorialPose1();
}
