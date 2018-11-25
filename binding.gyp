
{
  "targets": [
    {
      "target_name": "lymuilib",
      "sources": [
        "lymui/binding/bootstrap.c",
        "lymui/binding/binding_util.c",
        "lymui/binding/bridge.c",
        "lymui/binding/factory.c",
        "lymui/binding/convert_xyz.c",
        "lymui/binding/convert_rgb.c",
        "lymui/binding/convert_regular.c",
        "lymui/binding/convert_space.c",
        "lymui/binding/deserializer.c",
        "lymui/binding/deserializer_space.c",
        "lymui/binding/normalizer/normalizer_rgb.c",
        "lymui/binding/normalizer/normalizer_xyz.c",
      ],
      "include_dirs": [
        "bin/include",
        "lymui/binding/include"
      ],
      "libraries": [
        "<(module_root_dir)/bin/liblymui.a"
      ]
    }
  ]
}
