#include <opencv2/opencv.hpp>
#include <vector>
#include <filesystem>

std::vector<cv::Vec6f> delaunay_triangulation(std::vector<cv::Point2f> points) {
    cv::Rect rect(0, 0, 255, 255);
    cv::Subdiv2D subdiv(rect);

    for (auto &p : points) {
        subdiv.insert(p);
    }

    std::vector<cv::Vec6f> triangles;
    subdiv.getTriangleList(triangles);

    return triangles;
}

int main() {
    std::vector<cv::Point2f> a_n = {{0,   0},
                                    {0,   254},
                                    {254, 0},
                                    {254, 254},
                                    {44,  34},
                                    {151, 37},
                                    {91,  101},
                                    {217, 104},
                                    {35,  165},
                                    {162, 167}};
    std::vector<cv::Point2f> a_k = {{0,   0},
                                    {0,   254},
                                    {254, 0},
                                    {254, 254},
                                    {51,  34},
                                    {158, 28},
                                    {98,  77},
                                    {215, 77},
                                    {47,  166},
                                    {179, 157}};

    auto triangulation_n = delaunay_triangulation(a_n);
    std::filesystem::path currentDir = std::filesystem::current_path();

    // Выводим текущую директорию на экран
    std::cout << "Current Directory: " << currentDir << std::endl;


    cv::Mat image = cv::imread("../grid.png");
    cv::Mat result_image = cv::Mat::zeros(image.size(), image.type());



    for (auto &t: triangulation_n) {
        std::vector<cv::Point2f> src_points = {{t[0], t[1]},
                                               {t[2], t[3]},
                                               {t[4], t[5]}};
        std::vector<cv::Point2f> dst_points;

        for (auto &pt: src_points) {
            for (size_t i = 0; i < a_n.size(); ++i) {
                if (a_n[i] == pt) {
                    dst_points.push_back(a_k[i]);
                    break;
                }
            }
        }
        std::vector<cv::Point> dst_points_int;
        for (const auto &pt: dst_points) {
            dst_points_int.emplace_back(static_cast<int>(pt.x), static_cast<int>(pt.y));
        }

        cv::Mat transform_matrix = cv::getAffineTransform(src_points, dst_points);
        cv::Mat warped_triangle;
        cv::warpAffine(image, warped_triangle, transform_matrix, image.size(), cv::INTER_LINEAR,
                       cv::BORDER_REFLECT_101);

        std::vector<cv::Point> int_dst_points;
        for (const auto &point : dst_points) {
            int_dst_points.emplace_back(static_cast<int>(point.x), static_cast<int>(point.y));
        }

        cv::Mat mask = cv::Mat::zeros(image.size(), image.type());

        cv::fillConvexPoly(mask, int_dst_points, cv::Scalar(1, 1, 1), 16, 0);
        cv::add(result_image, warped_triangle.mul(mask), result_image);
    }

    cv::imshow("Result", result_image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
