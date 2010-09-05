package {
  import flash.events.Event;
  import flash.display.Sprite;

  public class FirstCircle extends Sprite {
    public function FirstCircle() {
      stage.addEventListener(Event.ENTER_FRAME, init);
    }

    public function init(event:Event):void {
      stage.removeEventListener(Event.ENTER_FRAME, init);
      var circle:MovingCircle = new MovingCircle();
      addChild(circle);

      circle.init();
    }
  }
}
