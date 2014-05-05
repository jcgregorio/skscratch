{
  "targets": [
    {
      "target_name": "hello",
      "includes": [
        'common.gypi',
      ],
      'include_dirs' : [
        '../src/core',
        '../src/images',
        '../src/pathops',
        ],
      "sources": [ "../../hello.cc" ],
       'dependencies': [
         'flags.gyp:flags',
         'skia_lib.gyp:skia_lib',
         'images.gyp:images',
       ],
    }
  ]
}
