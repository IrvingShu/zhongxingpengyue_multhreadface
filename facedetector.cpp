#include "facedetector.h"
#include <QString>
FaceDetector::FaceDetector(const string &shape_predictor_model)
{
    this->detector = get_frontal_face_detector();
     deserialize(shape_predictor_model) >> this->sp;
}
std::vector<cv::Mat> FaceDetector::getFaceImg(const string &imgName)
{
    array2d<rgb_pixel> img;
    load_image(img, imgName);
    pyramid_up(img);
    std::vector<rectangle> dets = detector(img);
    // Now we will go ask the shape_predictor to tell us the pose of
    // each face we detected.
    std::vector<full_object_detection> shapes;
    //image_window win, win_faces;

    for (unsigned long j = 0; j < dets.size(); ++j)
    {
        full_object_detection shape = sp(img, dets[j]);
        shapes.push_back(shape);
     }

     // We can also extract copies of each face that are cropped, rotated upright,
     // and scaled to a standard size as shown here:
     dlib::array<array2d<rgb_pixel> > face_chips;
     extract_image_chips(img, get_face_chip_details(shapes), face_chips);
     //win_faces.set_image(tile_images(face_chips));

     std::vector<cv::Mat> face_chips_cv;
     for(unsigned int i=0; i<face_chips.size(); i++)
     {
         cv::Mat tmp = toMat(face_chips[i]);
         cv::cvtColor(tmp, tmp, CV_RGB2BGR);
         face_chips_cv.push_back(tmp.clone());
     }
     //std::cout << "Hit enter to process the next image..." << std::endl;
     //std::cin.get();
     return face_chips_cv;

}

