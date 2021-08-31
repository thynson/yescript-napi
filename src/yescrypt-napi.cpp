#include <napi.h>
#include <yescrypt.h>

class YescryptWorker : public Napi::AsyncWorker
{
public:
  YescryptWorker(Napi::Function &callback,
                 Napi::Buffer<std::uint8_t> password,
                 Napi::Buffer<std::uint8_t> salt,
                 std::uint32_t n,
                 std::uint32_t r,
                 std::uint32_t p,
                 std::uint32_t t,
                 std::uint32_t g,
                 std::uint32_t flags,
                 std::uint32_t dkLength)
                 : AsyncWorker(callback)
                 , password(reinterpret_cast<std::uint8_t*>(password.Data()),
                            reinterpret_cast<std::uint8_t*>(password.Data()) + password.ByteLength())
                 , salt(reinterpret_cast<std::uint8_t*>(salt.Data()),
                        reinterpret_cast<std::uint8_t*>(salt.Data()) + salt.ByteLength())
                 , output(dkLength, 0)
                 , n(n)
                 , r(r)
                 , p(p)
                 , t(t)
                 , g(g)
                 , flags(flags)
  {

  }

  void Execute() override {
    yescrypt_local_t local;
    yescrypt_params_t params = {
        this->flags,
        this->n,
        this->r,
        this->p,
        this->t,
        this->g,
        0
    };
    int result = 0;
    // Current version of yescrypt_local won't failed on init and free
    yescrypt_init_local(&local);

    result = yescrypt_kdf(nullptr,
                 &local,
                 password.data(),
                 password.size(),
                 salt.data(),
                 salt.size(),
                 &params,
                 output.data(),
                 output.size());
    if (result != 0) {
      SetError("Failed to compute yescrypt kdf");
      return;
    }
    // Current version of yescrypt_local won't failed on init and free
    yescrypt_free_local(&local);
  }

  void OnOK() override {
    Callback().Call({Env().Undefined(), Napi::ArrayBuffer::New(Env(), output.data(), output.size())});
  }

private:
  std::vector<std::uint8_t> password;
  std::vector<std::uint8_t> salt;
  std::vector<std::uint8_t> output;
  std::uint32_t n;
  std::uint32_t r;
  std::uint32_t p;
  std::uint32_t t;
  std::uint32_t g;
  std::uint32_t flags;
};


// yescript (password,
static Napi::Value Method(const Napi::CallbackInfo &info)
{

  if (info.Length() != 10)
  {
    Napi::Error::New(info.Env(), "Expect 10 arguments")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  if (!info[0].IsBuffer())
  {
    Napi::Error::New(info.Env(), "password shall be a buffer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }

  auto password = info[0].As<Napi::Buffer<std::uint8_t>>();
  if (!info[1].IsBuffer())
  {
    Napi::Error::New(info.Env(), "salt shall be a buffer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto salt = info[1].As<Napi::Buffer<std::uint8_t>>();
  if (!info[2].IsNumber())
  {
    Napi::Error::New(info.Env(), "N shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto n = info[2].As<Napi::Number>().Uint32Value();
  if (!info[3].IsNumber())
  {
    Napi::Error::New(info.Env(), "r shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto r = info[3].As<Napi::Number>().Uint32Value();
  if (!info[4].IsNumber())
  {
    Napi::Error::New(info.Env(), "p shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto p = info[4].As<Napi::Number>().Uint32Value();

  if (!info[5].IsNumber())
  {
    Napi::Error::New(info.Env(), "t shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto t = info[5].As<Napi::Number>().Uint32Value();
  if (!info[6].IsNumber())
  {
    Napi::Error::New(info.Env(), "g shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto g = info[6].As<Napi::Number>().Uint32Value();

  if (!info[7].IsNumber())
  {
    Napi::Error::New(info.Env(), "keyLength shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto keyLength = info[7].As<Napi::Number>().Uint32Value();

  if (!info[8].IsNumber())
  {
    Napi::Error::New(info.Env(), "flags shall be an integer")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto flags = info[8].As<Napi::Number>().Uint32Value();

  if (flags > 2) {
    Napi::Error::New(info.Env(), "flags shall be either 0(SCRYPT), 1 (YESCRYPT_WORM), or 2 (YESCRYPT_RW).")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  } else if (flags == 2) {
    flags = YESCRYPT_RW_DEFAULTS;
  }

  if (!info[9].IsFunction())
  {
    Napi::Error::New(info.Env(), "callback shall be an function")
        .ThrowAsJavaScriptException();
    return info.Env().Undefined();
  }
  auto cb = info[9].As<Napi::Function>();

  auto worker = new YescryptWorker(cb, password, salt, n, r, p, t, g, flags, keyLength);
  worker->Queue();
  return info.Env().Undefined();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  exports["yescrypt"] = Napi::Function::New(env, Method);

  return exports;
}

NODE_API_MODULE(yescrypt, Init);
