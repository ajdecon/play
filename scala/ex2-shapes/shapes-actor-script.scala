import shapes._

ShapeDrawingActor.start()

ShapeDrawingActor ! new Circle(new Point(0.0,0.0), 1.0)
ShapeDrawingActor ! new Circle(new Point(1.0,2.5), 0.025)
ShapeDrawingActor ! "ponies"
ShapeDrawingActor ! new Rectangle(new Point(3.14,-3.14), 10.0, 15.0)
ShapeDrawingActor ! "exit"


