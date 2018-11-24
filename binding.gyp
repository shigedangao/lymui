
{
  "targets": [
    {
      "target_name": "lymuilib",
      "sources": [
        "lymui/binding/bootstrap.c",
        "lymui/binding/node_rgb.c",
        "lymui/binding/convert_space.c",
        "lymui/binding/convert_regular.c",
        "lymui/binding/binding_util.c",
        "lymui/binding/bridge.c",
        "lymui/binding/factory.c"
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
