#include "algorithms.hpp"
#include "common.hpp"

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace fs = std::filesystem;
using namespace fx;

namespace {

// Apresentação (apenas visualização — não faz parte de nenhum algoritmo)

cv::Mat toBgr(const cv::Mat& m) {
    if (m.channels() == 3) return m;
    cv::Mat o;
    cv::cvtColor(m, o, cv::COLOR_GRAY2BGR);
    return o;
}

cv::Mat fitHeight(const cv::Mat& m, int h) {
    if (m.rows == h) return toBgr(m);
    cv::Mat o;
    cv::resize(toBgr(m), o, cv::Size(std::max(1, m.cols * h / m.rows), h), 0, 0, cv::INTER_AREA);
    return o;
}