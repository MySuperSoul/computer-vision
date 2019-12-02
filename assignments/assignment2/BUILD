package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "assignment2",
    srcs = ["main.cc"],
    deps = [
        ":hw2_argparser",
        ":key_points_finder",
    ],
)

cc_library(
    name = "key_points_finder",
    srcs = ["KeyPointsFinder.cc"],
    hdrs = ["KeyPointsFinder.h"],
    deps = [
        "//computer-vision/assignments/common:renderer",
        "@opencv3//:common",
    ],
)

cc_library(
    name = "hw2_argparser",
    srcs = [],
    hdrs = ["HW2Argparser.h"],
    deps = ["//computer-vision/assignments/common:argparser"],
)
