#include "tree_sitter/parser.h"
#include <node.h>
#include "nan.h"

using namespace v8;

extern "C" TSLanguage * tree_sitter_embedded_template();

namespace {

NAN_METHOD(New) {}

void Init(Local<Object> exports, Local<Object> module) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Language").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Local<Function> constructor = Nan::GetFunction(tpl).ToLocalChecked();
  Local<Object> instance = constructor->NewInstance(Nan::GetCurrentContext()).ToLocalChecked();
  Nan::SetInternalFieldPointer(instance, 0, tree_sitter_embedded_template());

  Nan::Set(instance, Nan::New("name").ToLocalChecked(), Nan::New("embedded_template").ToLocalChecked());
  Nan::Set(module, Nan::New("exports").ToLocalChecked(), instance);
}

#if NODE_MAJOR_VERSION >= 12
  NODE_MODULE_INIT(/* exports, module, context */) {
    Init(exports, Nan::To<Object>(module).ToLocalChecked());
  }
#else
  NODE_MODULE(tree_sitter_embedded_template_binding, Init)
#endif

}  // namespace