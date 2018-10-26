
{
  "targets": [
    {
      "target_name": "lymuilm",
      "sources": [
        "lymui/binding/bootstrap.c",
        "lymui/binding/node_rgb.c",
        "lymui/binding/binding_util.c"
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
