bin_PROGRAMS = hexa_be
hexa_be_SOURCES = hexa_be.cc hexa_common.h commandcontainer.cc bodypart.cc hipgroup.cc hip.cc  hip_sagit.cc  leg.cc  joint.cc  servo.cc 
hexa_be_CPPFLAGS = $(BOOST_CPPFLAGS)
hexa_be_LDFLAGS = $(BOOST_THREAD_LDFLAGS)
hexa_be_LIBS = $(BOOST_THREAD_LIBS)

LDFLAGS_BOOST = \
    $(BOOST_SERIALIZATION_LDFLAGS) 

LIBS_BOOST = \
    $(BOOST_SERIALIZATION_LIBS)

hexa_be_CPPFLAGS += $(BOOST_CPPFLAGS)
hexa_be_LDFLAGS += $(LDFLAGS_BOOST)
LIBS += $(LIBS_BOOST)