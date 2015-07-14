/* 
 * CExtensions/BPFCompiler/BPFCompiler.c
 * Written by, Sohail Qayum Malik[sqm@hackers.pk]
 **/

#include "BPFCompiler.h"

/*
 * @self, receiver object
 **/ 
static VALUE t_init(VALUE self) {

   printf("In init()\n");

   return self;
}

/*
 * #define R_CAST(st)	(struct st*)
 * #define RARRAY(args)	(R_CAST(RArray)args)
 */ 

/*
 * @self, receiver object
 * @args, type T_ARRAY
 */ 
static VALUE t_add(VALUE self, VALUE args) {

   long i;
   VALUE arg;

   /*
    * Raise exception
    * To explicitly raise an exception...
    * rb_raise(rb_eTypeError, "Message string");
    */ 
   Check_Type(args, T_ARRAY);

   for ( i = 0; i < RARRAY_LEN(args); i++ ) {

      arg = rb_ary_entry(args, i);
      printf("%s(%d)\n", RSTRING_PTR(arg), RSTRING_LEN(arg));
   }

   arg = rb_ary_entry(args, 3);

   return T_NIL;
}

VALUE cBPF;

void Init_BPFCompiler() {

   cBPF = rb_define_class("BPFCompiler", rb_cObject);
   rb_define_method(cBPF, "add", t_add, -2);
   rb_define_method(cBPF, "init", t_init, 0);
}

