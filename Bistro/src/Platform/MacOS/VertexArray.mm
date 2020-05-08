#import "VertexArray.h"
#include "MacVertexArrayInterface.h"
#include "Bistro/Core/Log.h"

@implementation VertexArray

Bistro::MacVertexArrayImpl::MacVertexArrayImpl() : self(nullptr)
{
    init();
    B_CORE_INFO("Impl constructor");
}

Bistro::MacVertexArrayImpl::~MacVertexArrayImpl() {
    [(id)self release];
}

void Bistro::MacVertexArrayImpl::init() {
    self = [[VertexArray alloc] init];
}

void Bistro::MacVertexArrayImpl::bind() const {
    [(id)self bind];
}

void Bistro::MacVertexArrayImpl::unbind() const {
    [(id)self unbind];
}

- (void)bind {
    NSLog(@"Bind from objc");
}

- (void)unbind {
    NSLog(@"Unbind from objc");
}

@end
