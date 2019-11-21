package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "assignment1",
    srcs = ["main.cc"],
    deps = [
        ":vedio_processor",
        "//computer-vision/assignments/common:argparser",
        "//computer-vision/assignments/common:util",
    ],
)

cc_library(
    name = "vedio_processor",
    srcs = ["VedioProcessor.cc"],
    hdrs = ["VedioProcessor.h"],
    deps = [
        "@opencv3//:common",
    ],
)
