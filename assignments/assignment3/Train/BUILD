package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "processor",
    srcs = ["processor.cc"],
    hdrs = ["processor.h"],
    deps = ["//computer-vision/assignments/assignment3/preprocessor:image_preprocessor"],
)

cc_binary(
    name = "train",
    srcs = ["train.cc"],
    deps = [":processor"],
)
