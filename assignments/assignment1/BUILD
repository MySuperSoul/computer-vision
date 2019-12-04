package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "assignment1",
    srcs = ["main.cc"],
    deps = [
        ":hw1_argparser",
        ":video_processor",
        "//computer-vision/assignments/common:util",
    ],
)

cc_library(
    name = "video_processor",
    srcs = ["VideoProcessor.cc"],
    hdrs = ["VideoProcessor.h"],
    deps = [
        ":image_processor",
        "@opencv3//:common",
    ],
)

cc_library(
    name = "image_processor",
    srcs = ["ImageProcessor.cc"],
    hdrs = ["ImageProcessor.h"],
    deps = [
        "//computer-vision/assignments/common:util",
        "@opencv3//:common",
    ],
)

cc_library(
    name = "hw1_argparser",
    srcs = [],
    hdrs = ["HW1Argparser.h"],
    deps = ["//computer-vision/assignments/common:argparser"],
)
