package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "eye_position_calibrator",
    srcs = ["EyePositionCalibrator.cc"],
    hdrs = ["EyePositionCalibrator.h"],
    deps = [
        "@opencv3//:common",
    ],
)

cc_binary(
    name = "calibrator",
    srcs = ["Calibrator.cc"],
    deps = [
        ":eye_position_calibrator",
        "//computer-vision/assignments/common:util",
    ],
)
