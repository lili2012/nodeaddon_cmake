#include "occt.h"

Napi::Object Pnt2d::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func = DefineClass(env, "Pnt2d", {
       InstanceAccessor<&Pnt2d::GetX, &Pnt2d::SetX>(
           "x",
           static_cast<napi_property_attributes>(napi_default_jsproperty)),
       InstanceAccessor<&Pnt2d::GetY, &Pnt2d::SetY>(
           "y",
           static_cast<napi_property_attributes>(napi_default_jsproperty))
  });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("Pnt2d", func);
  return exports;
}

Pnt2d::Pnt2d(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Pnt2d>(info) {
  Napi::Env env = info.Env();

  int length = info.Length();
  if(length == 0){
    this->pt.SetX(0);
    return;
  }else if (length == 1){
    double v = info[0].As<Napi::Number>();
    this->pt.SetX(v);
    return;
  }else if(length == 2){
    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();
    this->pt.SetX(x);
    this->pt.SetY(y);
  }

  //this->value_ = gp_Pnt2d(x, y);
}

Napi::Value Pnt2d::GetX(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->pt.X());
}

void Pnt2d::SetX(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    Napi::Number arg = value.As<Napi::Number>();
    double x = arg.DoubleValue();
    this->pt.SetX(x);
}

Napi::Value Pnt2d::GetY(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->pt.Y());
}

void Pnt2d::SetY(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    Napi::Number arg = value.As<Napi::Number>();
    double y = arg.DoubleValue();
    this->pt.SetY(y);
}


Napi::Object Line2d::Init(Napi::Env env, Napi::Object exports) {
  Napi::Function func = DefineClass(env, "Line2d", {
       InstanceAccessor<&Line2d::GetPos, &Line2d::SetPos>(
           "pos",
           static_cast<napi_property_attributes>(napi_default_jsproperty)),
       InstanceAccessor<&Line2d::GetDir, &Line2d::SetDir>(
           "dir",
           static_cast<napi_property_attributes>(napi_default_jsproperty))
  });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();
  *constructor = Napi::Persistent(func);
  env.SetInstanceData(constructor);

  exports.Set("Line2d", func);
  return exports;
}

Line2d::Line2d(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<Line2d>(info) {
  Napi::Env env = info.Env();

  int length = info.Length();
  if(length == 0){
    this->line.SetLocation(gp_Pnt2d(0,0));
    this->line.SetDirection(gp_Dir2d(0,0));
    return;
  }else if (length == 1){
    Napi::Object pt = info[0].As<Napi::Object>();
    double x = static_cast<Napi::Value>(pt["x"]).As<Napi::Number>();
    double y = static_cast<Napi::Value>(pt["y"]).As<Napi::Number>();
    this->line.SetLocation(gp_Pnt2d(x,y));
    return;
  }else if(length == 2){
    Napi::Object pt = info[0].As<Napi::Object>();
    double x = static_cast<Napi::Value>(pt["x"]).As<Napi::Number>();
    double y = static_cast<Napi::Value>(pt["y"]).As<Napi::Number>();
    this->line.SetLocation(gp_Pnt2d(x,y));

    Napi::Object dir = info[1].As<Napi::Object>();
    double dir_x = static_cast<Napi::Value>(dir["x"]).As<Napi::Number>();
    double dir_y = static_cast<Napi::Value>(dir["y"]).As<Napi::Number>();
    this->line.SetDirection(gp_Dir2d(dir_x, dir_y));

  }
}

Napi::Value Line2d::GetPos(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);
    const gp_Pnt2d& pt = this->line.Location();
    obj["x"] = pt.X();
    obj["y"] = pt.Y();
    return obj;
}

void Line2d::SetPos(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    Napi::Object arg = value.As<Napi::Object>();
    double x = static_cast<Napi::Value>(arg[(uint32_t)0]).As<Napi::Number>();
    double y = static_cast<Napi::Value>(arg[(uint32_t)1]).As<Napi::Number>();
    this->line.SetLocation(gp_Pnt2d(x,y));
}

Napi::Value Line2d::GetDir(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);
    const gp_Dir2d& dir = this->line.Direction();
    obj["x"] = dir.X();
    obj["y"] = dir.Y();
    return obj;
}

void Line2d::SetDir(const Napi::CallbackInfo &info, const Napi::Value &value) {
    Napi::Env env = info.Env();
    Napi::Object arg = value.As<Napi::Object>();
    double x = static_cast<Napi::Value>(arg[(uint32_t)0]).As<Napi::Number>();
    double y = static_cast<Napi::Value>(arg[(uint32_t)1]).As<Napi::Number>();
    this->line.SetDirection(gp_Dir2d(x,y));
}

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    Pnt2d::Init(env, exports);
    Line2d::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(occt, Init)

