const string APP_ID = "io.github.Miqueas.GTK-Examples.Vala.Gtk4.HeaderBar";
const string APP_TITLE = "Gtk.HeaderBar";
const string appSubtitle = "App subtitle";

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
  var titleLabel = new Gtk.Label(APP_TITLE);
  var subtitleLabel = new Gtk.Label(appSubtitle);
  var titleBox = new Gtk.Box(Gtk.Orientation.VERTICAL, 0);
  var header = new Gtk.HeaderBar();

  window.titlebar = header;
  window.set_default_size(400, 400);

  titleLabel.add_css_class("title");
  subtitleLabel.add_css_class("subtitle");

  titleBox.valign = Gtk.Align.CENTER;
  titleBox.append(titleLabel);
  titleBox.append(subtitleLabel);

  header.title_widget = titleBox;
  header.show_title_buttons = true;
}