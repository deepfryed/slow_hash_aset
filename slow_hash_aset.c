// vim:ts=4:sts=4:sw=4:expandtab

// (c) Bharanee Rathna 2012

#include <ruby/ruby.h>
#include <ruby/encoding.h>

#include <libpq-fe.h>
#include <libpq/libpq-fs.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

PGconn* hc_handle(VALUE self) {
    PGconn *c = 0;
    Data_Get_Struct(self, PGconn, c);
    if (!c)
        rb_raise(rb_eTypeError, "invalid handle");
    return c;
}

void hc_deallocate(PGconn *c) {
    if (c)
        PQfinish(c);
}

VALUE hc_allocate(VALUE klass) {
    PGconn *c = 0;
    return Data_Wrap_Struct(klass, 0, hc_deallocate, c);
}

VALUE hc_initialize(VALUE self) {
    PGconn *c = PQconnectdb("dbname='slow_hash_aset' host='127.0.0.1' port='5432' sslmode='disable'");
    if (!c)
        rb_raise(rb_eStandardError, "unable to connect to pg");
    DATA_PTR(self) = c;
    return self;
}

VALUE hc_execute(VALUE self) {
    int row, col;
    PGresult *res;
    PGconn *connection = hc_handle(self);
    VALUE fields = rb_ary_new();

    rb_ary_push(fields, ID2SYM(rb_intern("id")));
    rb_ary_push(fields, ID2SYM(rb_intern("name")));
    rb_ary_push(fields, ID2SYM(rb_intern("created_at")));

    res = PQexec(connection, "select * from users");
    if (PQresultStatus(res) > 5)
        rb_raise(rb_eRuntimeError, "error: %d %s", PQresultStatus(res), PQerrorMessage(connection));
    PQclear(res);

    for (row = 0; row < 1000; row++) {
        VALUE tuple = rb_hash_new();
        for (col = 0; col < 3; col++) {
            rb_hash_aset(tuple, rb_ary_entry(fields, col), Qnil);
        }
        rb_yield(tuple);
    }
    return Qtrue;
}

VALUE hc_execute_no_aset(VALUE self) {
    int row, col;
    PGresult *res;
    PGconn *connection = hc_handle(self);
    VALUE fields = rb_ary_new();

    rb_ary_push(fields, ID2SYM(rb_intern("id")));
    rb_ary_push(fields, ID2SYM(rb_intern("name")));
    rb_ary_push(fields, ID2SYM(rb_intern("created_at")));

    res = PQexec(connection, "select * from users");
    if (PQresultStatus(res) > 5)
        rb_raise(rb_eRuntimeError, "error: %d %s", PQresultStatus(res), PQerrorMessage(connection));
    PQclear(res);

    for (row = 0; row < 1000; row++) {
        VALUE tuple = rb_hash_new();
        for (col = 0; col < 3; col++) {
            // rb_hash_aset(tuple, rb_ary_entry(fields, col), Qnil);
        }
        rb_yield(tuple);
    }
    return Qtrue;
}

VALUE hc_no_execute(VALUE self) {
    int row, col;
    VALUE fields = rb_ary_new();

    rb_ary_push(fields, ID2SYM(rb_intern("id")));
    rb_ary_push(fields, ID2SYM(rb_intern("name")));
    rb_ary_push(fields, ID2SYM(rb_intern("created_at")));

    for (row = 0; row < 1000; row++) {
        VALUE tuple = rb_hash_new();
        for (col = 0; col < 3; col++) {
            rb_hash_aset(tuple, rb_ary_entry(fields, col), Qnil);
        }
        rb_yield(tuple);
    }
    return Qtrue;
}

void Init_slow_hash_aset() {
    VALUE cHC = rb_define_class("HC", rb_cObject);
    rb_define_alloc_func(cHC, hc_allocate);

    rb_define_method(cHC, "initialize",         hc_initialize,      0);
    rb_define_method(cHC, "execute",            hc_execute,         0);
    rb_define_method(cHC, "execute_no_aset",    hc_execute_no_aset, 0);
    rb_define_method(cHC, "no_execute",         hc_no_execute,      0);
}
