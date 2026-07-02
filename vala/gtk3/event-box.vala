const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk3.EventBox";
const string APP_TITLE = "Gtk.EventBox";

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
  var event_box = new Gtk.EventBox();
  var label = new Gtk.Label("Click me!");

  window.add(event_box);
  window.title = APP_TITLE;
  window.set_border_width(10);
  window.set_default_size(400, 400);

  event_box.add(label);
  event_box.show_all();
  event_box.button_press_event.connect(on_clicked);
}

bool on_clicked(Gtk.Widget self, Gdk.EventButton event) {
  print("Clicked\n");
  return false;
}