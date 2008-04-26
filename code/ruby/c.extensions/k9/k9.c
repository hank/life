#include "ruby.h"

VALUE k9 = Qnil;

void Init_k9();

VALUE method_speak(VALUE self);

void Init_k9()
{
  k9 = rb_define_module("K9");
  rb_define_method(k9, "speak", method_speak, 0);
}

VALUE method_speak(VALUE self)
{
  char text[20] = "Affirmative!";
  return rb_str_new2((char *)&text);
}
