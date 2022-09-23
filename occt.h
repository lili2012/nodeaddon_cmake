#ifndef OCCT_H
#define OCCT_H

#include <napi.h>
#include "gp_Pnt2d.hxx"
class Pnt2d : public Napi::ObjectWrap<Pnt2d> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Pnt2d(const Napi::CallbackInfo& info);

 private:
  Napi::Value GetX(const Napi::CallbackInfo& info);
  void SetX(const Napi::CallbackInfo& info, const Napi::Value &value);
  Napi::Value GetY(const Napi::CallbackInfo& info);
  void SetY(const Napi::CallbackInfo& info, const Napi::Value &value); 
  gp_Pnt2d pt;
};

#include <gp_Lin2d.hxx>

class Line2d : public Napi::ObjectWrap<Line2d> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Line2d(const Napi::CallbackInfo& info);

 private:
  Napi::Value GetPos(const Napi::CallbackInfo& info);
  void SetPos(const Napi::CallbackInfo& info, const Napi::Value &value);
  Napi::Value GetDir(const Napi::CallbackInfo& info);
  void SetDir(const Napi::CallbackInfo& info, const Napi::Value &value); 
  gp_Lin2d line;
};




#endif
