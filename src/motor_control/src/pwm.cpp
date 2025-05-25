#include "motor_control/pwm.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <filesystem>
#include <cstdio>

#define BASE_SYS_PATH "/sys/class/pwm/"
#define PWMDEV "0000:00:17.0"
#define MAX_BUF 64

namespace PWM {

static void writePWM(const std::string &path, int value, rclcpp::Logger logger) {
    int fd = open(path.c_str(), O_WRONLY);
    if (fd < 0) {
        RCLCPP_ERROR(logger, "Failed to open: %s", path.c_str());
        return;
    }
    char buf[MAX_BUF];
    int len = snprintf(buf, sizeof(buf), "%d", value);
    write(fd, buf, len);
    close(fd);
}

static std::string getSysPath() {
    std::string syspath = BASE_SYS_PATH "pwmchip0";
    for (const auto &entry : std::filesystem::directory_iterator(BASE_SYS_PATH)) {
        if (std::filesystem::is_symlink(entry)) {
            std::string target = std::filesystem::read_symlink(entry).string();
            if (target.find(PWMDEV) != std::string::npos) {
                syspath = BASE_SYS_PATH + entry.path().filename().string();
                break;
            }
        }
    }
    return syspath;
}

Servo::Servo(int channel, rclcpp::Logger logger)
    : channel_(channel), syspath_(getSysPath()), logger_(logger) {
    char exportPath[MAX_BUF];
    snprintf(exportPath, sizeof(exportPath), "%s/pwm%d", syspath_.c_str(), channel_);
    struct stat st;
    if (stat(exportPath, &st) != 0) {
        writePWM(syspath_ + "/export", channel_, logger_);
    }

    // Enable PWM channel
    char enablePath[MAX_BUF];
    snprintf(enablePath, sizeof(enablePath), "%s/pwm%d/enable", syspath_.c_str(), channel_);
    writePWM(enablePath, 1, logger_);
}

void Servo::setPeriod(int period_ns) {
    char path[MAX_BUF];
    snprintf(path, sizeof(path), "%s/pwm%d/period", syspath_.c_str(), channel_);
    writePWM(path, period_ns, logger_);
}

// void Servo::setDuty(int duty_ns) {
//     char path[MAX_BUF];
//     snprintf(path, sizeof(path), "%s/pwm%d/duty_cycle", syspath_.c_str(), channel_);
//     writePWM(path, duty_ns, logger_);
// }
void Servo::setDuty(int duty_ns) {
    char path[MAX_BUF];
    snprintf(path, sizeof(path), "%s/pwm%d/duty_cycle", syspath_.c_str(), channel_);

    // 강제로 0 → 실제 값 순으로 write
    writePWM(path, 0, logger_);
    usleep(1000);  // 1ms 대기
    writePWM(path, duty_ns, logger_);
}

}