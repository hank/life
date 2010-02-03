#import "Fibo.h"
#import <stdio.h>

@implementation Fibo
-(id) init
{
  self = [super init];

  if(self) {
    self->cur = 0;
    self->last = 1;
  }

  return self;
}

-(void) print
{
  printf( "%i", last);
}

-(void) next
{
  int tmp = last;
  last = cur;
  cur += tmp;
}
@end
