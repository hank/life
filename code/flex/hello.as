package {
  import flash.display.*;
  import flash.text.*;
  public class hello extends Sprite {
    public function hello() {
      var t:TextField = new TextField();
      t.text = "hello actionscript 3";
      t.width = 300;
      t.height = 200;
      t.x = 50;
      t.y = 20;
      addChild(t);
    }
  }
}
