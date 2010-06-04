package {
  import flash.display.Shape;
  import flash.display.Sprite;
  import flash.events.Event;

  public class MovingCircle extends Sprite {
    public var xspeed:Number;
    public var yspeed:Number;

    public function MovingCircle() {
      graphics.beginFill(0xff9933, 1);
      graphics.drawCircle(0, 0, 40);
    }

    public function init():void {
      // x , y and stage are inherited properties

      x = Math.random() * stage.stageWidth;
      y = Math.random() * stage.stageHeight;

      xspeed = Math.random() * 10;
      yspeed = Math.random() * 10;

      addEventListener(Event.ENTER_FRAME, step); 
    }

    public function step(event:Event):void {

      // bounce ball at stage edges
      if(x + xspeed > stage.stageWidth || x + xspeed < 0) {
        xspeed *= -1;
      }

      if(y + yspeed > stage.stageWidth || y + yspeed < 0) {
        yspeed *= -1;
      }

      x += xspeed;
      y += yspeed;
    }
  }
}
