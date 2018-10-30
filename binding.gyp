
{
  "targets": [
    {
      "target_name": "lymuilib",
      "sources": [
        "lymui/binding/bootstrap.c",
        "lymui/binding/node_rgb.c",
        "lymui/binding/node_hex.c",
        "lymui/binding/node_cymk.c",
        "lymui/binding/node_hue.c",
        "lymui/binding/binding_util.c",
        "lymui/binding/bridge.c"
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
