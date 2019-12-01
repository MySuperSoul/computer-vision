package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "assignment2",
    srcs = ["main.cc"],
    deps = [
        ":KeyPointsFinder",
        "//computer-vision/assignments/common:argparser",
    ],
)

cc_library(
    name = "KeyPointsFinder",
    srcs = ["KeyPointsFinder.cc"],
    hdrs = ["KeyPointsFinder.h"],
    deps = [
        "//computer-vision/assignments/common:renderer",
        "@opencv3//:common",
    ],
)
