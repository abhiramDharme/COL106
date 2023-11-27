#include "entry.h"

SymEntry::SymEntry() {
    val = new UnlimitedRational();
}

SymEntry::SymEntry(string k, UnlimitedRational* v) : key(k), val(v), left(nullptr), right(nullptr) {}

SymEntry::~SymEntry() {
    delete val;
    // Note: You may want to recursively delete left and right, depending on your use case.
}