package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "roi_creater",
    srcs = ["roi_creater.cc"],
    hdrs = ["roi_creater.h"],
    deps = [
        "//computer-vision/assignments/common:util",
        "@opencv3//:common",
    ],
)

cc_library(
    name = "image_preprocessor",
    srcs = ["image_preprocessor.cc"],
    hdrs = ["image_preprocessor.h"],
    deps = [":roi_creater"],
)
