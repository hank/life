#import <Foundation/NSObject.h>

@interface Fibo: NSObject {
  int last;
  int cur;
}

-(id) init;
-(void) next;
-(void) print;
@end
