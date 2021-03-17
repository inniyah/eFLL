import eFLL.Fuzzy as Fuzzy

from libcpp cimport bool
from libcpp.memory cimport shared_ptr, weak_ptr
from cython.operator cimport dereference as deref

fuzzy = Fuzzy.cFuzzy()
