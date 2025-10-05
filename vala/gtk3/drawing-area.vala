const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.DrawingArea";
const string APP_TITLE = "Gtk.DrawingArea";

int main(string[] args) {
  var app = new Gtk.Application(APP_ID, 0);
  app.startup.connect(on_app_startup);
  app.activate.connect(on_app_activate);
  return app.run(args);
}

void on_app_activate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void on_app_startup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var squareDrawingArea = new Gtk.DrawingArea();
  var circleDrawingArea = new Gtk.DrawingArea();
  var triangleDrawingArea = new Gtk.DrawingArea();

  window.add(box);
  window.title = APP_TITLE;
  window.border_width = 10;
  window.set_default_size(400, 400);

  box.halign = Gtk.Align.CENTER;
  box.valign = Gtk.Align.CENTER;
  box.pack_start(squareDrawingArea, false, false, 0);
  box.pack_start(circleDrawingArea, false, false, 0);
  box.pack_start(triangleDrawingArea, false, false, 0);
  box.show_all();

  squareDrawingArea.set_size_request(80, 80);
  squareDrawingArea.draw.connect((self, cr) => {
    var width = self.get_allocated_width();
    var height = self.get_allocated_height();
    var context = self.get_style_context();

    cr.rectangle(0, 0, width, height);
    Gdk.cairo_set_source_rgba(cr, context.get_color(context.get_state()));
    cr.fill();

    return true;
  });

  circleDrawingArea.set_size_request(80, 80);
  circleDrawingArea.draw.connect((self, cr) => {
    var width = self.get_allocated_width();
    var height = self.get_allocated_height();
    var context = self.get_style_context();

    cr.arc(width / 2, height / 2, int.min(width, height) / 2, 0, 2 * Math.PI);
    Gdk.cairo_set_source_rgba(cr, context.get_color(context.get_state()));
    cr.fill();

    return true;
  });

  triangleDrawingArea.set_size_request(80, 80);
  triangleDrawingArea.draw.connect((self, cr) => {
    var width = self.get_allocated_width();
    var height = self.get_allocated_height();
    var context = self.get_style_context();

    cr.move_to(width / 2, 0);
    cr.line_to(0, height);
    cr.line_to(width, height);
    cr.close_path();
    Gdk.cairo_set_source_rgba(cr, context.get_color(context.get_state()));
    cr.fill();

    return true;
  });
}