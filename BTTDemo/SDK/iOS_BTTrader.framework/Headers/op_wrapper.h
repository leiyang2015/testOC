#pragma once
#include "base_operation.h"
#include "util.h"

namespace bytetrade {

struct op_wrapper {

    base_operation *op;

    op_wrapper() {
    }

    op_wrapper(base_operation *o) {
        op = o;
    }

    bytes toBytes() {

        bytes b;

        b = b + op->getId();
        b = b + op->toBytes();

        return b;
    }

    jsonxx::Object toJsonObject() {
        jsonxx::Object o;
        o << "op" << op->toJsonObject();

        return o;
    }
};
}