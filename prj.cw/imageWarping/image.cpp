#include "image.h"
#include <nfd.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <ctime>

Image::Image() = default;

float Image::transparency = 0.5f;
float Image::pointRadius = 8.0f;

void Image::openImage() {
    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_OpenDialog(nullptr, nullptr, &outPath);
    if (result == NFD_OKAY) {
        if (!texture.loadFromFile(outPath)) {
            exit(EXIT_FAILURE);
        }
        is_opened = true;
        sprite.setTexture(texture);
        ast = Asterism(cv::Rect(0, 0, texture.getSize().x, texture.getSize().y));
        drawPicture();
    } else {
        std::cout << "nfd error" << std::endl;
    }
}

void Image::genWarpImg(const Image &firstSourceImage, const Image &secondSourceImage) {
    clock_t start = clock();
    sf::Image srcImg = firstSourceImage.texture.copyToImage();
    sf::Image dstImg = secondSourceImage.texture.copyToImage();
    cv::Size2f srcImgSize(srcImg.getSize().x, srcImg.getSize().y);
    cv::Size2f dstImgSize(dstImg.getSize().x, dstImg.getSize().y);
    cv::Mat image(srcImgSize, CV_8UC4, (void *) srcImg.getPixelsPtr(), cv::Mat::AUTO_STEP);
    cv::cvtColor(image, image, cv::COLOR_RGBA2RGB);

    std::vector<cv::Point2f> a_n = {{0,                    0},
                                    {0,                    srcImgSize.height - 1},
                                    {srcImgSize.width - 1, 0},
                                    {srcImgSize.width - 1, srcImgSize.height - 1}};
    std::vector<cv::Point2f> a_k = {{0,                    0},
                                    {0,                    dstImgSize.height - 1},
                                    {dstImgSize.width - 1, 0},
                                    {dstImgSize.width - 1, dstImgSize.height - 1}};

    for (int i = 0; i < firstSourceImage.ast.countPts(); ++i) {
        a_n.emplace_back(firstSourceImage.ast.getPosition(i));
    }
    for (int i = 0; i < secondSourceImage.ast.countPts(); ++i) {
        a_k.emplace_back(secondSourceImage.ast.getPosition(i));
    }

    cv::Subdiv2D subdiv(cv::Rect(0, 0, srcImgSize.width * 10, srcImgSize.height * 10));

    for (auto &p: a_n) {
        subdiv.insert(p);
    }
    std::vector<cv::Vec6f> triangulation_n;
    subdiv.getTriangleList(triangulation_n);

    cv::Mat result_image = cv::Mat::zeros(dstImgSize, image.type());

    for (auto &t: triangulation_n) {
        std::vector<cv::Point2f> src_points = {{t[0], t[1]},
                                               {t[2], t[3]},
                                               {t[4], t[5]}};
        std::vector<cv::Point2f> dst_points;
        for (auto &pt: src_points) {
            for (size_t i = 0; i < a_n.size(); ++i) {
                if (static_cast<cv::Point_<float>>(a_n[i]) == pt) {
                    dst_points.push_back(a_k[i]);
                    break;
                }
            }
        }

        cv::Rect src_bounding_rect = cv::boundingRect(src_points);
        cv::Rect dst_bounding_rect = cv::boundingRect(dst_points);

        cv::Point2f shift_src(src_bounding_rect.x, src_bounding_rect.y);
        cv::Point2f shift_dst(dst_bounding_rect.x, dst_bounding_rect.y);

        std::vector<cv::Point2f> local_src_points;
        std::vector<cv::Point2f> local_dst_points;

        for (auto &pt: src_points) {
            local_src_points.push_back(pt - shift_src);
        }
        for (auto &pt: dst_points) {
            local_dst_points.push_back(pt - shift_dst);
        }
        std::vector<cv::Point> int_local_src_points;
        for (const auto &point: local_src_points) {
            int_local_src_points.emplace_back(static_cast<int>(point.x), static_cast<int>(point.y));
        }
        std::vector<cv::Point> int_local_dst_points;
        for (const auto &point: local_dst_points) {
            int_local_dst_points.emplace_back(static_cast<int>(point.x), static_cast<int>(point.y));
        }

        cv::Mat roi = image(src_bounding_rect);

        cv::Mat local_transform = cv::getAffineTransform(local_src_points, local_dst_points);
        cv::Mat warped;
        cv::warpAffine(roi, warped, local_transform, dst_bounding_rect.size());

        cv::Mat mask(warped.size(), CV_8U, cv::Scalar(0));
        cv::fillConvexPoly(mask, int_local_dst_points, cv::Scalar(1), 16, 0);

        warped.copyTo(result_image(dst_bounding_rect), mask);
    }


    if (result_image.channels() == 3) {
        cv::cvtColor(result_image, result_image, cv::COLOR_BGR2BGRA);
    }

    texture.create(result_image.cols, result_image.rows);
    texture.update(result_image.data);
    sprite.setTexture(texture);
    is_opened = true;

    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "time: " << duration << std::endl;
}

void Image::drawCircles() {
    pointsTexture.clear(sf::Color(0, 0, 0, 0));
    for (std::size_t i = 0; i < ast.countPts(); ++i) {
        sf::CircleShape tempCircle(pointRadius);
        cv::Point point(ast.getPosition(i));
        tempCircle.setPosition(sprite.getTransform().transformPoint(point.x, point.y));
        tempCircle.move(-pointRadius, -pointRadius);
        tempCircle.setFillColor(sf::Color::Red);
        if (hoveredCircleIndex == i) {
            tempCircle.setOutlineThickness(3);
            tempCircle.setOutlineColor(sf::Color(255, 178, 102));
        }
        pointsTexture.draw(tempCircle);
    }
}

void Image::drawPicture() {
    internalTexture.clear();
    internalTexture.draw(sprite);
}

void Image::drawPicture(sf::Sprite overlaySprite) {
    drawPicture();
    overlaySprite.setColor(sf::Color(255, 255, 255, transparency * 255));
    internalTexture.draw(overlaySprite);
}

void Image::importPoints() {
    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_OpenDialog("txt", nullptr, &outPath);
    if (result == NFD_OKAY) {
        ast.loadPts(outPath);
        drawCircles();
    } else {
        std::cout << "nfd error" << std::endl;
    }
}

void Image::exportPoints() {
    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_SaveDialog("txt", nullptr, &outPath);
    if (result == NFD_OKAY) {
        ast.savePts(outPath);
    }
}



