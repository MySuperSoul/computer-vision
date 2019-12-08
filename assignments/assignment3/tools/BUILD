package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "show_all_with_mask",
    srcs = ["show_all_with_mask.cc"],
    deps = [
        "//computer-vision/assignments/assignment3/preprocessor:image_preprocessor",
        "//computer-vision/assignments/assignment3/preprocessor:roi_creater",
        "//computer-vision/assignments/common:util",
        "@opencv3//:common",
    ],
)

cc_binary(
    name = "split_dataset",
    srcs = ["split_dataset.cc"],
    deps = [
        "//computer-vision/assignments/common:util",
    ],
)

cc_binary(
    name = "generate_all_images",
    srcs = ["generate_all_images.cc"],
    deps = ["//computer-vision/assignments/common:util"],
)
