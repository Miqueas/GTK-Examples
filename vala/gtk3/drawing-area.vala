const string appID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.DrawingArea";
const string appTitle = "GtkDrawingArea";

int main(string[] args) {
  var app = new Gtk.Application(appID, 0);
  app.startup.connect(onAppStartup);
  app.activate.connect(onAppActivate);
  return app.run(args);
}

void onAppActivate(Application self) {
  var window = (self as Gtk.Application)?.get_active_window();
  window?.present();
}

void onAppStartup(Application self) {
  var window = new Gtk.ApplicationWindow(self as Gtk.Application);
  var box = new Gtk.Box(Gtk.Orientation.VERTICAL, 10);
  var squareDrawingArea = new Gtk.DrawingArea();
  var circleDrawingArea = new Gtk.DrawingArea();
  var triangleDrawingArea = new Gtk.DrawingArea();

  with (window) {
    add(box);
    title = appTitle;
    border_width = 10;
    set_default_size(400, 400);
  }

  with (box) {
    halign = Gtk.Align.CENTER;
    valign = Gtk.Align.CENTER;
    pack_start(squareDrawingArea, false, false, 0);
    pack_start(circleDrawingArea, false, false, 0);
    pack_start(triangleDrawingArea, false, false, 0);
    show_all();
  }

  with (squareDrawingArea) {
    set_size_request(80, 80);
    draw.connect((self, cr) => {
      var width = self.get_allocated_width();
      var height = self.get_allocated_height();
      var context = self.get_style_context();

      cr.rectangle(0, 0, width, height);
      Gdk.cairo_set_source_rgba(cr, context.get_color(context.get_state()));
      cr.fill();

      return true;
    });
  }

  with (circleDrawingArea) {
    set_size_request(80, 80);
    draw.connect((self, cr) => {
      var width = self.get_allocated_width();
      var height = self.get_allocated_height();
      var context = self.get_style_context();

      cr.arc(width / 2, height / 2, int.min(width, height) / 2, 0, 2 * Math.PI);
      Gdk.cairo_set_source_rgba(cr, context.get_color(context.get_state()));
      cr.fill();

      return true;
    });
  }

  with (triangleDrawingArea) {
    set_size_request(80, 80);
    draw.connect((self, cr) => {
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
}