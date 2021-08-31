{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "deps/yescrypt/yescrypt.h",
        "deps/yescrypt/yescrypt-opt.c",
        "deps/yescrypt/insecure_memzero.h",
        "deps/yescrypt/insecure_memzero.c",
        "deps/yescrypt/sha256.h",
        "deps/yescrypt/sha256.c",
        "src/yescrypt-napi.cpp"
      ],
      "include_dirs": [
        "deps/yescrypt",
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"]
    }
  ]
}